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