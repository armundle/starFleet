#pragma once
//todo:rename this file to make better sense
//todo:this file should go away

#include <vector>
#include <iostream>//todo:remove this
#include <string>
#include "types.h"

//todo: create an unordered map for this.


//helper for now. Might not need it
//todo: simulator class should handle this
static Position createPosition(int x, int y)
{
    return Position(x, y);
}

//todo:move this to ship as a helper function
static std::vector<Position> convertPatternToNumVector(const FirePatternStringType& s)
{
    std::vector<Position> v;

    if(s == "alpha")
    {
        //std::cout << "alpha" << std::endl;
        v.push_back(createPosition(-1, -1));
        v.push_back(createPosition(-1, 1));
        v.push_back(createPosition(1, -1));
        v.push_back(createPosition(1, 1));
        //v.push_back(p);
        return v;
    }

    if(s == "beta")
    {
        //std::cout << "beta" << std::endl;
        v.push_back(createPosition(-1, 0));
        v.push_back(createPosition(0, -1));
        v.push_back(createPosition(0, 1));
        v.push_back(createPosition(1, 0));
        return v;
    }

    if(s == "gamma")
    {
        //std::cout << "gamma" << std::endl;
        v.push_back(createPosition(-1, 0));
        v.push_back(createPosition(0, 0));
        v.push_back(createPosition(1, 0));
        return v;
    }

    if(s == "delta")
    {
        //std::cout << "delta" << std::endl;
        v.push_back(createPosition(0, -1));
        v.push_back(createPosition(0, 0));
        v.push_back(createPosition(0, 1));
        return v;
    }

    //todo: throw error if this doesn't work out
    std::cout << "Error" << std::endl;

    return v;
}

//todo:move this to ship as a helper function
static Position convertMoveToNum(const MoveType& move)
{
    if(move == "north")
    {
        return createPosition(0,1);
    }
    
    if(move == "south")
    {
        return createPosition(0,-1); 
    }
    
    if(move == "east")
    {
        return createPosition(1,0); 
    }
    
    if(move == "west")
    {
        return createPosition(-1,0); 
    }

    std::cout << "Error" << std::endl;

    return createPosition(0,0);
}

//todo: simulator class should handle this
static bool isFireCommand(const FirePatternStringType& s)
{
    if((s == "alpha") || (s == "beta") ||
       (s == "gamma") || (s == "delta"))
    {
        return true;
    }

    else
    {
        return false;
    }
}

//todo: simulator class should handle this
static bool isMoveCommand(const MoveType& s)
{
    if((s == "north") || (s == "south") ||
       (s == "east") || (s == "west"))
    {
        return true;
    }

    else
    {
        return false;
    }
}
