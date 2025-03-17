#include "Game.hpp"

Game::Game(RenderWindow& window) {
    m_entityManager = make_shared<EntityManager>();
    deltaTime = 0.f;
    event = {};
    isRunning = true;
    inGame = false;
    screenX = window.getSize().x;
    screenY = window.getSize().y;
    spaceReleases = 0;
    index = 0;
    firstParralaxOn = true;
    secondParralaxOn = false;
}

void Game::Run(RenderWindow& window) {
    inGame = true;
    srand(time(NULL));

    // Chargement des assets
    parralaxLevelOne.instanciateLayers(window, "levelOne", 7); // Level 1 has 7 layers in his background
    // Chargement de la map
    level.loadMap(level.allLevels.at(index));
    // Ajout des menus
    // Appel du dessin du menu

    playerSize = { (int)((float)window.getSize().y / 16.f), (int)((float)window.getSize().y / 8.f) };
    player.loadAssets(window);
    player.resize(window);

    shared_ptr<Lampadaire> lampadaire = make_shared<Lampadaire>(Vector2f(500,  900), &player);
    shared_ptr<Petrifeu> petrifeu     = make_shared<Petrifeu>  (Vector2f(500,  900), &player);
    shared_ptr<Eolienne> eolienne     = make_shared<Eolienne>  (Vector2f(1000, 900), &player, window);
    m_entityManager->addEnnemy(lampadaire);
    m_entityManager->addEnnemy(petrifeu);
    m_entityManager->addEnnemy(eolienne);

    view(window);

    while (isRunning) {
        deltaTime = Clock.restart().asSeconds();

        pollEvents(window);
        update(deltaTime, window);
        draw(window);
        view(window);

    }

    window.close();
}

bool Game::setRunning(bool test)
{
    inGame = test;
    return inGame;
}

void Game::pollEvents(RenderWindow& window) {
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
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::P) {
            inGame = !inGame;
        }
    }
}

void Game::update(const float& deltaTime, RenderWindow& window) {
    m_entityManager->updateEntities(window, deltaTime);
    player.Colision(window, deltaTime, level.platforms);
    player.update(deltaTime, window);
}

void Game::view(RenderWindow& window) {
    vue.reset(FloatRect(0, 0, (float)screenX, (float)screenY));
    Vector2f position(screenX / 2.f, screenY / 2.f);
    position.x = (player.playerSprite.getPosition().x + (playerSize.x / 2.f) - (screenX / 2.f));
    position.y = (player.playerSprite.getPosition().y + (playerSize.y / 2.f) - (screenY / 2.f));

    // permet de fixer une limite donc a voir avec les carré noir de Kiliann

    if (position.x < 0) {
        position.x = 0;
    }
    else if (position.x > window.getSize().x * 3.f) {
        position.x = window.getSize().x * 3.f;
    }
    else {
        parralaxLevelOne.moveLayers(deltaTime, window, player);
    }

    if (position.y > window.getSize().y / 2.f) {
        position.y = window.getSize().y / 2.f;
    }
  
    vue.reset(FloatRect(position.x, position.y, (float)screenX, (float)screenY));
    vue.zoom(1);
    window.setView(vue);
}

void Game::draw(RenderWindow& window) {
    window.clear();
    parralaxLevelOne.draw(window);
    level.drawMap(window);
    player.draw(window);
    m_entityManager->drawEntities(window);
    window.display();
}