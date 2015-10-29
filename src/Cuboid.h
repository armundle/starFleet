#pragma once

#include "types.h"

/* Cuboid class:
 * This class is intended to provide the Ship access to the grid.
 * The ship can only query the dimensions of the grid and destroy a mine at a
 * particular location
 */

class Cuboid
{
    public:
    Cuboid(GridType& g);
    ~Cuboid(){};

    //get the dimensions of the cuboid
    int getWidth() const;
    int getHeight() const;

    //destroy a mine at the given coordinates
    //return true if a mine was destroyed
    bool destroyMine(int x, int y);

    private:
    GridType& _grid;
};
