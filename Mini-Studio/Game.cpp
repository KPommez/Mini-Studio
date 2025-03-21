#include "Game.hpp"
#include "LightRay.hpp"

namespace {
    Ray ray;
    std::vector<Mirror> mirrors;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> allSegments;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> raySegments;
    const int MAX_REFLECTIONS = 15;
}

Game::Game(RenderWindow& window) {
    winScreenTexture.loadFromFile("Assets/End/win.png");
    lostScreenTexture.loadFromFile("Assets/End/lose.png");
    winScreen.setTexture(winScreenTexture);
    winScreen.setScale((float)window.getSize().x / winScreenTexture.getSize().x, (float)window.getSize().y / winScreenTexture.getSize().y);
    lostScreen.setTexture(lostScreenTexture);
    lostScreen.setScale((float)window.getSize().x / lostScreenTexture.getSize().x, (float)window.getSize().y / lostScreenTexture.getSize().y);
    deltaTime = 0.f;
    event = {};
    lose = false;
    isRunning = false;
    inGame = false;
    screenX = window.getSize().x;
    screenY = window.getSize().y;
    spaceReleases = 0;
    index = 0;
    levelActif = true;
    isMousePressed = false;
    isRectangleSelected = false;
    floorLevel = (float)window.getSize().y * (9.f / 10.f);
    hasWon = false;
    hasLost = false;
}

