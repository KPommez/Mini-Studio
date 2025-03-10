#pragma once

#include "Entity.hpp"

class Player : public Entity {
public:
	float speed;
	float gravity;

public:
	Player();

public:
	void update(const float& deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void Colision(RenderWindow& window, const float& deltaTime);
};