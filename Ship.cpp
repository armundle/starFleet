#include "Ship.h"

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
    return _destroyMine(_firePatternToPosition(pattern));
}

void Ship::move(const MoveType& move)
{
    _updateShipCenter(_moveToPosition(move));
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

Ship::Position Ship::_createPosition(int x, int y)
{
    return Position(x, y);
}

//todo:replace this with map
std::vector<Ship::Position> Ship::_firePatternToPosition(const FirePatternStringType& s)
{
    std::vector<Position> v;

    if(s == "alpha")
    {
        v.push_back(_createPosition(-1, -1));
        v.push_back(_createPosition(-1, 1));
        v.push_back(_createPosition(1, -1));
        v.push_back(_createPosition(1, 1));
        return v;
    }

    if(s == "beta")
    {
        v.push_back(_createPosition(-1, 0));
        v.push_back(_createPosition(0, -1));
        v.push_back(_createPosition(0, 1));
        v.push_back(_createPosition(1, 0));
        return v;
    }

    if(s == "gamma")
    {
        v.push_back(_createPosition(-1, 0));
        v.push_back(_createPosition(0, 0));
        v.push_back(_createPosition(1, 0));
        return v;
    }

    if(s == "delta")
    {
        v.push_back(_createPosition(0, -1));
        v.push_back(_createPosition(0, 0));
        v.push_back(_createPosition(0, 1));
        return v;
    }

    //todo: throw error if this doesn't work out

    return v;
}

//todo:replace this with a map
Ship::Position Ship::_moveToPosition(const MoveType& move)
{
    if(move == "north")
    {
        return _createPosition(0,1);
    }
    
    if(move == "south")
    {
        return _createPosition(0,-1); 
    }
    
    if(move == "east")
    {
        return _createPosition(1,0); 
    }
    
    if(move == "west")
    {
        return _createPosition(-1,0); 
    }

    //else error

    return _createPosition(0,0);
}