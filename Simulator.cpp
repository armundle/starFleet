#include "Simulator.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>

Simulator::Simulator(const char* fieldFile, const char *scriptFile) :
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

    _initMines = _grid.countMines();
    _minesRemaining = _initMines;
    _maxPoints = INIT_MULT * _initMines;
    _points = _maxPoints;
}

Simulator::~Simulator()
{
}

void Simulator::_readFieldFile(const char* f)
{
    std::ifstream fieldFile(f);
    std::string row;

    while(fieldFile >> row)
    {
        GridElement element(row.begin(), row.end());
        _g.push_back(element);
    }
}

void Simulator::_readScriptFile(const char* s)
{
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
        
        //new line
        _commands.push_back("");
    }
}

void Simulator::showGrid() const
{
    _grid.print();
}

void Simulator::run()
{
    if(isComplete())
    {
        return;
    }

    std::string command;

    while(!_commands.empty())
    {
        command = _commands.front();
        
        //end of line
        if(command == "")
        {
            _commands.pop_front();
            _drop();
            break;
        }
        
        //print out current command
        std::cout << command << " ";
        
        try
        {
            _runOnce(command);    
        }
        catch (const std::invalid_argument& arg)
        {
            std::cerr<< "\n" << "Invalid command: " << arg.what() << "\n Exiting!" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        
        //on to next command
        _commands.pop_front();
    }

    //new line for output formatting
    std::cout << std::endl;

    if(_commands.empty())
    {
        _endOfScript = true;
    }
}

void Simulator::_runOnce(const std::string& command)
{
    if(_isFireCommand(command))
    {
        _minesRemaining -= _ship.fire(command);
        _updateFirePenalty();

        _grid.trim();
    }
    else if(_isMoveCommand(command))
    {
        _ship.move(command);
        _updateMovePenalty();

        _grid.resize(command);
        _grid.trim();
    }
    else
    {
        throw std::invalid_argument(command);
    }
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

bool Simulator::isComplete() const
{
    //terminating condition for the simulation
    if( _mineMissed || _endOfScript || !_minesRemaining)
    {
        return true;
    }

    return false;
}

int Simulator::numFires() const
{
    return _nFires;
}

int Simulator::numMoves() const
{
    return _nMoves;
}

int Simulator::minesRemaining() const
{
    return _minesRemaining;
}

bool Simulator::endOfScript() const
{
    return _endOfScript;
}

//todo: maybe use a set for this?
bool Simulator::_isFireCommand(const FirePatternStringType& s)
{
    if((s == "alpha") || (s == "beta") ||
       (s == "gamma") || (s == "delta"))
    {
        return true;
    }
    
    return false;
}

//todo:maybe use a set for this?
bool Simulator::_isMoveCommand(const MoveType& s)
{
    if((s == "north") || (s == "south") ||
       (s == "east") || (s == "west"))
    {
        return true;
    }
    
    return false;
}