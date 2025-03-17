#pragma once

#include "Player.hpp"
#include "vector"
class Eolienne : public Entity {
public:
	Eolienne(Vector2f pos, Player* players, RenderWindow& window);
	void update(const float& deltaTime, RenderWindow& window) override;
	void draw(RenderWindow& window) override;
	
	
	void patrol(const float& deltaTime);
	void push(RenderWindow& window, const float& deltaTime);
private:
	Player* player;
	Vector2f position;
	RectangleShape zone;
	enum State { PATROL, PUSH };
	Clock clock;
	enum  MOVEMENTSIDE { LEFT, RIGHT };
	State currentState;
	MOVEMENTSIDE moveSide;
	Vector2f Position;
};