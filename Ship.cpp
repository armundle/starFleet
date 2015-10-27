#include "Ship.h"
#include "PatternHelper.h"
#include "common.h"
#include <iostream>

Ship::Ship(GridType& g) : 
                        _grid(g)
{
    _center.x = getGridSizeX()/2;
    _center.y = getGridSizeY()/2;
}

const GridType& Ship::getGrid()
{
    return _grid;
}

const std::size_t Ship::getGridSizeX()
{
    //check for boundary
    return _grid[0].size();
}

const std::size_t Ship::getGridSizeY()
{
    return _grid.size();
}

const Position& Ship::getCenter()
{
    return _center;
}

void Ship::fire(const FirePatternStringType& pattern)
{
    /*
    for(int i = 0; i < 1; i++)
    {
    */
    //Position p;
    //p.x = -1;
    //p.y = 1;
    //    _destroyMine(p);
    /*
    }
    */
    _destroyMine(convertPatternToNumVector(pattern));

    //createVectorofPositions();
}

void Ship::move(const MoveType& move)
{
    _updateShipCenter(convertMoveToNum(move));
    //_resizeGrid(convertMoveToEnum(move));
    _resizeGrid(move);
}

void Ship::_updateShipCenter(const Position& p)
{
    //todo:move this to a function
    _center.x += p.x;
    _center.y += p.y;
}


void Ship::_resizeGrid(const MoveType& move)
{
    //todo:don't use the direct string. Too brittle
    //todo:refactor this. It's ugly
    //todo:handle exceptions
    if(move == "north")
    {
        //std::cout << "moving north" << std::endl;
        std::string row(getGridSizeX(), '.');
        GridElement element(row.begin(), row.end());
        //std::cout << "gridSizeX" << getGridSizeX() << std::endl;
        //std::cout << element.size() << std::endl;
        _grid.push_front(element);
        _grid.push_front(element);
    }

    if(move == "south")
    {
        //std::cout << "moving south" << std::endl;
        std::string row(getGridSizeX(), '.');
        GridElement element(row.begin(), row.end());
        //std::cout << "gridSizeX" << getGridSizeX() << std::endl;
        //std::cout << element.size() << std::endl;
        _grid.push_back(element);
        _grid.push_back(element);
    }

    if(move == "east")
    {
        for(int i = 0; i < getGridSizeY(); i++)
        {
            _grid[i].push_back('.');
            _grid[i].push_back('.');
        }
    }

    if(move == "west")
    {
        for(int i = 0; i < getGridSizeY(); i++)
        {
            _grid[i].push_front('.');
            _grid[i].push_front('.');
        }
    }
}

bool Ship::_outOfBounds(int x, int y)
{
    int xBoundL = _center.x - (getGridSizeX() -1);
    int xBoundR = _center.x + (getGridSizeX() -1);
    int yBoundU = _center.y - (getGridSizeY()-1);
    int yBoundD = _center.y + (getGridSizeY()-1);
    
    if((x > xBoundR) || (x < xBoundL) || (y > yBoundD) || (y < yBoundU))
    {
        return true;
    }
    
    return false;
}

void Ship::_destroyMine(std::vector<Position> v)
{
    //std::cout << "x: " << x << ", y: " << y << std::endl;
    
    //std::cout << "destroying grid" << std::endl;
    for(int i = 0; i < v.size(); i++)
    {
        //std::cout <<  v[i].x << " " << v[i].y << std::endl;

        int relativeX = _center.x + v[i].x;
        int relativeY = _center.y + v[i].y;
        
        if(_outOfBounds(relativeX, relativeY))
        {
            continue;
        }
        
        //std::cout << relativeX << " , " << relativeY << std::endl;
        //std::cout << _grid[relativeY][relativeX] << std::endl;
        _grid[relativeY][relativeX] = '.';
    }
    //std::cout << "destroyed!" << std::endl;
}

void Ship::printGrid()
{
    for(int i = 0; i < getGridSizeY(); i++)
    {
        for(int j = 0; j < getGridSizeX(); j++)
        {
            std::cout << getGrid()[i][j];
        }
        std::cout << std::endl;
    }
}

void Ship::drop()
{
    int x = getGridSizeX();
    int y = getGridSizeY();
    
    int totalField = x*y;

    //todo:make these class members
    int clearedField = false;
    bool missedMine = false;
    
    //todo: is there an elegant way?
    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            if(_grid[i][j] == '.')
            {
                totalField--;
                continue;
            }
            else if(_grid[i][j] == 'a')
            {
                _grid[i][j] = '*';
                missedMine = true;
            }
            else if(_grid[i][j] == 'A')
            {
                _grid[i][j] = 'z';
            }
            else
            {
                _grid[i][j] -= 1;
            }
        }
    }
    
    if(totalField == 0)
    {
        clearedField = true;
    }
}