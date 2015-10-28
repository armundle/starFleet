#include "Ship.h"
#include "PatternHelper.h"//todo:remove this eventually
#include <iostream>//todo:remove this
#include <algorithm>//todo:remove this

Ship::Ship(Cuboid& g) : 
                        _grid(g)
{
}

void Ship::_recalCenter()
{
    _center.x = _grid.getSizeX()/2;
    _center.y = _grid.getSizeY()/2;
}

//todo:make this private?
const Position& Ship::getCenter()
{
    return _center;
}

int Ship::fire(const FirePatternStringType& pattern)
{
    int destroyedMines =
    _destroyMine(convertPatternToNumVector(pattern));

    return destroyedMines;
}

void Ship::move(const MoveType& move)
{
    _updateShipCenter(convertMoveToNum(move));
}

void Ship::_updateShipCenter(const Position& p)
{
    //todo:move this to a function
    _recalCenter();
    _center.x += p.x;
    _center.y += p.y;
}

bool Ship::_outOfBounds(int x, int y)
{
    _recalCenter();

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

int Ship::_destroyMine(std::vector<Position> v)
{
    int destroyedMines = 0;
    int numAttacks = v.size();
    
    for(int i = 0; i < numAttacks; i++)
    {
        int relativeX = _center.x + v[i].x;
        int relativeY = _center.y + v[i].y;

        if(_outOfBounds(relativeX, relativeY))
        {
            continue;
        }

        if(_grid.destroyMine(relativeX, relativeY))
        {
            destroyedMines++;
        }
    }

    return destroyedMines;
}
