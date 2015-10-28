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

    private:
    GridType& _grid;
};
