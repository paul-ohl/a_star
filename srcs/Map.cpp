#include <iostream>
#include "Map.hpp"

Map::Map( void ) { return; }
Map::~Map( void ) { return; }

Map::Map( const Map& other )
{
	if (this == &other)
		return;
	*this = other;
}

Map&	Map::operator=( const vector2d &other )
{
	this->_map = other;
	return *this;
}

Map&	Map::operator=( const Map &other )
{
	this->_map = other._map;
	return *this;
}

std::vector<Point>& Map::operator[]( std::size_t idx )
{
	return this->_map[idx];
}

void	Map::printMap( void )
{
	for (size_t i = 0; i < _map.size(); i++)
	{
		for (size_t j = 0; j < _map[i].size(); j++)
			std::cout << _map[i][j];
		std::cout << std::endl;
	}
}

Map::vector2d&	Map::getMap( void )
{
	return _map;
}
