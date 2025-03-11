#pragma once

#include "Lampadaire.hpp"
#include "EntityManager.hpp"
#include "Map.hpp"

class Game
{
private:
	bool isRunning;	
	float deltaTime;
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock Clock;
	std::shared_ptr<EntityManager>  m_entityManager;

public:
	Player player;
	Map level;

public:
	Game();
	void Run();
	
private:
	void update(const float& deltaTime);
	void pollEvents();
	void draw();
};