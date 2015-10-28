#pragma once

#include "types.h"

class Grid
{
    public:
    Grid(GridType& g);
    ~Grid(){};

    int getWidth() const;
    int getHeight() const;

    void trim();
    void resize(const MoveType& move);

    int countMines() const;
    bool mineMissed() const;
    void print() const;
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
