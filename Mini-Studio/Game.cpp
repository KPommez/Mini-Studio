#include "Game.hpp"

//WindowConfig* windowConfigs = WindowConfig::getInstance();

Game::Game()
{
}

void Game::Run(RenderWindow& window) {
    

    RectangleShape joueur(Vector2f(40, 40));
    joueur.setPosition(100, 100);
    joueur.setFillColor(Color(0, 255, 0));


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            joueur.move(0, -1);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            joueur.move(0, 1);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            joueur.move(1, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            joueur.move(-1, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::J)) {
            window.close();
        }



        window.clear();
        window.draw(joueur);

        window.display();
    }
}

MenuManager* Game::createMenu(sf::RenderWindow& window)
{
    return new MenuManager;
}
