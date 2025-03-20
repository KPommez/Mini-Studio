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
    ray.create(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), sf::Vector2f(1.f, 1.5f));
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
    isMousePressed = false;
    isRectangleSelected = false;
}

void Game::Run(RenderWindow& window) {
    isRunning = true;
    inGame = true;
    srand(static_cast<unsigned int>(time(NULL)));
    levelActif = true;

    // Chargement des assets
    parralaxLevelOne.instanciateLayers(window, "levelOne", 8); // Level 1 has 7 layers in his background + 1 for high sky
    // Chargement de la map
    mirrors.push_back(createRectangle(sf::Vector2f(300.f, 200.f)));
    mirrors.push_back(createRectangle(sf::Vector2f(500.f, 400.f)));
    mirrors.push_back(createRectangle(sf::Vector2f(400.f, 300.f)));
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
        if ((event.type == Event::KeyReleased && event.key.code == Keyboard::S && inGame) || (Joystick::getAxisPosition(0, Joystick::Y) < 50)) {
            player.hasPressedS = false;
        }
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::P) {
            inGame = !inGame;
        }
        // Gestion des clics de souris
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
                // Créer un nouveau rectangle à la position du clic droit
                mirrors.push_back(createRectangle(mousePos));
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                isMousePressed = false;

                // Désélectionner tous les rectangles
                for (auto& rect : mirrors) {
                    rect.deselect();
                }
            }
        }
        else if (event.type == sf::Event::MouseMoved && isMousePressed) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // Déplacer le rectangle sélectionné
            for (auto& rect : mirrors) {
                rect.move(mousePos);
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Delete) {
                // Supprimer le rectangle sélectionné
                for (auto it = mirrors.begin(); it != mirrors.end(); ) {
                    if (it->isSelected) {
                        it = mirrors.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
            }
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
		updateRay(window);
    }
    level.m_entityManager->updateEntities(window, deltaTime);
    player.Colision(window, deltaTime, level.platforms, level.plateformeTest);
    player.update(deltaTime, window);
    parralaxLevelOne.moveLayers(deltaTime, window, player);
    for (auto& Plateforme : level.plateformeTest) {
        Plateforme->platUpdate(deltaTime);
    }
    
        if (player.playerSprite.getGlobalBounds().intersects(level.endLevel.getGlobalBounds()) || player.playerSprite.getPosition().x >12300) {
            index += 1;
            if (index > 2) {
                index = 2;
            }
            if (index == 1) {
                levelActif = false;
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
        //metre pour modif le joueur
    }
}

void Game::draw(RenderWindow& window) {
    window.clear();
    if (index == 0) {
        parralaxLevelOne.draw(window);
    }
    else if (index == 1) {
        for (auto& rect : mirrors) {
            rect.draw(window);
        }
        // Dessiner tous les segments du rayon
        for (const auto& segment : raySegments) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = segment.first;
            line[0].color = sf::Color::Red;
            line[1].position = segment.second;
            line[1].color = sf::Color::Yellow;
            window.draw(line);
        }
    }
    level.drawMap(window);
    player.draw(window);
    window.display();
}