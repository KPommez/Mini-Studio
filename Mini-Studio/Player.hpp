#pragma once

#include "Entity.hpp"

class Player : public Entity {
public:
	bool isGoingLeft;
	bool isGoingRight;
	bool isDashing;
	bool isJumping;
	bool canDoubleJump;
	bool isTuching;
	bool hasPlatform;
	float fallingMovement;
	float jumpMovement;
	float velocity;
	float speed;
	float fallingTime;
	const int maxFallingForce = 20; // About twice as much as gravity force
	const int maxJumpingSpeed = 10;
	const int dashSpeed       = 700;
	const float gravityConst  = 9.81f;
	const float jumpForce     = 6.54f; // ~= Gravity force / 1.5f
	float dashingTime         = 0.5f;
	Clock clockDash;
	std::vector<sf::RectangleShape> platforms;

public:
	Player();

public:
	void update(const float& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void Colision(RenderWindow& window, const float& deltaTime);
	void resize(sf::RenderWindow& window);
};