#pragma once

#include "Entity.hpp"

class Player : public Entity {
private:
	bool isJumping;
	bool hasPlatform;
	float fallingTime;
	float speed;
	float velocity;
	const int maxFallingSpeed = 20; // ~2 fois la gravité
	const float gravityConst = 9.81f;

public:
	Player();

public:
	void update(const float& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
};