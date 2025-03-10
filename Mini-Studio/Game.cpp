#include "Game.hpp"

Game::Game() : window(sf::VideoMode::getFullscreenModes().at(0), "Mini-Studio", sf::Style::Fullscreen)
{
    window.setFramerateLimit(144);
    deltaTime = 0.f;
    event = {};
    isRunning = true;
}

void Game::Run() {

    // Chargement des assets
    // Chargement de la map
    // Ajout des menus
    // Appel du dessin du menu

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
    }
}

void Game::update(const float& deltaTime) {

    player.update(deltaTime, window);

    if (Keyboard::isKeyPressed(Keyboard::J)) {
        isRunning = false;
    }
}

void Game::draw() {
    window.clear();
    player.draw(window);
    window.display();
}