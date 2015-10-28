#include "Grid.h"
#include <iostream>
#include <algorithm>


Grid::Grid(GridType& g) :
                        _grid(g), _missedMine(false)
{
}

const int Grid::getWidth()
{
    return _grid[0].size();  
}

const int Grid::getHeight()
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
    std::string row(getWidth(), '.');

    GridElement element(row.begin(), row.end());

    _grid.push_front(element);
    _grid.push_front(element);
}

void Grid::_moveSouth()
{
    std::string row(getWidth(), '.');

    GridElement element(row.begin(), row.end());

    _grid.push_back(element);
    _grid.push_back(element);
}

void Grid::_moveEast()
{
    //todo: create a row of size 2 and push back that
    for(int i = 0; i < getHeight(); i++)
    {
        _grid[i].push_back('.');
        _grid[i].push_back('.');
    }
}

void Grid::_moveWest()
{
    for(int i = 0; i < getHeight(); i++)
    {
        //todo: create a row of size 2 and push back that
        _grid[i].push_front('.');
        _grid[i].push_front('.');
    }
}

void Grid::print()
{
    //todo:rename
    int h = getHeight();
    int w = getWidth();

    for(int i = 0; i <h; i++)
    {
        for(int j = 0; j < w; j++)
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
    int w = getWidth();
    int h = getHeight();
    
    //Iterative trim until no more 'extra' rows remain.
    bool trim = true;

    //Rows
    while(trim)
    {
        //Don't trim if height is just 1
        if(h < 3)
        {
            break;
        }
        
        //count empty fields in top row
        int countFirstRow = std::count(_grid[0].begin(), _grid[0].end(), '.');

        //count empty fields in bottom row
        int countLastRow = std::count(_grid[getHeight() -1].begin(),
                            _grid[getHeight() -1].end(), '.');
        
        if( (countFirstRow == w) && (countLastRow == w))
        {
            _grid.erase(_grid.begin());
            _grid.erase(_grid.end());
            
            //update the dimensions after each successfull trim
            w = getWidth();
            h = getHeight();
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
        //Don't trim if width is 1.
        if(w < 3)
        {
            break;
        }
    
        //todo:better name
        int countEmptyColumnFields = 0;

        //count empty fields along first and last column
        for(int i = 0; i < h && (w > 2); i++)
        {
            if((_grid[i][0] == '.') && (_grid[i][w - 1] == '.'))
            {
                countEmptyColumnFields++;
            }
        }

        if(countEmptyColumnFields == h)
        {
            for(int i = 0; i < h; i++)
            {
                //erase the first column
                _grid[i].erase(_grid[i].begin());
                
                //update the width
                w = getWidth();
                
                //erase the last column
                _grid[i].erase(_grid[i].begin() + w);
            }
            
            //update the dimensions after each successfull trim
            h = getHeight();
            w = getWidth();
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
    int w = getWidth();
    int h = getHeight();

    //todo: is there an elegant way?
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(_grid[i][j] == '.')
            {
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
}

bool Grid::mineMissed()
{
    return _missedMine;
}

int Grid::countMines()
{
    //todo:a better way to count?
    int count = 0;
    int w = getWidth();
    int h = getHeight();

    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            if(_grid[i][j] != '.')
            {
                count++;
            }
        }
    }

    return count;
}