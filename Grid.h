#pragma once

#include "types.h"

class Grid
{
    public:
    Grid(GridType& g);
    ~Grid(){};

    const int getSizeX();//needed by ship
    const int getSizeY();//needed by ship
    void trim();
    void resize(const MoveType& move);

    int getNumMines();//call only at init; use a successfull fire to update the count
    bool mineMissed();//might not be required
    void print();
    void drop();//might overload to return if a mine missed in the process

    private:
    GridType& _grid;

    bool _missedMine;

    void _addNorth();
    void _addSouth();
    void _addEast();
    void _addWest();
};
