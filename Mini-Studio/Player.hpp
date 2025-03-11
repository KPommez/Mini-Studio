#pragma once

#include "Entity.hpp"
#include "Map.hpp"

class Player : public Entity {
public:
	bool isGoingLeft;
	bool isGoingRight;
	bool isDashing;
	bool isJumping;
	bool hasPlatform;
	bool invertedGravity;
	float fallingMovement;
	float jumpMovement;
	float velocity;
	float speed;
	float fallingTime;
	const int maxFallingForce = 30; // About twice as much as gravity force
	const int maxJumpingSpeed = 10;
	const int dashSpeed       = 700;
	const float gravityConst  = 9.81f;
	float dashingTime         = 0.5f;
	Clock clockDash;

public:
	Player();

public:
	void update(const float& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void Colision(RenderWindow& window, const float& deltaTime, vector<RectangleShape>& platforms);
	void resize(sf::RenderWindow& window);

private:
	void jumpGestion(const float& deltaTime, RenderWindow& window, const float& jumpDuration);
	void dashGestion(const float& deltaTime, RenderWindow& window);
	void gravityGestion(const float& deltaTime, RenderWindow& window);
};