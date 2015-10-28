#include "Grid.h"
#include <iostream>
#include <algorithm>


Grid::Grid(GridType& g) :
                            _grid(g), _missedMine(false)
{
}

const int Grid::getSizeX()
{
    return _grid[0].size();  
}

const int Grid::getSizeY()
{
    return _grid.size();    
}

void Grid::resize(const MoveType& move)
{
    if(move == "north")
    {
        _moveNorth();
    }
    else if(move == "south")
    {
        _moveSouth();
    }
    else if(move == "east")
    {
        _moveEast();
    }
    else if(move == "west")
    {
        _moveWest();
    }
    else
    {
        //error
    }
}

void Grid::_moveNorth()
{
    std::string row(getSizeX(), '.');

    GridElement element(row.begin(), row.end());

    _grid.push_front(element);
    _grid.push_front(element);
}

void Grid::_moveSouth()
{
    std::string row(getSizeX(), '.');

    GridElement element(row.begin(), row.end());

    _grid.push_back(element);
    _grid.push_back(element);
}

void Grid::_moveEast()
{
    //todo: create a row of size 2 and push back that
    for(int i = 0; i < getSizeY(); i++)
    {
        _grid[i].push_back('.');
        _grid[i].push_back('.');
    }
}

void Grid::_moveWest()
{
    for(int i = 0; i < getSizeY(); i++)
    {
        _grid[i].push_front('.');
        _grid[i].push_front('.');
    }
}

void Grid::print()
{
    //todo:rename
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

void Grid::trim()
{
    //Cache the width and height
    //todo:better names
    int x = getSizeX();
    int y = getSizeY();
    
    //Iterative trim until no more 'extra' rows remain.
    bool trim = true;

    //Rows
    while(trim)
    {
        //update after each trim
        //todo:move to the bottom of the loop
        x = getSizeX();
        y = getSizeY();
    
        //Don't trim if width is just 1
        if(y < 3)
        {
            break;
        }
        
        //count empty fields in top row
        int countRow0 = std::count(_grid[0].begin(), _grid[0].end(), '.');

        //count empty fields in bottom row
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

    //Iterative trim until no more 'extra' columns remain.
    //Re-init
    trim = true;

    //Columns
    while(trim)
    {
        //update after each trim
        //todo:move to the bottom of the loop
        y = getSizeY();
        x = getSizeX();

        //Don't trim if width is 1.
        if(x < 3)
        {
            break;
        }
    
        //todo:better name
        int countCol = 0;

        //count empty fields along first and last column
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

void Grid::drop()
{
    //cache the height and width
    int x = getSizeX();
    int y = getSizeY();

    //todo:remove this
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
                //field already clear
                totalField--;
                continue;
            }
            else if(_grid[i][j] == 'a')
            {
                //missed mine!
                _grid[i][j] = '*';
                _missedMine = true;
            }
            else if(_grid[i][j] == 'A')
            {
                //jump
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

bool Grid::mineMissed()
{
    return _missedMine;
}

int Grid::countMines()
{

    int count = 0;
    int x = getSizeX();
    int y = getSizeY();

    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            if(g[i][j] != '.')
            {
                count++;
            }
        }
    }

    return count;
}