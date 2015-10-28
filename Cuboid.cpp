#include "Cuboid.h"
#include <iostream>
#include <algorithm>


Cuboid::Cuboid(GridType& g) :
                            _grid(g), _missedMine(false)
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
    if(_grid[x][y] != '.')
    {
        result = true;
    }
    _grid[x][y] = '.';

    return result;
}
