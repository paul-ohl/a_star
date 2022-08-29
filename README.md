# A star algorithm by Paul OHL

## Installation

Run `make` to compile the project, `make clean` to remove everything except the
binary file, `make fclean` to remove everything and `make re` to rebuild the
project.

## How to use

``` bash
./a_star ./path/to/map
```

The program can be tested with `tester.sh`, the script will launch the program
with every map available in `./maps/`.

If you want to add your own tests, just add a file inside the `./maps/` folder.

## Map specifications

The map **must** have:
- A start point, represented by `S`
- An arrival point, represented by `A`
- A continuous walkable path from `S` to `A`

Optionally, you can add:
- Walkable ground, represented by `.`
- Walls, represented by `X`

If those conditions are not met, the program will stop with `fatal error`.

The map does not have to be square, it can have holes (space characters) in the
middle.

## Creation process

This program was developped in 2 days to understand how the A\* algorithm works.

It is developped in C++, with 4 classes:
- Point: represents a point, with a position, a character, and parameters used by the algorithm
- Map: stores the map as a two dimensional vector of `Point` as well as the start and arrival points, stored as `Point*`
- MapAnalyser: fills the `Map` using the file given in `argv[1]`.
- PathFinder: run the A\* algorithm
