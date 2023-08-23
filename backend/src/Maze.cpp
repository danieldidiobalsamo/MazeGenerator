#include "Maze.hpp"

#include <iostream>
#include <stdexcept>

Maze::Maze(int width, int height, Cell entryPos, Cell exitPos)
    : _width(width)
    , _height(height)
    , _entryPos(entryPos)
    , _grid(width, height, entryPos, exitPos)
{
}

Maze::~Maze()
{
}

CellWalls Maze::getCellWalls(Cell coords)
{
    return _grid.getCellWalls(coords);
}

void Maze::visitCell(Cell cell)
{
    _grid.setVisited(cell);
}

void Maze::huntAndKill()
{
    Cell currentCell = _entryPos;

    visitCell(currentCell);

    Cell nextCell;
    bool allCellsTreated = false;
    bool huntMode = false;

    // looping on the whole maze
    do {

        do // looping until a dead end is reached
        {
            if (_grid.isDeadEnd(currentCell)) {
                // launching hunt mode
                huntMode = true;
            } else {
                // choosing an unvisited cell

                do {
                    nextCell = _grid.chooseRandomNeighbors(currentCell);
                } while (_grid.isCellVisited(nextCell));

                visitCell(nextCell);
                _grid.carve(currentCell, nextCell);

                currentCell = nextCell;
            }

        } while (!huntMode);

        // hunt mode
        // consists in searching for an unvisited cell which have at least a visited one
        // and searching row by row

        bool selectedCell = false;
        int row = 0;

        while (row < _height && !selectedCell) {
            int col = 0;

            while (col < _width && !selectedCell) {
                if (_grid.isCellVisited(Cell(row, col))) {
                    // checking if among its neighbors, there is one who is visited

                    auto [visitedNeighbor, chosenNeighbor] = _grid.hasVisitedNeighbor(Cell(row, col));

                    if (visitedNeighbor) {
                        currentCell = Cell(row, col);

                        _grid.carve(currentCell, chosenNeighbor);
                        visitCell(currentCell);
                        selectedCell = true;
                    }
                }
                ++col;
            }

            ++row;
        }

        if (!selectedCell) {
            allCellsTreated = true;
        }

        huntMode = false;
    } while (!allCellsTreated);
}