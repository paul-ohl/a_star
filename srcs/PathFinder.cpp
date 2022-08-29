#include <iostream>
#include <vector>
#include "PathFinder.hpp"

PathFinder::PathFinder( void ) { return; }
PathFinder::~PathFinder( void ) { return; }

PathFinder::PathFinder( const PathFinder& other )
{
	if (this == &other)
		return;
	*this = other;
}

PathFinder&	PathFinder::operator=( const PathFinder &other )
{
	this->_map = other._map;
	return *this;
}

void	PathFinder::calculatePath( Map& map )
{
	Point* currentPoint;

	this->_map = map;
	setStartAndArrivalPoints();
	currentPoint = this->_map.startPoint;
	openList.push_back(this->_map.startPoint);
	aStar(currentPoint);
}

void	PathFinder::drawPath( void )
{
	Point*	currentPoint = this->_map.arrivalPoint->parent;

	while (currentPoint != this->_map.startPoint)
	{
		if (!currentPoint)
			throw std::logic_error("Algorithm error");
		currentPoint->c = 'o';
		currentPoint = currentPoint->parent;
	}
}

Map	PathFinder::getMap( void )
{
	return this->_map;
}

void	PathFinder::setStartAndArrivalPoints( void )
{
	std::vector<Point>::iterator	startPosition;
	std::vector<Point>::iterator	arrivalPosition;

	for (Map::vector2d::iterator it = _map.getMap().begin();
			it != _map.getMap().end(); it++)
	{
		startPosition = std::find(it->begin(), it->end(), 'S');
		if (startPosition != it->end())
			_map.startPoint = &(*startPosition);
		arrivalPosition = std::find(it->begin(), it->end(), 'A');
		if (arrivalPosition != it->end())
			_map.arrivalPoint = &(*arrivalPosition);
	}
}

void	PathFinder::aStar( Point *currentPoint )
{
	std::vector<Point*> neighbours;
	int i = 0;

	while (openList.size() && i < 3)
	{
		openList.erase(std::find(openList.begin(), openList.end(), currentPoint));
		neighbours = generateNeighbours(currentPoint);
		for (std::vector<Point*>::iterator it = neighbours.begin();
				it != neighbours.end(); it++)
		{
			if (isArrivalPoint(*it))
			{
				(*it)->parent = currentPoint;
				return;
			}
			addToOpenListIfValid(currentPoint, *it);
		}
		closedList.push_back(currentPoint);
		currentPoint = getBestNextPoint();
	}
	throw std::invalid_argument("Map cannot be completed");
}

std::vector<Point*>	PathFinder::generateNeighbours( Point* currentPoint )
{
	std::vector<Point*> neighbours;
	Point*				selectedNeighbour;
	size_t				neighbourX;
	size_t				neighbourY;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;
			neighbourX = currentPoint->position.first + i;
			neighbourY = currentPoint->position.second + j;
			if (checkNeighbourValidity(neighbourX, neighbourY))
			{
				selectedNeighbour = &_map.getMap()[neighbourY][neighbourX];
				neighbours.push_back(selectedNeighbour);
			}
		}
	}
	return neighbours;
}

bool	PathFinder::isArrivalPoint( Point* point )
{
	if (point->position.first == this->_map.arrivalPoint->position.first
			&& point->position.second == this->_map.arrivalPoint->position.second)
		return true;
	return false;
}

void	PathFinder::addToOpenListIfValid( Point* currentPoint, Point* neighbourPoint )
{
	std::vector<Point*>::iterator positionInOpenList;

	float neighbourCost = currentPoint->cost
		+ currentPoint->calculateDistance(neighbourPoint);
	float neighbourScore = neighbourCost
		+ neighbourPoint->calculateDistance(this->_map.arrivalPoint);
	positionInOpenList = std::find(openList.begin(), openList.end(), neighbourPoint);
	if (positionInOpenList == openList.end()
			|| neighbourScore < (*positionInOpenList)->score)
	{
		neighbourPoint->cost = neighbourCost;
		neighbourPoint->score = neighbourScore;
		neighbourPoint->parent = currentPoint;
		if (positionInOpenList == openList.end())
			openList.push_back(neighbourPoint);
	}
}

bool	PathFinder::checkNeighbourValidity( size_t neighbourX, size_t neighbourY )
{
	Point* neighbourPoint;

	if (neighbourX < 0 || neighbourY < 0)
		return false;
	if (neighbourX >= this->_map.getMap()[neighbourY].size())
		return false;
	if (neighbourY >= this->_map.getMap().size())
		return false;
	neighbourPoint = &_map.getMap()[neighbourY][neighbourX];
	if (std::find(closedList.begin(), closedList.end(), neighbourPoint)
			!= closedList.end())
		return false;
	if (neighbourPoint->c != '.' && neighbourPoint->c != 'A')
		return false;
	return true;
}

Point*	PathFinder::getBestNextPoint( void )
{
	Point*				bestCandidate = nullptr;
	std::vector<Point*> bestCandidates;

	if (openList.size() == 0)
		return nullptr;
	for (std::vector<Point*>::iterator it = openList.begin();
			it != openList.end(); it++)
	{
		if (!bestCandidates.size() || (*it)->score < bestCandidates[0]->score)
		{
			bestCandidates.clear();
			bestCandidates.push_back(*it);
		}
		else if ((*it)->score == bestCandidates[0]->score)
			bestCandidates.push_back(*it);
	}
	for (std::vector<Point*>::iterator it = bestCandidates.begin();
			it != bestCandidates.end(); it++)
	{
		if (!bestCandidate || (*it)->cost > bestCandidate->cost)
			bestCandidate = *it;
	}
	return bestCandidate;
}
