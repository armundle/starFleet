#pragma once

#include "types.h"

class Cuboid
{
    public:
    Cuboid(GridType& g);
    ~Cuboid(){};

    void resize(const MoveType& move);

    const int getSizeX();//needed by ship
    const int getSizeY();//needed by ship

    bool destroyMine(int x, int y);//needed by ship

    void trim();

    //todo:maybe move this to simple helper functions

    /*
    int getNumMines();//call only at init; use a successfull fire to update the count
    */
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
