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
	int screenX;
	int screenY;
	int spaceReleases;

public:
	bool inGame;
	Game(RenderWindow& window);
	void Run(RenderWindow& window);
	bool setRunning(bool test);

public:
	Map level;
	Player player;

private:
	void update(const float& deltaTime, RenderWindow& window);
	void pollEvents(RenderWindow& window);
	void draw(RenderWindow& window);
	void view(RenderWindow& window);
};