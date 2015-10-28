#include <iostream>
#include <string> //todo:Is this needed anymore?
#include <fstream> //todo:is there a subset of this?
#include <sstream>
#include <cstdlib>
#include "PatternHelper.h"
#include "types.h"
#include "Ship.h"
#include "constants.h"
#include "Simulator.h"

//todo:debugMode
using std::cout;
using std::endl;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Please specify 'field' and 'script' files.\nExiting." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    Simulator sim(argv[1], argv[2]);

    //todo: check for good file
    std::ifstream fieldFile(argv[1]);

    //todo:typedef this
    GridType grid;
    Row row;

    //todo: when does this terminate?
    //todo:wrap this in a helper class?
    while(fieldFile >> row)
    {
        //create a vector of char
        //todo: typedef this too
        GridElement element(row.begin(), row.end());
        grid.push_back(element);
    }

    Cuboid c(grid);
    Ship s(c);


    //initialize variables
    unsigned int initMines = countMines(grid);
    unsigned int numMines = initMines;

    unsigned int step = 1;

    unsigned int maxPoints = INIT_MULT*initMines;
    unsigned int points = maxPoints;

    unsigned int nFires = 0;
    unsigned int nMoves = 0;

    bool stepsRemaining = false;

    std::string result("pass");

    //reading the script file
    std::ifstream scriptFile(argv[2]);
    std::string command;

    while(scriptFile.good() && !scriptFile.eof())
    {
        std::getline(scriptFile, row);
        std::istringstream iss(row);

        //end of file
        if(row.empty())
        {
            break;
        }

        if(numMines == 0)
        {
            stepsRemaining = true;
            break;
        }

        //Step
        cout << "\nStep " << step << endl;
        cout << endl;

        //Current minefield.
        s.printGrid();
        cout << endl;

        while(iss >> command)
        {

            //Current command.
            //cout << "command" << endl;
            cout << command << " ";
            //cout << "this was the command" << endl;

            //testing for command type
            if(isFireCommand(command))//todo: use a set instead?
            {
                numMines -= s.fire(command);
                if(nFires < FIRE_PENATLY_MULT * initMines)
                {
                    nFires += FIRE_PENALTY_INCR;
                }
            }
            else if(isMoveCommand(command))//todo:use a set instead?
            {
                s.move(command);
                if(nMoves < MOVE_PENALTY_MULT * initMines)
                {
                    nMoves += MOVE_PENALTY_INCR;
                }
            }
        }

        //If it is not the last line in the script, drop down by 1km.
        if(!scriptFile.eof())
        {
            s.drop();
        }

        //Resulant field
        cout << "\n" << endl;
        s.printGrid();

        if(s.missedMine())
        {
            break;
        }

        step++;
    }

    if(numMines == 0 && !stepsRemaining)
    {
        points = points - nFires - nMoves;
        std::cout << "\npass (" << points << ")" << std::endl;
    }
    else if(numMines == 0 && stepsRemaining)
    {
        std::cout << "\npass (1)" << std::endl;
    }
    else //missed mine or mines remaining
    {
        std::cout << "\nfail (0)" << std::endl;
    }
}
