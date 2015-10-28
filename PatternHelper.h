#pragma once
//todo:rename this file to make better sense
//todo:this file should go away

#include <vector>
#include <iostream>//todo:remove this
#include <string>
#include "types.h"

//todo: create an unordered map for this.




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
