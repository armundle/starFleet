#include "Ship.h"
#include "PatternHelper.h"
#include "common.h"
#include <iostream>
#include <algorithm>

Ship::Ship(GridType& g) : 
                        _grid(g), _missedMine(false)
{
    _center.x = getGridSizeX()/2;
    _center.y = getGridSizeY()/2;
    
    _trim();
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
    _trim();
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
        //std::cout << "gridSizeY " << getGridSizeY() << std::endl;
        //std::cout << element.size() << std::endl;
        _grid.push_front(element);
        _grid.push_front(element);
        //std::cout << "gridSizeY " << getGridSizeY() << std::endl;

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
        
        //std::cout << _center.x << " , " << _center.y << std::endl;
        //std::cout << _grid[relativeY][relativeX] << std::endl;
        _grid[relativeY][relativeX] = '.';
    }
    //std::cout << "destroyed!" << std::endl;
    
    //_trim();
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
                _missedMine = true;
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
    
    _trim();
}

void Ship::_trim()
{
    //std::cout << "trim..." << std::endl;
    //Top
    int x = getGridSizeX();
    int y = getGridSizeY();
    
    //std::cout << "x size: " << x << ", y size: " << y << std::endl;
    bool trim = true;
    
    while(trim)
    {
        x = getGridSizeX();
        y = getGridSizeY();
        
        if(y < 3)
        {
            //std::cout << "cannot trim along y" << std::endl;
            break;
        }
        int x0 = std::count(_grid[0].begin(), _grid[0].end(), '.');
        //int x1 = std::count(_grid[1].begin(), _grid[1].end(), '.');
        int x2 = std::count(_grid[getGridSizeY() -1].begin(),
                            _grid[getGridSizeY() -1].end(), '.');
        //int x3 = std::count(_grid[getGridSizeY() -1].begin(),
        //                    _grid[getGridSizeY() -1].end(), '.');                   
        
        //std::cout << "x size: " << x << " x0: " << x0 << " x1: " << x1 << std::endl;
    
        //std::cout << "x size: " << x << ", y size: " << y << std::endl;
    
        if( (x0 == x) && (x2 == x) /*&& (x2 == x) && (x3 == x)*/)
        {
            //std::cout << getGridSizeY() << std::endl;
            _grid.erase(_grid.begin());
            //std::cout << getGridSizeY() << std::endl;
            _grid.erase(_grid.end());
            //std::cout << getGridSizeY() << std::endl;
    
            //printGrid();
        }
        else
        {
            trim = false;
        } 
    }

    trim = true;
    
    while(trim)
    {
        y = getGridSizeY();
        x = getGridSizeX();
        
        if(x < 3)
        {
            //std::cout << "cannot trim along x" << std::endl;
            break;
        }
        int yCount = 0;

        
        for(int i = 0; i < y && (x > 2); i++)
        {
            if((_grid[i][0] == '.') && (_grid[i][x - 1] == '.'))
            {
                yCount++;
            }
        }
        
        if(y == yCount)
        {
            for(int i = 0; i < y && (y > 2); i++)
            {
                //std::cout << "x: " << getGridSizeX() << std::endl;
                _grid[i].erase(_grid[i].begin());
                x = getGridSizeX();
                
                //std::cout << "x: " << getGridSizeX() << std::endl;
    
                _grid[i].erase(_grid[i].begin() + x);
                //std::cout << "x: " << getGridSizeX() << std::endl;
            }
        }
        else
        {
            trim = false;
        }
    }
    
    _center.x = getGridSizeX()/2;
    _center.y = getGridSizeY()/2;
}

bool Ship::missedMine()
{
    return _missedMine;
}