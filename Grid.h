#pragma once

#include "types.h"

class Grid
{
    public:
    Grid(GridType& g);
    ~Grid(){};
    
    const int getWidth();
    const int getHeight();
    
    void trim();
    void resize(const MoveType& move);

    int countMines();
    bool mineMissed();
    void print();
    void drop();

    private:
    GridType& _grid;

    bool _missedMine;

    void _moveNorth();
    void _moveSouth();
    void _moveEast();
    void _moveWest();
    
    //todo:disallow copy constructors
};