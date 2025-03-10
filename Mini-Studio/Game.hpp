#pragma once

#include "Player.hpp"
#include "Lampadaire.hpp"

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

private:
	void update(const float& deltaTime);
	void pollEvents();
	void draw();
};