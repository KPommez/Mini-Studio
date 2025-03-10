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
	Player player;

public:
	Game();
	void Run();
	Map level;

private:
	void update(const float& deltaTime);
	void pollEvents();
	void draw();
};