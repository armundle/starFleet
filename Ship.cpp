#include "Ship.h"
#include "PatternHelper.h"
#include "common.h"
#include <iostream>
#include <algorithm>
#include "Cuboid.h"

Ship::Ship(Cuboid& g) : 
                        _grid(g), _missedMine(false)
{
    _center.x = _grid.getSizeX()/2;
    _center.y = _grid.getSizeY()/2;
    
    _grid.trim();
}

const Position& Ship::getCenter()
{
    return _center;
}

void Ship::fire(const FirePatternStringType& pattern)
{
    _destroyMine(convertPatternToNumVector(pattern));

    _grid.trim();
}

void Ship::move(const MoveType& move)
{
    _updateShipCenter(convertMoveToNum(move));

    _grid.resize(move);
}

void Ship::_updateShipCenter(const Position& p)
{
    //todo:move this to a function
    _center.x += p.x;
    _center.y += p.y;
}

bool Ship::_outOfBounds(int x, int y)
{
    int xBoundL = _center.x - (_grid.getSizeX() -1);
    int xBoundR = _center.x + (_grid.getSizeX() -1);
    int yBoundU = _center.y - (_grid.getSizeY()-1);
    int yBoundD = _center.y + (_grid.getSizeY()-1);
    
    if((x > xBoundR) || (x < xBoundL) || (y > yBoundD) || (y < yBoundU))
    {
        return true;
    }
    
    return false;
}

void Ship::_destroyMine(std::vector<Position> v)
{
    for(int i = 0; i < v.size(); i++)
    {

        int relativeX = _center.x + v[i].x;
        int relativeY = _center.y + v[i].y;
        
        if(_outOfBounds(relativeX, relativeY))
        {
            continue;
        }
        
        _grid.destroyMine(relativeY, relativeX);
    }
}

void Ship::printGrid()
{
    _grid.print();
}

void Ship::drop()
{
    _grid.drop();
}

void Ship::_trim()
{
    _grid.trim();
}

bool Ship::missedMine()
{
    return _grid.mineMissed();
}