#pragma once

#include "types.h"

/* Grid class:
 * This class provides an interface to manipulate the grid by the simulator.
 */

class Grid
{
    public:
    Grid(GridType& g);
    ~Grid(){};

    //get dimensions of the grid
    int getWidth() const;
    int getHeight() const;

    //crop the grid such that the ship does not see more than 1
    //consecutive row or column of empty mines
    void trim();

    //when the ship moves, resize the so that ship is still attacks
    //the 'center'
    void resize(const MoveType& move);

    //simulate the ship dropping through the cuboid by decrementing value of
    //each mine
    void drop();

    //count the number of mines
    int countMines() const;
    //return true if a mine was missed during after a drop
    bool mineMissed() const;
    //print the grid
    void print() const;

    private:
    GridType& _grid;

    bool _missedMine;

    //helper functions to resize the grid according to the ship's movement
    void _moveNorth();
    void _moveSouth();
    void _moveEast();
    void _moveWest();
};
