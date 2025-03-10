#include "Game.hpp"


Game::Game() : window(sf::VideoMode::getFullscreenModes().at(0), "Mini-Studio", sf::Style::Fullscreen)
{
    window.setVerticalSyncEnabled(true);
    deltaTime = 0.f;
    event = {};
    isRunning = true;
}

void Game::Run() {

    

    // Chargement des assets
    // Chargement de la map
    level.loadMap();
    // Ajout des menus
    // Appel du dessin du menu

    player.resize(window);

    while (window.isOpen() && isRunning) {
        
        deltaTime = Clock.restart().asSeconds();

        pollEvents();
        update(deltaTime);
        draw();

    }

    window.close();

}

void Game::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            isRunning = false;
        if (event.type == Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
            player.isJumping = false;
            cout << "Released" << endl;
        }
    }
}

void Game::update(const float& deltaTime) {

    player.update(deltaTime, window);
    player.Colision(window, deltaTime);
    if (Keyboard::isKeyPressed(Keyboard::J)) {
        isRunning = false;
    }
}

void Game::draw() {
    window.clear();
    player.draw(window);
    level.drawMap(window);
    window.display();
}