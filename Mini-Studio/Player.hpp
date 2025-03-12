#pragma once

#include "Entity.hpp"
#include "Map.hpp"

class Player : public Entity {
public:
	bool isGoingLeft;
	bool isGoingRight;
	bool isDashing;
	bool isJumping;
	bool isFalling;
	bool canDoubleJump;
	bool hasPlatform;
	bool invertedGravity;
	bool isSpacePressed;
	int spacebarPresses;
	float fallingMovement;
	float jumpMovement;
	float velocity;
	float speed;
	float lastYPos;
	float fallingTime;
	float fallingSpeed;
	const float maxFallingForce = 9.81f;
	const int dashSpeed         = 700;
	const float gravityConst    = 9.81f;
	float dashingTime           = 0.5f;
	Clock clockDash;

public:
	Player();

public:
	void update(const float& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void Colision(RenderWindow& window, const float& deltaTime, vector<RectangleShape>& platforms);
	void resize(sf::RenderWindow& window, const Vector2f& size);

private:
	void jumpGestion(const float& deltaTime, RenderWindow& window);
	void dashGestion(const float& deltaTime, RenderWindow& window);
	void gravityGestion(const float& deltaTime, RenderWindow& window);
};