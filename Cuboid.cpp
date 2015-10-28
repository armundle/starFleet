#include "Cuboid.h"

Cuboid::Cuboid(GridType& g) :
                            _grid(g)
{
}

int Cuboid::getWidth() const
{
    return _grid[0].size();  
}

int Cuboid::getHeight() const
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