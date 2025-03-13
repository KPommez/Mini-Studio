#include "Game.hpp"
    
Game::Game() : window(VideoMode::getDesktopMode(), "Mini-Studio", Style::Fullscreen) {
    m_entityManager = make_shared<EntityManager>();
    window.setVerticalSyncEnabled(true);
    deltaTime = 0.f;
    event = {};
    isRunning = true;
    inGame = false;
    screenX = window.getSize().x;
    screenY = window.getSize().y;
    spaceReleases = 0;
    index = 0;
}

void Game::Run() {
    //Menu menu;
    //menu.start(window);
    inGame = true;
    
    // Chargement des assets
    // Chargement de la map
    level.loadMap(level.allLevels.at(index)); //level.allLevels.at(index)"Assets/map/test_map1.txt"
    // Ajout des menus
    // Appel du dessin du menu

    playerSize = { (int)((float)window.getSize().y / 16.f), (int)((float)window.getSize().y / 8.f) };
    player.loadAssets(window);
    player.resize(window);

    shared_ptr<Lampadaire> test = make_shared<Lampadaire>(Vector2f(500, 900), &player);
    shared_ptr<Petrifeu> test2 = make_shared<Petrifeu>(Vector2f(500, 900), &player);
    m_entityManager->addEnnemy(test);
    m_entityManager->addEnnemy(test2);

    view();

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
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::S && inGame) {
            player.hasPressedS = false;
        }
    }
}

void Game::update(const float& deltaTime) {
    m_entityManager->updateEntities(window, deltaTime);
    player.Colision(window, deltaTime, level.platforms);
    player.update(deltaTime, window);
    for (auto& Plateforme : level.plateformeTest) {
        Plateforme->platUpdate();
    }
}

void Game::view() {
    vue.reset(FloatRect(0, 0, (float)screenX, (float)screenY));
    Vector2f position(screenX / 2.f, screenY / 2.f);
    position.x = (player.playerSprite.getPosition().x + (playerSize.x / 2.f) - (screenX / 2.f));
    position.y = (player.playerSprite.getPosition().y + (playerSize.y / 2.f) - (screenY / 2.f));

    // permet de fixer une limite donc a voir avec les carré noir de Kiliann

    if (position.x < 0) {
        position.x = 0;
    }
    if (position.x > window.getSize().x * 3.f) {
        position.x = window.getSize().x * 3.f;
    }
    if (position.y > window.getSize().y / 2.f) {
        position.y = window.getSize().y / 2.f;
    }

    vue.reset(FloatRect(position.x, position.y, (float)screenX, (float)screenY));
    vue.zoom(1);
    window.setView(vue);
}

void Game::draw() {
    window.clear();
    level.drawMap(window);
    player.draw(window);
    m_entityManager->drawEntities(window);
    window.display();
}