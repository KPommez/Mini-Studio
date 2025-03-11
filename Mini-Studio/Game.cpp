#include "Game.hpp"
    
Game::Game() : window(sf::VideoMode::getDesktopMode(), "Mini-Studio", sf::Style::Fullscreen) {
    m_entityManager = make_shared<EntityManager>();
    window.setVerticalSyncEnabled(true);
    deltaTime = 0.f;
    event = {};
    isRunning = true;
}

void Game::Run() {
    shared_ptr<Lampadaire> test = make_shared<Lampadaire>(Vector2f(200, 1000), &player);
    m_entityManager->addEnnemy(test);
    
    // Chargement des assets
    // Chargement de la map
    level.loadMap("Assets/map/test_map1.txt");
    // Ajout des menus
    // Appel du dessin du menu

    player.resize(window);

    while (isRunning) {
        deltaTime = Clock.restart().asSeconds();

        pollEvents();
        update(deltaTime);
        draw();
        if (Keyboard::isKeyPressed(Keyboard::J)) {
            isRunning = false;
        }
    }

    window.close();

}

void Game::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::J)) {
            isRunning = false;
        }
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::F) {
            player.isDashing = false;
        }
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space) {
            player.isJumping = false;
        }
    }
}

void Game::update(const float& deltaTime) {
    m_entityManager->updateEntities(window, deltaTime);
    player.update(deltaTime, window);
    player.Colision(window, deltaTime);
}

void Game::draw() {
    window.clear();
    level.drawMap(window);
    player.draw(window);
    m_entityManager->drawEntities(window);
    window.display();
}