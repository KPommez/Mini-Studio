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
        view();

    }
    vue.reset(FloatRect(0, 0, screenX, screenY));
    vue.zoom(1);

    window.setView(vue);
    window.close();

}

void Game::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            isRunning = false;
        if (event.type == Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
            player.isJumping = false;
        }
    }
}

void Game::update(const float& deltaTime) {

    player.update(deltaTime, window);
    player.Colision(window, deltaTime);
    if (Keyboard::isKeyPressed(Keyboard::J)) {
        isRunning = false;
    }
    player.Colision(window, deltaTime,level.platforms);
}

void Game::draw() {
    window.clear();
    player.draw(window);
    level.drawMap(window);
    window.display();
}

void Game::view() {
    vue.reset(FloatRect(0, 0, screenX, screenY));
    Vector2f position(screenX / 2, screenY / 2);
    position.x = (player.shape.getPosition().x + (128 / 2) - (screenX / 2));
    position.y = (player.shape.getPosition().y + (128 / 2) - (screenY / 2));

    // permet de fixer une limite donc a voir avec les carré noir de Kiliann

    if (position.x < -480) {
        position.x = -480;
    }
    if (position.y < -270) {
        position.y = -270;
    }

    if (position.x > 2000) {
        position.x = 1920;
    }
    if (position.y > 270) {
        position.y = 270;
    }


    vue.reset(FloatRect(position.x, position.y, screenX, screenY));
    vue.zoom(1);



    window.setView(vue);
}