#include "game.h"

/*
    Making this game using Suraj Sharma Simple 2D Games - Game 1 tutorial
    in hopes it will help me learn C++
*/

int main()
{
    /*std::vector<sf::RectangleShape> enemies;
    std::vector<std::string> strings;
    strings.push_back("Wigga");
    std::cout << strings[0];*/

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
    printf("Game over");
    return 0;
}

// WHY NOT WORKING