#pragma once

#include "Entity.hpp"

class Player : public Entity {
public:
	bool isJumping;
	bool hasPlatform;
	float fallingMovement;
	float jumpMovement;
	float velocity;
	const int maxFallingForce = 20; // ~2 fois la gravit�
	const int maxJumpingSpeed = 10;
	const float gravityConst = 9.81f;
	const float jumpForce = 6.54f;
	float speed;

public:
	std::vector<sf::RectangleShape> platforms;

public:
	Player();

public:
	void update(const float& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void Colision(RenderWindow& window, const float& deltaTime);
	void resize(sf::RenderWindow& window);
};