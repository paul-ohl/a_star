#include <iostream>
#include <cmath>
#include "Point.hpp"

Point::Point( void )
{
	position.first = -1;
	position.second = -1;
	c = 0.0f;
	parent = nullptr;
	score = 0.0f;
}

Point::Point( char character )
{
	position.first = -1;
	position.second = -1;
	parent = nullptr;
	this->c = character;
	cost = 0.0f;
	score = 0.0f;
}

Point::~Point( void ) { return; }

Point::Point( const Point& other )
{
	if (this == &other)
		return;
	*this = other;
}

Point&	Point::operator=( const Point &other )
{
	this->parent = other.parent;
	this->position.first = other.position.first;
	this->position.second = other.position.second;
	this->score = other.score;
	this->cost = other.cost;
	this->c = other.c;
	return *this;
}

bool	Point::operator==( const Point &other )
{
	if (this->c == other.c)
		return true;
	return false;
}

float	Point::calculateDistance( const Point& other )
{
	float x = static_cast<float>(this->position.first)
			- static_cast<float>(other.position.first);
	float y = static_cast<float>(this->position.second)
			- static_cast<float>(other.position.second);
	float distance = std::hypot(x, y);
	return distance;
}

float	Point::calculateDistance( const Point* other )
{
	float x = static_cast<float>(this->position.first)
			- static_cast<float>(other->position.first);
	float y = static_cast<float>(this->position.second)
			- static_cast<float>(other->position.second);
	float distance = std::hypot(x, y);
	return distance;
}

std::ostream &  operator<<( std::ostream & ostr, Point const & instance)
{
	ostr << instance.c;
	return ostr;
}
