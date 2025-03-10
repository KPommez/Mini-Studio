#pragma once

#include "Entity.hpp"

class Player : public Entity {
public:
	bool isGoingLeft;
	bool isGoingRight;
	bool isDashing;
	bool isJumping;
	bool hasPlatform;
	float fallingMovement;
	float jumpMovement;
	float velocity;
	float fallingTime;
	const int maxFallingForce = 20; // ~2 fois la gravit�
	const int maxJumpingSpeed = 10;
	const float gravityConst = 9.81f;
	float dashingTime = 0.5f;
	const int dashSpeed = 5;
	const float jumpForce = 6.54f;
	float speed;
	Clock clockDash;

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