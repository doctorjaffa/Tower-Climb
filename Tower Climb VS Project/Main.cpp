#include <SFML/Graphics.hpp>
#include "Game.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    //Initliase the random number generator.
    srand(time(NULL));

    //Create the game.
    Game gameInstance; //Default constructor.

    //This will not end until the game is over.
    gameInstance.RunGameLoop();

    //If we get here, the loop exited, so the game is over.
    //End the program by returning.
    return 0;
}