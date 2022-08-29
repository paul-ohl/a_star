#include "Map.hpp"
#include <vector>
#include <fstream>

#pragma once

class MapAnalyser
{
private:

	typedef std::vector<std::vector<Point> > vector2d;

public:

	MapAnalyser( void );
	~MapAnalyser( void );

	void	analyseMap( const char* mapPath );

	Map& getMap( void );

private:

	MapAnalyser(const MapAnalyser &);
	MapAnalyser &operator=(const MapAnalyser &);

	void	readMap( const char* mapPath );
	void	checkCharacters( void );

	bool	checkUniqueness( MapAnalyser::vector2d::iterator it, char c,
				bool alreadyExists );
	void	checkInvalidCharacters( std::vector<Point>& chars );
	void	printMap( void );

	Map				_map;
	std::ifstream	_mapFileStream;

};
