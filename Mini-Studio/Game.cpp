#include "Game.hpp"
    
Game::Game() : window(sf::VideoMode::getDesktopMode(), "Mini-Studio", sf::Style::Fullscreen) {
    m_entityManager = make_shared<EntityManager>();
    window.setVerticalSyncEnabled(true);
    deltaTime = 0.f;
    event = {};
    isRunning = true;
    inGame = false;
    screenX = window.getSize().x;
    screenY = window.getSize().y;
    spaceReleases = 0;
}

void Game::Run() {
    //Menu menu;
    //menu.start(window);
    inGame = true;
    
    // Chargement des assets
    // Chargement de la map
    level.loadMap("Assets/map/test_map1.txt");
    // Ajout des menus
    // Appel du dessin du menu

    playerSize = { window.getSize().y / 16.f, (window.getSize().y / 8.f) };
    player.resize(window, playerSize);

    shared_ptr<Lampadaire> test = make_shared<Lampadaire>(Vector2f(500, 900), &player);
    m_entityManager->addEnnemy(test);

    vue.reset(FloatRect(0, 0, screenX, screenY));
    vue.zoom(1);
    view();
    window.setView(vue);

    while (isRunning) {
        deltaTime = Clock.restart().asSeconds();

        pollEvents();
        update(deltaTime);
        draw();
        view();

    }
    
    window.close();

}

void Game::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::J)) {
            isRunning = false;
        }
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::F && inGame) {
            player.isDashing = false;
        }
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space && inGame) {
            player.isJumping = false;
        }
    }
}

void Game::update(const float& deltaTime) {
    m_entityManager->updateEntities(window, deltaTime);
    player.Colision(window, deltaTime, level.platforms);
    player.update(deltaTime, window);
    if (Keyboard::isKeyPressed(Keyboard::J)) {
        isRunning = false;
    }
}

void Game::draw() {
    window.clear();
    level.drawMap(window);
    player.draw(window);
    m_entityManager->drawEntities(window);
    window.display();
}

void Game::view() {
    vue.reset(FloatRect(0, 0, screenX, screenY));
    Vector2f position(screenX / 2, screenY / 2);
    position.x = (player.shape.getPosition().x + (playerSize.x / 2) - (screenX / 2));
    position.y = (player.shape.getPosition().y + (playerSize.y / 2) - (screenY / 2));

    // permet de fixer une limite donc a voir avec les carré noir de Kiliann

    if (position.x < 0) {
        position.x = 0;
    }
    if (position.x > window.getSize().x) {
        position.x = window.getSize().x;
    }
    if (position.y > 0) {
        position.y = 0;
    }

    vue.reset(FloatRect(position.x, position.y, screenX, screenY));
    vue.zoom(1);
    window.setView(vue);
}