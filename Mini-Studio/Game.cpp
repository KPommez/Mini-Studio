#include "Game.hpp"
    
Game::Game(RenderWindow& window)
{
    m_entityManager = make_shared<EntityManager>();
    deltaTime = 0.f;
    event = {};
    isRunning = true;
    inGame = false;
    screenX = window.getSize().x;
    screenY = window.getSize().y;
    spaceReleases = 0;
}

void Game::Run(RenderWindow& window) {
    inGame = true;

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

        pollEvents(window);
        update(deltaTime, window);
        draw(window);
        view(window);

        if (Keyboard::isKeyPressed(Keyboard::P) && inGame == true)
        {
            inGame = false;
            isRunning = false;
        }
    }
    vue.reset(FloatRect(0, 0, screenX, screenY));
    vue.zoom(1);

    window.clear();
    window.setView(vue);
    //window.close();
}

bool Game::setRunning(bool test)
{
    isRunning = test;
    return isRunning;
}

void Game::pollEvents(RenderWindow& window) {
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

void Game::update(const float& deltaTime, RenderWindow& window) {
    m_entityManager->updateEntities(window, deltaTime);
    player.update(deltaTime, window);
    if (Keyboard::isKeyPressed(Keyboard::J)) {
        isRunning = false;
    }
    player.Colision(window, deltaTime, level.platforms);
}

void Game::draw(RenderWindow& window) {
    window.clear();
    level.drawMap(window);
    player.draw(window);
    m_entityManager->drawEntities(window);
    window.display();
}

void Game::view(RenderWindow& window) {
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