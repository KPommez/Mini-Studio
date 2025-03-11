#pragma once

#include "Player.hpp"
#include "Map.hpp"

class Game
{
private:
	bool isRunning;	
	float deltaTime;
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock Clock;
	
private:
	Map level;
	Player player;
	View vue;
	int screenX = 1920;
	int screenY = 1080;

	void update(const float& deltaTime);
	void pollEvents();
	void draw();
	void view();

public:
	Game();
	void Run();
	Map level;

private:
	void update(const float& deltaTime);
	void pollEvents();
	void draw();
};