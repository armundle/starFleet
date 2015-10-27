#include <iostream>
#include <string> //todo:Is this needed anymore?
#include <fstream> //todo:is there a subset of this?
#include <sstream>
#include "common.h"
#include "Ship.h"

//todo:debugMode
using std::cout;
using std::endl;

int main(int argc, char** argv)
{
    //todo:debugMode
    //std::cout << "Total arguments: " << argc << std::endl;

    //todo: handle invalid or insufficient arguments
    /*
    for(int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }
    */

    //todo: check for good file
    std::ifstream fieldFile(argv[1]);

    //todo:typedef this
    GridType grid;
    Row row;

    //todo: when does this terminate?
    while(fieldFile >> row)
    {
        //create a vector of char
        //todo: typedef this too
        GridElement element(row.begin(), row.end());
        grid.push_back(element);
    }

    Ship s(grid);

    //reading the script file
    std::ifstream scriptFile(argv[2]);
    std::string command;

    while(scriptFile.good())
    {
        std::getline(scriptFile, row);
        std::istringstream iss(row);
        while(iss >> command)
        {
            //testing if the command was read successfully
            cout << command << " ";
        }
        cout << endl;
    }

    //todo:check the command and perform action accordingly

    //manual testing
    cout << "\n***Grid***\n" << endl;
    s.printGrid();

    //cout << "Vessel Center: " << s.getCenter().x << ", " <<
    //s.getCenter().y << endl;

    //std::string str("alpha");
    //s.fire(str);
    //s.printGrid();

    //s.move("west");
    //s.printGrid();

    //std::cout << s.getCenter().x << ", " << s.getCenter().y << std::endl;
    //std::cout << s.getGridSizeX() << ", " << s.getGridSizeY() << std::endl;

    cout << "\nMoving Down\n\n";
    s.drop();
    s.printGrid();

    cout << "Done!" << endl;
}
