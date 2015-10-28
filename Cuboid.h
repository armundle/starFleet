#pragma once

#include "types.h"

class Cuboid
{
    public:
    Cuboid(GridType& g);
    ~Cuboid(){};//move this to implementation

    void resize(const MoveType& move);

    int getWidth() const;
    int getHeight() const;

    bool destroyMine(int x, int y);

    private:
    GridType& _grid;
    //todo:add private copy constructors
};