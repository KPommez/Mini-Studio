#pragma once

#include "EntityManager.hpp"
#include "Map.hpp"
#include "ParralaxBackground.hpp"
#include "LuminousBeam.hpp"

class Game {
public:
	Game(RenderWindow& window);
	void Run(RenderWindow& window);
	bool setRunning(bool test);

public:
	bool lose;
	bool inGame;
	Map level;
	Player player;
	bool getRunning();

private:
	void pollEvents(RenderWindow& window);
	void update(const float& deltaTime, RenderWindow& window);
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
	
	Event event;
	Clock Clock;
	View vue;
	Vector2i playerSize;
	ParralaxBackground parralaxLevelOne;
	LuminousBeam levelTwoBeam;
};