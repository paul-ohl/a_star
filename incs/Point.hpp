#include <vector>

#pragma once

struct Point
{
	typedef std::pair<size_t, size_t>		coordinates;

	Point( void );
	Point( char c );
	~Point( void );
	Point( const Point & );
	Point &operator=( const Point & );
	bool operator==( const Point & );

	float	calculateDistance( const Point& other );
	float	calculateDistance( const Point* other );

	coordinates	position;
	float		score;
	float		cost;
	Point*		parent;
	char		c;

};

std::ostream    &operator<<( std::ostream &ostr, const Point &instance );
