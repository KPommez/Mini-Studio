#pragma once

#include "Entity.hpp"

class Player : public Entity {
private:
	float speed;
	float velocity;

public:
	Player();

public:
	void update(const float& deltaTime) override;
	void draw(sf::RenderWindow& window) override;
};