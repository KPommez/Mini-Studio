#pragma once

#include "EntityManager.hpp"
#include "Map.hpp"
#include "ParralaxBackground.hpp"
// Level 2 header files
#include "LightSource.hpp"
#include "Mirror.hpp"
#include "Target.hpp"

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

private:
	void pollEvents(RenderWindow& window);
	void update(const float& deltaTime, RenderWindow& window);
	void draw(RenderWindow& window);

// Level 2 exclusive
private:
	int selectedMirror;
	bool mirrorSelected;
	LightSource lightSource;
	vector<Mirror> mirrors;
	Target target;
	vector<LightRay> lightPath;
	vector<LightRay> traceLightPath(const LightSource& source, const vector<Mirror>& mirrors, Target& target, int maxReflections = 10);

private:
	bool isRunning;
	bool firstParralaxOn, secondParralaxOn;
	bool levelActif;
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
};