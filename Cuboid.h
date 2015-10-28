#pragma once

#include "types.h"

class Cuboid
{
    public:
    Cuboid(GridType& g);
    ~Cuboid(){};//move this to implementation

    void resize(const MoveType& move);

    //rename these
    const int getSizeX();//needed by ship
    const int getSizeY();//needed by ship

    bool destroyMine(int x, int y);//needed by ship

    private:
    GridType& _grid;
    //todo:add private copy constructors
};
