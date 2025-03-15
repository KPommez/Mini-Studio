#pragma once

#include "Lampadaire.hpp"
#include "Pétrifeu.hpp"
#include "Eolienne.hpp"
#include "EntityManager.hpp"
#include "Map.hpp"
#include "ParralaxBackground.hpp"

class Game {
public:
	Game(RenderWindow& window);
	void Run(RenderWindow& window);
	bool setRunning(bool test);

public:
	bool inGame;
	Map level;
	Player player;

private:
	void update(const float& deltaTime, RenderWindow& window);
	void pollEvents(RenderWindow& window);
	void draw(RenderWindow& window);
	void view(RenderWindow& window);

private:
	bool isRunning;
	bool firstParralaxOn, secondParralaxOn;
	int index;
	int screenX;
	int screenY;
	int spaceReleases;
	float deltaTime;
	shared_ptr<EntityManager>  m_entityManager;
	Event event;
	Clock Clock;
	View vue;
	Vector2i playerSize;
	ParralaxBackground parralaxLevelOne;
};