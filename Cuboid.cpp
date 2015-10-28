#include "Cuboid.h"
#include <iostream>//is this required anymore?
#include <algorithm>//is this required anymore?


Cuboid::Cuboid(GridType& g) :
                            _grid(g)
{
}

const int Cuboid::getSizeX()
{
    return _grid[0].size();  
}

const int Cuboid::getSizeY()
{
    return _grid.size();    
}

bool Cuboid::destroyMine(int x, int y)
{
    bool result = false;
    
    //if a mine was found
    if(_grid[x][y] != '.')
    {
        result = true;
    }
    //todo:move this up in the condition
    _grid[x][y] = '.';

    return result;
}
