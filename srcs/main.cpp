#include <exception>
#include <iostream>
#include <stdexcept>
#include "Map.hpp"
#include "MapAnalyser.hpp"
#include "PathFinder.hpp"

int	print_error( const char* error_msg )
{
	std::cerr << "Fatal error: " << error_msg << std::endl;
	return 1;
}

Map	analyseMap( char* mapPath )
{
	MapAnalyser mapAnalyser;

	try {
		mapAnalyser.analyseMap(mapPath);
	} catch (std::exception &e) {
		exit(print_error(e.what()));
	}
	return mapAnalyser.getMap();
}

Map	findAndDrawPath( Map& map )
{
	PathFinder	pathFinder;

	try {
		pathFinder.calculatePath(map);
	} catch (std::exception &e) {
		exit(print_error(e.what()));
	}
	pathFinder.drawPath();
	return pathFinder.getMap();
}

int	main (int argc, char *argv[])
{
	Map			map;

	if (argc != 2)
		return print_error("Wrong number of arguments");
	map = analyseMap(argv[1]);
	map = findAndDrawPath(map);
	map.printMap();
	return 0;
}
