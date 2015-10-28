#pragma once

#include <string>
#include <deque>
#include "types.h"
#include "Ship.h"

class Simulator
{
    public:
        Simulator(std::string fieldFile, std::string scriptFile);
        ~Simulator();

        void showGrid();
        void run();

        bool isComplete();

        int numFires();
        int numMoves();
        
        int minesRemaining();
        bool endOfScript();

    private:
        GridType _g;
        Grid     _grid;
        Cuboid   _cuboid;
        Ship     _ship;

        unsigned int _initMines;
        unsigned int _minesRemaining;
        unsigned int _maxPoints;
        unsigned int _points;
        unsigned int _nFires;
        unsigned int _nMoves;

        bool _endOfScript;
        bool _mineMissed;

        std::deque<std::string> _commands;

        void _readFieldFile(std::string fieldFile);
        void _readScriptFile(std::string scriptFile);

        void _runLine(std::string command);
};

//Implementation

Simulator::Simulator(std::string fieldFile, std::string scriptFile) :
                    _grid(_g),
                    _cuboid(_g),
                    _ship(_cuboid),
                    _initMines(0),
                    _minesRemaining(0),
                    _maxPoints(0),
                    _points(0),
                    _nFires(0),
                    _nMoves(0),
                    _endOfScript(false),
                    _mineMissed(false)
{
    _readFieldFile(fieldFile);
    _readScriptFile(scriptFile);

    _initMines = _countMines();
    _minesRemaining = _initMines;
    _maxPoints = INIT_MULT * _initMines;
    _points = _maxPoints;
}

~Simulator::Simulator()
{
}

void Simulator::_readFieldFile(std::string f)
{
    std::ifstream f(fieldFile);
    std::string row;

    while(fieldFile >> row)
    {
        GridElement element(row.begin(), row.end());
        grid.push_back(element);
    }
}

void Simulator::_readScriptFile(std::string s)
{
    //reading the script file
    std::ifstream scriptFile(s);
    std::string command;
    std::string row;

    while(scriptFile.good() && !scriptFile.eof())
    {
        std::getline(scriptFile, row);
        std::istringstream iss(row);

        //end of file
        if(row.empty())
        {
            break;
        }

        while(iss >> command)
        {
            _commands.push_back(command);
        }
        _commands.push_back("");
    }
}

void Simulator::showGrid()
{
    _grid.print();
}

void Simulator::run()
{
    if(isComplete())
    {
        return;
    }

    std::string command = _commands.front();

    while(command != "" && !_commands.empty())
    {
        //print out each command being executed
        std::cout << command << " ";
        _runLine(command);

        _commands.pop_front();
        command = _commands.front();
    }
    
    //new line for output formatting
    std::cout << std::endl;

    if(!_commands.empty())
    {
        _drop();
    }
    else
    {
        _endOfScript = true;
    }
}

void Simulator::_runLine(std::string command)
{
    if(isFireCommand(command))
    {
        _minesRemaining -= _ship.fire(command);
        _updateFirePenalty();

        _grid.trim();
    }
    else if(isMoveCommand(command))
    {
        _ship.move(command);
        _updateMovePenalty();

        _grid.resize(command);
    }
    //error
}

void Simulator::_updateFirePenalty()
{
    _nFires++;

    /*
    if(_nFires < FIRE_PENATLY_MULT * _initMines)
    {
        _nFires += FIRE_PENALTY_INCR;
    }
    */
}

void Simulator::_updateMovePenalty()
{
    _nMoves++;
    /*
    if(_nMoves < MOVE_PENALTY_MULT * _initMines)
    {
        _nMoves += MOVE_PENALTY_INCR;
    }
    */
}

void Simulator::_drop()
{
    _grid.drop();
    
    if(_grid.mineMissed())
    {
        _mineMissed = true;    
    }
}

bool Simulator::missedMine()
{
    return _grid.mineMissed();
}

bool Simulator::isComplete()
{
    //todo: fill this in.
    if( _mineMissed || _endOfScript || !_minesRemaining)
    {
        return true;
    }

    return false;
}

int Simulator::numFires()
{
    return numFires;
}

int Simulator::numMoves()
{
    return numMoves;
}

int Simulator::minesRemaining()
{
    return _minesRemaining;
}

bool Simulator::endOfScript()
{
    return _endOfScript;
}
