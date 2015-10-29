#pragma once

#include "types.h"

class Cuboid
{
    public:
    Cuboid(GridType& g);
    ~Cuboid(){};//move this to implementation

    //get the dimensions of the cuboid
    int getWidth() const;
    int getHeight() const;

    //destroy a mine at the given coordinates
    //return true if a mine was destroyed
    bool destroyMine(int x, int y);

    private:
    GridType& _grid;
    //todo:add private copy constructors
};
