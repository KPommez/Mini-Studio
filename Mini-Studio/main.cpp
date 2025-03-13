#include "Menu.hpp"

int main()
{
    RenderWindow window;
    window.create(VideoMode(1920, 1080), "Steal The Project", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    Menu MiniStudio (window);
    while (window.isOpen()) {
        MiniStudio.start(window);
    }
    //Game game(window);
    //game.Run(window);
}