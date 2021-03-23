#ifndef MAZE_GRID_HPP
#define MAZE_GRID_HPP

#include "Cell.hpp"

#include <utility> // pair
#include <random>
#include <time.h>


class MazeGrid
{
	private :

		int _width;
		int _height;

		std::pair<int, int> _entryPos;
		std::pair<int, int> _exitPos;

		Cell **_grid;

		std::default_random_engine _randomEngine;

	public :

		MazeGrid();
		MazeGrid(int width, int height);
		MazeGrid(int width, int height, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool allWallsBuilt);
		MazeGrid(const MazeGrid &m);
		
		~MazeGrid();

		MazeGrid& operator=(const MazeGrid &m);
		
		int carve(std::pair<int, int> src, std::pair<int, int> dest);	
		std::pair<int, int> chooseRandomNeighbors(int row, int col);
		bool isDeadEnd(std::pair<int ,int> cell);
		bool hasVisitedNeighbor(std::pair<int, int> cell, std::pair<int, int> &validNeighbor);
		std::vector<std::pair<int, int>> getNeighbors(std::pair<int, int> cell);

		bool isEmpty();

		Cell& getCell(int row, int col) const;
};

enum CarvingDirection
{
	CARVING_NORTH,
	CARVING_WEST,
	CARVING_SOUTH,
	CARVING_EAST
};

#endif