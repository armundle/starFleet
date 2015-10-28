#include "Cuboid.h"

Cuboid::Cuboid(GridType& g) :
                            _grid(g)
{
}

const int Cuboid::getWidth()
{
    return _grid[0].size();  
}

const int Cuboid::getHeight()
{
    return _grid.size();    
}

bool Cuboid::destroyMine(int x, int y)
{
    bool result = false;

    //if a mine was found
    if(_grid[y][x] != '.')
    {
        _grid[y][x] = '.';
        result = true;
    }

    return result;
}