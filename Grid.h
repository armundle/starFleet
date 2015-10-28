#pragma once

#include "types.h"

class Grid
{
    public:
    Grid(GridType& g);
    ~Grid(){};
    
    //todo:better name:
    //getWidth
    //getHeight
    const int getSizeX();//needed by ship
    const int getSizeY();//needed by ship
    
    void trim();
    void resize(const MoveType& move);

    int countMines();//call only at init; use a successfull fire to update the count
    bool mineMissed();//might not be required
    void print();
    void drop();//might overload to return if a mine missed in the process

    private:
    GridType& _grid;

    bool _missedMine;

    void _moveNorth();
    void _moveSouth();
    void _moveEast();
    void _moveWest();
    
    //todo:disallow copy constructors
};
