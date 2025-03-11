#include "Menu.hpp"

int main()
{
    RenderWindow window(VideoMode(1920, 1080), "Mini-Studio",Style::Fullscreen);
    
    window.setFramerateLimit(60);

    Menu jeu;
    while (window.isOpen()) 
    {
        jeu.start(window);
    }

    return 0;
}