#include "Menu.hpp"

int main()
{
    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), "Steal The Project", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    Menu MiniStudio(window);
    while (window.isOpen()) {
        MiniStudio.start(window);
    }
}