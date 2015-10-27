#pragma once

#include <vector>
#include <deque>
#include <string>

//todo: there might be a cleaner way to wrap these
typedef std::string Row;
typedef std::deque<char> GridElement;
typedef std::deque< GridElement > GridType;

typedef std::string MoveType;

struct Position
{
    int x;
    int y;

    Position(int xIn = 0, int yIn = 0) : x(xIn), y(yIn)
    {
    }
};

typedef struct Position Position;

typedef std::string FirePatternStringType;
typedef std::vector<Position> FirePatternNumType;

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
