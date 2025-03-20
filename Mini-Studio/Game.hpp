#pragma once

#include "EntityManager.hpp"
#include "Map.hpp"
#include "ParralaxBackground.hpp"

class Ray;
struct Mirror;

class Game {
public:
	Game(RenderWindow& window);
	void Run(RenderWindow& window);
	bool setRunning(bool test);
	void view(RenderWindow& window);

public:
	bool lose;
	bool inGame;
	Map level;
	Player player;
	bool getRunning();
	int index;

private:
	void pollEvents(RenderWindow& window);
	void update(const float& deltaTime, RenderWindow& window);
	void updateRay(RenderWindow& window);
	void draw(RenderWindow& window);

private:
	bool isRunning;
	bool firstParralaxOn, secondParralaxOn;
	bool isMousePressed;
	bool isRectangleSelected;
	bool levelActif;

	int screenX;
	int screenY;
	int spaceReleases;
	float deltaTime;
	
	Event event;
	Clock Clock;
	View vue;
	Vector2i playerSize;
	ParralaxBackground parralaxLevelOne;
};