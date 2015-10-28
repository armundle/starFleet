#include <iostream>
#include <cstdlib>
#include "constants.h"
#include "Simulator.h"

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Please specify 'field' and 'script' files.\nExiting!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    Simulator sim(argv[1], argv[2]);

    unsigned int step = 1;
    
    while(!sim.isComplete())
    {
        std::cout << "\nStep " << step << std::endl;

        sim.showGrid();
        
        sim.run();
        
        sim.showGrid();

        step++;
    }

    /*
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
    */
}