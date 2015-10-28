#pragma once

#include <vector>
#include <deque>
#include <string>

//todo: there might be a cleaner way to wrap these
typedef std::string Row;
typedef std::deque<char> GridElement;
typedef std::deque< GridElement > GridType;

typedef std::string MoveType;
typedef std::string FirePatternStringType;

static int countMines(GridType& g)
{
    int count = 0;
    int x = g[0].size();
    int y = g.size();

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
