#pragma once

#include "Maze.hpp"

#include <string>

class EngineFacade {
private:
    Maze _maze;

public:
    EngineFacade() = delete;
    EngineFacade(const int w, const int h);
    EngineFacade(const int w, const int h, const Cell entryPos, const Cell exitPos);
    EngineFacade(const EngineFacade& e) = default;
    EngineFacade& operator=(const EngineFacade& f) = default;
    ~EngineFacade();

    void initMaze();
    void generateMaze(const std::string& algo);

    // generation algo
    void huntAndKillGeneration();

    vector<CellWalls> getWallsList();
};