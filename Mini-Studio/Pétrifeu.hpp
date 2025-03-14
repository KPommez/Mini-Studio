#pragma once

#include "Player.hpp"

class Petrifeu : public Entity {
public:
	Petrifeu(Vector2f pos, Player* players);
	void update(const float& deltaTime, RenderWindow& window) override;
	void draw(RenderWindow& window) override;

private:
	void patrol(const float& deltaTime);

private:
	Player* player;
	RectangleShape zone;
	Vector2f position;
};