#pragma once
//todo:rename this file to make better sense

#include <vector>
#include <iostream>
#include <string>
#include "common.h"

//todo: create an unordered map for this.


//helper for now. Might not need it
Position createPosition(int x, int y)
{
    return Position(x, y);
}


std::vector<Position> convertPatternToNumVector(const FirePatternStringType& s)
{
    std::vector<Position> v;

    if(s == "alpha")
    {
        std::cout << "alpha" << std::endl;
        v.push_back(createPosition(-1, -1));
        v.push_back(createPosition(-1, 1));
        v.push_back(createPosition(1, -1));
        v.push_back(createPosition(1, 1));
        //v.push_back(p);
        return v;
    }

    if(s == "beta")
    {
        std::cout << "beta" << std::endl;

        v.push_back(createPosition(-1, 0));
        v.push_back(createPosition(0, -1));
        v.push_back(createPosition(0, 1));
        v.push_back(createPosition(1, 0));
        return v;
    }

    if(s == "gamma")
    {
        std::cout << "gamma" << std::endl;
        v.push_back(createPosition(-1, 0));
        v.push_back(createPosition(0, 0));
        v.push_back(createPosition(1, 0));
        return v;
    }

    if(s == "delta")
    {
        std::cout << "delta" << std::endl;
        v.push_back(createPosition(0, -1));
        v.push_back(createPosition(0, 0));
        v.push_back(createPosition(0, 1));
        return v;
    }

    //todo: throw error if this doesn't work out
    std::cout << "Error" << std::endl;

    return v;
}

Position convertMoveToNum(const MoveType& move)
{
    if(move == "north")
    {
        return createPosition(0,1);
    }

    std::cout << "Error" << std::endl;

    return createPosition(0,0);
}
