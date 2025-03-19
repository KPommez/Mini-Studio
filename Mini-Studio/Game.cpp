#include "Game.hpp"

Game::Game(RenderWindow& window) {
	m_entityManager = make_shared<EntityManager>();
    deltaTime = 0.f;
    event = {};
    isRunning = false;
    inGame = false;
    screenX = window.getSize().x;
    screenY = window.getSize().y;
    spaceReleases = 0;
    index = 0;
    firstParralaxOn = true;
    secondParralaxOn = false;
    levelActif = true;
}

void Game::Run(RenderWindow& window) {
    isRunning = true;
    inGame = true;
    srand(time(NULL));

    // Chargement des assets
    parralaxLevelOne.instanciateLayers(window, "levelOne", 7); // Level 1 has 7 layers in his background
    // Chargement de la map
    
    // Ajout des menus
    // Appel du dessin du menu

    playerSize = { (int)((float)window.getSize().y / 16.f), (int)((float)window.getSize().y / 8.f) };
    player.loadAssets(window);
    //player.resize(window);

    m_entityManager->deleteAllEnnemy();


    level.loadMap(level.allLevels.at(index), &player, window, &parralaxLevelOne);

    view(window);

    while (isRunning) {
        deltaTime = Clock.restart().asSeconds();

        pollEvents(window);
        update(deltaTime, window);
        draw(window);
        view(window);
        if (player.hitcount >= 5)
        {
            isRunning = 0;
            lose = true;
        }
    }

    window.clear();
    levelActif = false;
    view(window);
    

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
        if ((event.type == Event::KeyReleased && event.key.code == Keyboard::LShift && inGame)) {
            player.isDashing = false;
        }
        if ((event.type == Event::KeyReleased && event.key.code == Keyboard::S && inGame) || (Joystick::getAxisPosition(0, Joystick::Y) < 50)) {
            player.hasPressedS = false;
        }
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::P) {
            inGame = !inGame;
        }
    }
}

bool Game::getRunning()
{
    return isRunning;
}

void Game::update(const float& deltaTime, RenderWindow& window) {
    level.m_entityManager->updateEntities(window, deltaTime);
    player.Colision(window, deltaTime, level.platforms, level.plateformeTest);
    player.update(deltaTime, window);
    parralaxLevelOne.moveLayers(deltaTime, window, player);
    for (auto& Plateforme : level.plateformeTest) {
        Plateforme->platUpdate(deltaTime);
    }
    if (player.playerSprite.getGlobalBounds().intersects(level.endLevel.getGlobalBounds())) {
        index += 1;
        levelActif = false;
        level.plateformeTest.clear();
        level.platforms.clear();
        level.m_entityManager->deleteAllEnnemy();
        player.playerSprite.setPosition(500, 500);
        level.loadMap(level.allLevels.at(index), &player, window, &parralaxLevelOne);
    }
    if (player.playerSprite.getGlobalBounds().intersects(level.end.getGlobalBounds())) {
        isRunning = 0;
        //mettre les transition
    }
}

void Game::view(RenderWindow& window) {
    if (levelActif) {
        vue.reset(FloatRect(0, 0, (float)screenX, (float)screenY));
        Vector2f position(screenX / 2.f, screenY / 2.f);
        position.x = (player.playerSprite.getPosition().x + (playerSize.x / 2.f) - (screenX / 2.f));
        position.y = (player.playerSprite.getPosition().y + (playerSize.y / 2.f) - (screenY / 2.f));

        // permet de fixer une limite donc a voir avec les carré noir de Kiliann

        if (position.x < 0) {
            position.x = 0;
        }
        else if (position.x > window.getSize().x * 50.f) { //bloquer joueur vue
            position.x = window.getSize().x * 50.f;
        }
        else {

        }

        if (position.y > 0) {
            position.y = 0;
        }

        vue.reset(FloatRect(position.x, position.y, (float)screenX, (float)screenY));
        vue.zoom(1);
        window.setView(vue);
    }
    else {
        vue.reset(FloatRect(0, 0, (float)screenX, (float)screenY));
        vue.zoom(1);

        window.setView(vue);
        //metre pour modif le joueur
    }
}

void Game::draw(RenderWindow& window) {
    window.clear();
    if (index == 0) {
        parralaxLevelOne.draw(window);
    }
    if (index == 1) {
        //parralaxLevelTwo.draw(window);
    }
    level.drawMap(window);
    player.draw(window);
    window.display();
}