void Game::Run(RenderWindow& window) {
    isRunning = true;
    inGame = true;
    srand(static_cast<unsigned int>(time(NULL)));
    levelActif = true;

    // Chargement des assets
    ray.create(sf::Vector2f(window.getSize().x / 3.f, window.getSize().y / 4.f - 50.f), sf::Vector2f(0.25f, 1.f));
    parralaxLevelOne.instanciateLayers(window, "levelOne", 8); // Level 1 has 7 layers in his background + 1 for high sky
    // Chargement de la map
    levelTwo.scaleSprites(window);
    levelTwo.endSolarPanel.create(Vector2f(window.getSize().x - 300.f, window.getSize().y * (9.f / 10.f) - 260.f), window);
    // Ajout des menus
    // Appel du dessin du menu

    playerSize = { (int)((float)window.getSize().y / 16.f), (int)((float)window.getSize().y / 8.f) };
    player.loadAssets(window);
    player.resize(window);
    player.screenWidthLimit = window.getSize().x * 6.5f;

    level.loadMap(level.allLevels.at(index), &player, window, &parralaxLevelOne);
    mirrors.push_back(createRectangle(sf::Vector2f(5.f  * 40.f, floorLevel - 2.f  * 80.f), sf::Vector2f(40.f, 80.f)));
    mirrors.push_back(createRectangle(sf::Vector2f(24.f * 40.f, floorLevel - 4.f  * 80.f), sf::Vector2f(40.f, 80.f)));
    mirrors.push_back(createRectangle(sf::Vector2f(8.f  * 40.f, floorLevel - 8.f  * 80.f), sf::Vector2f(40.f, 80.f)));
    mirrors.push_back(createRectangle(sf::Vector2f(2.f  * 40.f, floorLevel - 13.f * 80.f), sf::Vector2f(40.f, 80.f)));
    mirrors.push_back(createRectangle(sf::Vector2f(20.f * 40.f, floorLevel - 3.f  * 80.f), sf::Vector2f(40.f, 80.f)));
    for (auto& mirror : mirrors) {
        mirror.shape.setTexture(levelTwo.getTexture());
    }

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

    level.plateformeTest.clear();
    level.platforms.clear();
    level.m_entityManager->deleteAllEnnemy();

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
        else if ((event.type == Event::KeyReleased && event.key.code == Keyboard::S && inGame) || (Joystick::getAxisPosition(0, Joystick::Y) < 50)) {
            player.hasPressedS = false;
        }
        else if (event.type == Event::KeyReleased && event.key.code == Keyboard::P) {
            inGame = !inGame;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (event.mouseButton.button == sf::Mouse::Left) {
                isMousePressed = true;
                isRectangleSelected = false;

                // Vérifier si un rectangle est cliqué
                for (auto& rect : mirrors) {
                    if (rect.contains(mousePos)) {
                        rect.select(mousePos);
                        isRectangleSelected = true;
                        break; // Sélectionner seulement le premier rectangle trouvé
                    }
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                isMousePressed = true;
                isRectangleSelected = false;

                for (auto& rect : mirrors) {
                    if (rect.contains(mousePos)) {
                        rect.deselect();
                        break;
                    }
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            isMousePressed = false;
        }
    }
}

bool Game::getRunning()
{
    return isRunning;
}

void Game::updateRay(RenderWindow& window) {
	allSegments.clear();
    raySegments.clear();
    // Ajouter les segments des rectangles flottants
    auto solarPanelSegments = levelTwo.endSolarPanel.getSegments();
    allSegments.insert(allSegments.end(), solarPanelSegments.begin(), solarPanelSegments.end());
    for (auto& rect : mirrors) {
        auto rectSegments = rect.getSegments();
        allSegments.insert(allSegments.end(), rectSegments.begin(), rectSegments.end());
    }

    // Calculer les réflexions
    sf::Vector2f currentOrigin = ray.origin;
    sf::Vector2f currentDirection = ray.direction;

    raySegments.push_back({ currentOrigin, currentOrigin }); // Placeholder pour le premier segment

    for (int i = 0; i < MAX_REFLECTIONS; i++) {
        float minDistance = std::numeric_limits<float>::max();
        sf::Vector2f closestIntersection;
        sf::Vector2f closestNormal;
        bool foundIntersection = false;

        // Trouver l'intersection la plus proche
        for (const auto& segment : allSegments) {
            sf::Vector2f intersection;
            float distance;

            if (raySegmentIntersection(
                currentOrigin, currentDirection,
                segment.first, segment.second,
                intersection, distance
            )) {
                if (distance < minDistance && distance > 0.001f) {
                    minDistance = distance;
                    closestIntersection = intersection;

                    // Calculer la normale au segment
                    sf::Vector2f segDir = segment.second - segment.first;
                    sf::Vector2f normal(-segDir.y, segDir.x);
                    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
                    normal /= length;

                    // S'assurer que la normale pointe vers l'intérieur
                    if (normal.x * currentDirection.x + normal.y * currentDirection.y > 0) {
                        normal = -normal;
                    }

                    closestNormal = normal;
                    foundIntersection = true;

                    // Vérifier si l'intersection s'est produite sur le panneau solaire (4 premiers segments)
                    if (segment == allSegments[0] || segment == allSegments[1] || segment == allSegments[2] || segment == allSegments[3]) {
                        levelTwo.endSolarPanel.isOn = true;
                        hasWon = true;
                    }
                    else {
                        levelTwo.endSolarPanel.isOn = false;
                    }
                }
            }
        }

        // Mettre à jour le segment de rayon actuel
        raySegments.back().second = foundIntersection ? closestIntersection : currentOrigin + currentDirection * 1000.f;

        // Si pas d'intersection, arrêter
        if (!foundIntersection) {
            break;
        }

        // Calculer la direction réfléchie
        sf::Vector2f reflectedDirection = reflect(currentDirection, closestNormal);

        // Préparer pour la prochaine itération
        currentOrigin = closestIntersection;
        currentDirection = reflectedDirection;

        // Ajouter un nouveau segment pour la prochaine réflexion
        raySegments.push_back({ currentOrigin, currentOrigin });
    }
}

void Game::update(const float& deltaTime, RenderWindow& window) {
    if (index == 1) {
        levelTwo.endSolarPanel.update(deltaTime, window);
		updateRay(window);
        updateMirrors(mirrors, deltaTime, window);
    }
    level.m_entityManager->updateEntities(window, deltaTime);
    player.Colision(window, deltaTime, level.platforms, level.plateformeTest);
    player.update(deltaTime, window);
    parralaxLevelOne.moveLayers(deltaTime, window, player);
    for (auto& Plateforme : level.plateformeTest) {
        Plateforme->platUpdate(deltaTime);
    }
    if (player.playerSprite.getGlobalBounds().intersects(level.endLevel.getGlobalBounds()) || player.playerSprite.getPosition().x > player.screenWidthLimit) {
        index += 1;
        if (index > 2) {
            index = 2;
            player.screenWidthLimit = window.getSize().x * 50.f;
        }
        if (index == 1) {
            levelActif = false;
            player.screenWidthLimit = window.getSize().x - player.playerSprite.getGlobalBounds().width;
        }
        else {
            levelActif = true;
        }
        level.plateformeTest.clear();
        level.platforms.clear();
            
        level.m_entityManager->deleteAllEnnemy();

        player.playerSprite.setPosition(500, 500);
        level.loadMap(level.allLevels.at(index), &player, window, &parralaxLevelOne);
    }
    if (player.playerSprite.getGlobalBounds().intersects(level.end.getGlobalBounds())) {
        isRunning = false;
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
        else if (position.x > window.getSize().x * 6.f) { //bloquer joueur vue
            position.x = window.getSize().x * 6.f;
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
    }
}

void Game::draw(RenderWindow& window) {
    window.clear();
    if (!hasWon && !hasLost) {
        if (index == 0) {
            parralaxLevelOne.draw(window);
        }
        else if (index == 1) {
            levelTwo.draw(window);
            for (auto& rect : mirrors) {
                rect.draw(window);
            }
            for (size_t i = 0; i < raySegments.size(); i++) {
                const auto& segment = raySegments[i];
                // Couleurs qui s'affaiblissent avec chaque réflexion
                sf::Color startColor = sf::Color::Yellow;
                sf::Color endColor = sf::Color::Yellow;
                ray.drawSegment(window, segment.first, segment.second, startColor, endColor);
            }
            levelTwo.endSolarPanel.draw(window);
        }
        level.drawMap(window);
        player.draw(window);
    }
    else if(hasWon && !hasLost) {
        window.draw(winScreen);
    }
    else {
        window.draw(lostScreen);
    }
    window.display();
}