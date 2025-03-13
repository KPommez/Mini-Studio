#pragma once

#include "Player.hpp"

class Petrifeu : public Entity
{
public:
	Petrifeu(Vector2f pos, Player* players);
	Player* player;
	void update(const float& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	RectangleShape zone;
	Vector2f position;


	
	void patrol(const float& deltaTime);
	
	
};