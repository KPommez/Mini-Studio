#pragma once

#include "Player.hpp"

class Eolienne : public Entity {
public:
	Eolienne(Vector2f pos);
	void update(const float& deltaTime, RenderWindow& window) override;
	void draw(RenderWindow& window) override;

private:
	Vector2f Position;
};