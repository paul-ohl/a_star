#include "Point.hpp"
#include <vector>

#pragma once

class Map
{
public:

	typedef std::vector<std::vector<Point> > vector2d;
	typedef std::pair<size_t, size_t>		coordinates;

public:

	Map( void );
	Map( const char* map_path );
	Map( const Map &other );
	Map &operator=( const Map &other );
	Map &operator=( const vector2d &other );
	std::vector<Point>& operator[]( std::size_t idx );
	~Map( void );

	void		printMap( void );
	vector2d&	getMap( void );

	Point*	startPoint;
	Point*	arrivalPoint;

private:

	vector2d _map;

};
