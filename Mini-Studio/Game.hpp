#pragma once

#include "Lampadaire.hpp"
#include "Pétrifeu.hpp"
#include "EntityManager.hpp"
#include "Map.hpp"
#include "Menu.hpp"

class Game {
public:
	Game();
	void Run();

public:
	bool inGame;
	Map level;
	Player player;

private:
	void update(const float& deltaTime);
	void pollEvents();
	void draw();
	void view();

private:
	bool isRunning;
	int index;
	int screenX;
	int screenY;
	int spaceReleases;
	float deltaTime;
	shared_ptr<EntityManager>  m_entityManager;
	RenderWindow window;
	Event event;
	Clock Clock;
	View vue;
	Vector2i playerSize;
};