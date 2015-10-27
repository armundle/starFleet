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

void Cuboid::resize(const MoveType& move)
{
    if(move == "north")
    {
        _addNorth();
    }
    else if(move == "south")
    {
        _addSouth();
    }
    else if(move == "east")
    {
        _addEast();
    }
    else if(move == "west")
    {
        _addWest();
    }

    else
    {
        //error
    }
}

void Cuboid::_addNorth()
{
    std::string row(getSizeX(), '.');

    GridElement element(row.begin(), row.end());

    _grid.push_front(element);
    _grid.push_front(element);
}

void Cuboid::_addSouth()
{
    std::string row(getSizeX(), '.');

    GridElement element(row.begin(), row.end());

    _grid.push_back(element);
    _grid.push_back(element);
}

void Cuboid::_addEast()
{
    for(int i = 0; i < getSizeY(); i++)
    {
        _grid[i].push_back('.');
        _grid[i].push_back('.');
    }
}

void Cuboid::_addWest()
{
    for(int i = 0; i < getSizeY(); i++)
    {
        _grid[i].push_front('.');
        _grid[i].push_front('.');
    }
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

void Cuboid::print()
{
    int yBound = getSizeY();
    int xBound = getSizeX();

    for(int i = 0; i < yBound; i++)
    {
        for(int j = 0; j < xBound; j++)
        {
            std::cout << _grid[i][j];
        }
        std::cout << std::endl;
    }
}

void Cuboid::trim()
{
    //Rows
    int x = getSizeX();
    int y = getSizeY();

    bool trim = true;

    while(trim)
    {
        x = getSizeX();
        y = getSizeY();

        if(y < 3)
        {
            break;
        }

        int countRow0 = std::count(_grid[0].begin(), _grid[0].end(), '.');

        int countRow1 = std::count(_grid[getSizeY() -1].begin(),
                            _grid[getSizeY() -1].end(), '.');

        if( (countRow0 == x) && (countRow1 == x))
        {
            _grid.erase(_grid.begin());
            _grid.erase(_grid.end());
        }
        else
        {
            trim = false;
        }
    }

    trim = true;

    //Columns
    while(trim)
    {
        y = getSizeY();
        x = getSizeX();

        if(x < 3)
        {
            break;
        }

        int countCol = 0;


        for(int i = 0; i < y && (x > 2); i++)
        {
            if((_grid[i][0] == '.') && (_grid[i][x - 1] == '.'))
            {
                countCol++;
            }
        }

        if(y == countCol)
        {
            for(int i = 0; i < y && (y > 2); i++)
            {
                _grid[i].erase(_grid[i].begin());
                x = getSizeX();

                _grid[i].erase(_grid[i].begin() + x);
            }
        }
        else
        {
            trim = false;
        }
    }
}

void Cuboid::drop()
{
    int x = getSizeX();
    int y = getSizeY();

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

    //someone else calls this?
    trim();
}

bool Cuboid::mineMissed()
{
    return _missedMine;
}
