#include "Game.hpp"



int main()
{

    RenderWindow window(VideoMode(500, 500), "Mini-Studio");
    window.setFramerateLimit(60);

    Game jeu;
    jeu.Run(window);

    return 0;
}