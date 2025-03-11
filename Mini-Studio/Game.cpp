#include "Game.hpp"


Game::Game() : window(sf::VideoMode::getFullscreenModes().at(0), "Mini-Studio", sf::Style::Fullscreen)
{
    
    m_entityManager = make_shared<EntityManager>();
    window.setFramerateLimit(144);
    deltaTime = 0.f;
    event = {};
    isRunning = true;
}

void Game::Run() {
    shared_ptr<Lampadaire> test = make_shared<Lampadaire>(Vector2f(200, 1000), &player);
    m_entityManager->addEnnemy(test);
    
    // Chargement des assets
    // Chargement de la map
    // Ajout des menus
    // Appel du dessin du menu
    
    while (window.isOpen() && isRunning) {
        
        deltaTime = Clock.restart().asSeconds();

        pollEvents();
        m_entityManager->updateEntities(window,deltaTime);
        window.clear();
        player.draw(window);
        m_entityManager->drawEntities(window);
        window.display();
        player.update(deltaTime, window);
        player.Colision(window, deltaTime);
        if (Keyboard::isKeyPressed(Keyboard::J)) {
            isRunning = false;
        }
       
        
        
    }

    window.close();

}

void Game::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            isRunning = false;
    }
}

