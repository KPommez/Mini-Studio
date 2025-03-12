#pragma once

#include "Player.hpp"

class Lampadaire : public Entity
{
public:
	Lampadaire(Vector2f pos, Player* players);
	Player* player;
	void update(const float& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void chase(sf::Vector2f playerPos, const float& deltaTime);
	Vector2f position;
	
	
	bool detectPlayer(sf::Vector2f playerPos);
	void patrol(const float& deltaTime);
	ConvexShape lum;
	enum State { PATROL, CHASE, SEARCH };
	State currentState;
	enum  MOVEMENTSIDE
	{
		LEFT,
		RIGHT
	};
	MOVEMENTSIDE moveSide;
};