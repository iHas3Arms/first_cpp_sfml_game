#include "game.h"

/*
    Making this game using Suraj Sharma Simple 2D Games - Game 1 tutorial
    in hopes it will help me learn C++
*/

int main()
{
    // Init Game Engine
    Game game;

    // Game loop
    while (game.running())
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    return 0;
}