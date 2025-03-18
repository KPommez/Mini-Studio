#pragma once

#include "Entity.hpp"

class ParralaxBackground;
class Player;

class Lampadaire : public Entity {
public:
	Lampadaire(Vector2f pos, Player* players, ParralaxBackground* currentLevel);
	void update(const float& deltaTime, RenderWindow& window) override;
	void draw(RenderWindow& window) override;

private:
	void chase(Vector2f playerPos, const float& deltaTime, RenderWindow& window);
	bool detectPlayer(Vector2f playerPos);
	void patrol(const float& deltaTime);

private:
	ParralaxBackground* currentLevel;
	Player* player;
	Vector2f position;
	ConvexShape lum;
	enum State { PATROL, CHASE, SEARCH };
	enum  MOVEMENTSIDE { LEFT, RIGHT };
	State currentState;
	MOVEMENTSIDE moveSide;
	int currentWaypoint;
};