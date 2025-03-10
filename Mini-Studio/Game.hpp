#pragma once

#include "Menu.hpp"

class Game
{
public:

	Game();

	void Run(RenderWindow& window);
	MenuManager* createMenu(sf::RenderWindow& window);
};

