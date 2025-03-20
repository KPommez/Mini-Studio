#include "Game.hpp"

Game::Game(RenderWindow& window) {
    deltaTime = 0.f;
    event = {};
    lose = false;
    isRunning = false;
    inGame = false;
    screenX = window.getSize().x;
    screenY = window.getSize().y;
    spaceReleases = 0;
    index = 0;
    firstParralaxOn = true;
    secondParralaxOn = false;
    levelActif = true;
    // Level 2 exclusive
    selectedMirror = -1;
    mirrorSelected = false;
}

void Game::Run(RenderWindow& window) {
    isRunning = true;
    inGame = true;
    srand(time(NULL));

    // Chargement des assets
    parralaxLevelOne.instanciateLayers(window, "levelOne", 8); // Level 1 has 7 layers in his background + 1 for high sky
    // Chargement de la map
    mirrors = {
        Mirror(sf::Vector2f(300.f, 200.f), sf::Vector2f(100.f, 10.f), 45.f),
        Mirror(sf::Vector2f(500.f, 300.f), sf::Vector2f(100.f, 10.f), -45.f),
        Mirror(sf::Vector2f(400.f, 400.f), sf::Vector2f(100.f, 10.f), 0.f)
    };
    lightSource.setPosition(sf::Vector2f(400.f, 100.f)); // Mets une position correcte
    lightSource.setDirection(sf::Vector2f(1.f, 1.f));    // Une direction diagonale
    // Ajout des menus
    // Appel du dessin du menu

    playerSize = { (int)((float)window.getSize().y / 16.f), (int)((float)window.getSize().y / 8.f) };
    player.loadAssets(window);
    player.resize(window);

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
            inGame = false;
            isRunning = false;
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
            inGame = false;
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
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                // Vérifier si un miroir est sélectionné
                for (size_t i = 0; i < mirrors.size(); ++i) {
                    sf::Vector2f mirrorPos = mirrors[i].getPosition();
                    sf::Vector2f mirrorSize = mirrors[i].getSize();

                    // Vérification simplifiée (on pourrait améliorer la précision)
                    if (std::abs(mousePos.x - mirrorPos.x) < mirrorSize.x / 2 &&
                        std::abs(mousePos.y - mirrorPos.y) < mirrorSize.y / 2) {
                        selectedMirror = i;
                        mirrorSelected = true;
                        break;
                    }
                }
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                mirrorSelected = false;
            }
        }

        if (event.type == sf::Event::MouseMoved) {
            if (mirrorSelected && selectedMirror >= 0) {
                // Déplacer le miroir sélectionné
                mirrors[selectedMirror] = Mirror(
                    sf::Vector2f(event.mouseMove.x, event.mouseMove.y),
                    mirrors[selectedMirror].getSize(),
                    mirrors[selectedMirror].getRotation()
                );
            }
        }

        // Rotation des miroirs avec les touches R et F
        if (event.type == sf::Event::KeyPressed) {
            if (selectedMirror >= 0) {
                if (event.key.code == sf::Keyboard::R) {
                    mirrors[selectedMirror].rotate(5.f);
                }
                else if (event.key.code == sf::Keyboard::F) {
                    mirrors[selectedMirror].rotate(-5.f);
                }
            }
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
    lightPath = traceLightPath(lightSource, mirrors, target);
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
    for (size_t i = 0; i < mirrors.size(); ++i) {
        mirrors[i].draw(window);
    }
    target.draw(window);
    // Dessiner le chemin du rayon
    for (auto& ray : lightPath) {
        ray.draw(window);
    }

    // Dessiner la source
    lightSource.draw(window);
    window.display();
}