#include "Ship.h"
#include "PatternHelper.h"//todo:remove this eventually

Ship::Ship(Cuboid& g) : 
                    _grid(g)
{
}

void Ship::_recalCenter()
{
    _center.x = _grid.getWidth()/2;
    _center.y = _grid.getHeight()/2;
}

int Ship::fire(const FirePatternStringType& pattern)
{
    return _destroyMine(convertPatternToNumVector(pattern));
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

    int xBoundL = _center.x - (_grid.getWidth() -1);
    int xBoundR = _center.x + (_grid.getWidth() -1);
    int yBoundU = _center.y - (_grid.getHeight()-1);
    int yBoundD = _center.y + (_grid.getHeight()-1);

    if((x > xBoundR) || (x < xBoundL) || (y > yBoundD) || (y < yBoundU))
    {
        return true;
    }

    return false;
}

int Ship::_destroyMine(std::vector<Position> v)
{
    _recalCenter();
    
    int destroyedMines = 0;
    
    //cache the number of attacks inflicted by each pattern
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
