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
	View vue;
	int screenX = 1920;
	int screenY = 1080;

public:
	Game();
	void Run();

public:
	Map level;
	Player player;

private:
	void update(const float& deltaTime);
	void pollEvents();
	void draw();
	void view();
};