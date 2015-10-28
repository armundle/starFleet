#include "Cuboid.h"
#include <iostream>//is this required anymore?
#include <algorithm>//is this required anymore?


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
    //std::cout << "x: " << x << ", y: " << y << std::endl;
    bool result = false;
    
    //std::cout << "height: " << getSizeY() << ", width: " << getSizeX() << std::endl;
    
    //std::cout << _grid[y][x] << std::endl;
    
    //if a mine was found
    if(_grid[y][x] != '.')
    {
        //std::cout << "mine found" << std::endl;
        result = true;
    }
    //todo:move this up in the condition
    _grid[y][x] = '.';

    return result;
}
