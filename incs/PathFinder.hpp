#include <vector>
#include "Map.hpp"
#include "Point.hpp"

#pragma once

class PathFinder
{
public:

	PathFinder( void );
	~PathFinder( void );

	void	calculatePath( Map& map );
	void	drawPath( void );

	Map		getMap( void );

private:

	PathFinder( const PathFinder & );
	PathFinder &operator=( const PathFinder & );

	void				setStartAndArrivalPoints( void );
	void				aStar( Point *currentPoint );
	std::vector<Point*>	generateNeighbours( Point* currentPoint );
	bool				isArrivalPoint( Point* point );
	void				addToOpenListIfValid( Point* currentPoint, Point* neighbourPoint );
	bool				checkNeighbourValidity( size_t neighbourX, size_t neighbourY );
	Point*				getBestNextPoint( void );

	Map	_map;
	std::vector<Point*> openList;
	std::vector<Point*> closedList;

};
