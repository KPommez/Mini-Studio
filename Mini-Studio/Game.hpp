#pragma once

#include "Lampadaire.hpp"
#include "EntityManager.hpp"
#include "Map.hpp"
#include "Menu.hpp"

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
	sf::Vector2f playerSize;
	int index;
	int screenX;
	int screenY;
	int spaceReleases;


public:
	bool inGame;
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