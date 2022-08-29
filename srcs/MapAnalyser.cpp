#include "MapAnalyser.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <array>

#define BUF_SIZE 100

MapAnalyser::MapAnalyser( void ) { return; }
MapAnalyser::~MapAnalyser( void )
{
	if (this->_mapFileStream.is_open())
		this->_mapFileStream.close();
}

MapAnalyser::MapAnalyser( const MapAnalyser& other )
{
	if (this == &other)
		return;
	*this = other;
}

MapAnalyser&	MapAnalyser::operator=( const MapAnalyser &other )
{
	this->_map = other._map;
	return *this;
}

void	MapAnalyser::analyseMap( const char* mapPath )
{
	this->readMap(mapPath);
	this->checkCharacters();
}

void	MapAnalyser::readMap( const char* mapPath )
{
	vector2d	tmpMap;
	std::vector<Point> tmpLine;
	char		inputLine[BUF_SIZE];
	size_t		longestLine = 0;

	_mapFileStream.open(mapPath);
	if (!_mapFileStream.good())
		throw std::invalid_argument("Map Path is not readable");
	for (int i = 0; _mapFileStream.getline(inputLine, BUF_SIZE); i++)
	{
		for (int j = 0; inputLine[j]; j++)
		{
			tmpLine.push_back(Point(inputLine[j]));
			tmpLine.back().position.first = j;
			tmpLine.back().position.second = i;
		}
		tmpMap.push_back(tmpLine);
		if (longestLine < tmpLine.size())
			longestLine = tmpLine.size();
		tmpLine.clear();
	}
	for (size_t i = 0; i < tmpMap.size(); i++)
		tmpMap[i].resize(longestLine, Point(' '));
	_map = tmpMap;
}

void	MapAnalyser::checkCharacters( void )
{
	bool	startExists = false;
	bool	arrivalExists = false;

	for (MapAnalyser::vector2d::iterator it = _map.getMap().begin();
			it != _map.getMap().end(); it++)
	{
		checkInvalidCharacters(*it);
		startExists = checkUniqueness(it, 'S', startExists);
		arrivalExists = checkUniqueness(it, 'A', arrivalExists);
	}
	if (!startExists || !arrivalExists)
		throw std::invalid_argument("Map invalid");
}

void	MapAnalyser::printMap( void )
{
	_map.printMap();
}

Map&	MapAnalyser::getMap( void )
{
	return _map;
}

void	MapAnalyser::checkInvalidCharacters( std::vector<Point>& line )
{
	for (std::vector<Point>::iterator it = line.begin(); it != line.end(); it++)
	{
		if (strchr(".XSA ", it->c) == NULL)
			throw std::invalid_argument("Map invalid");
	}
}

bool	MapAnalyser::checkUniqueness( MapAnalyser::vector2d::iterator it,
	char c, bool alreadyExists )
{
	Point point(c);
	int	expectedNumberOfCharacters = alreadyExists ? 0 : 1;
	int	countOnLine = std::count(it->begin(), it->end(), point);

	if (countOnLine > expectedNumberOfCharacters)
		throw std::invalid_argument("Map invalid");
	else if (countOnLine == expectedNumberOfCharacters)
		return true;
	return false;
}
