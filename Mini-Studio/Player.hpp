#pragma once

#include "Entity.hpp"
#include "Map.hpp"

class Player : public Entity {
public:
	Player();

public:
	void update(const float& deltaTime, RenderWindow& window) override;
	void draw(RenderWindow& window) override;
	void Colision(RenderWindow& window, const float& deltaTime, vector<RectangleShape> platforms);
	void resize(RenderWindow& window);
	void loadAssets(RenderWindow& window);

public:
	bool isDashing;
	bool isGoingLeft;
	bool isGoingRight;
	bool hasPressedS;
	Sprite playerSprite;

private:
	void inputGestion(const float& deltaTime, RenderWindow& window);
	void jumpGestion(const float& deltaTime, RenderWindow& window);
	void dashGestion(const float& deltaTime, RenderWindow& window);
	void gravityGestion(const float& deltaTime, RenderWindow& window);
	void animationGestion(const float& deltaTime);

private:
	bool hadPlatformWhenJumped;
	bool isJumping;
	bool isFalling;
	bool canDoubleJump;
	bool hasPlatform;
	bool invertedGravity;
	bool isSpacePressed;
	bool isIdling;
	bool isIdlingAnimationStarted;
	bool isAnimationStarted;
	int spacebarPresses;
	int countSide;
	float animationTime;
	float fallingMovement;
	float jumpMovement;
	float speed;
	float lastYPos;
	float fallingTime;
	float fallingSpeed;
	const float maxFallingForce = 9.81f;
	const int dashSpeed         = 700;
	const float gravityConst    = 9.81f;
	float dashingTime           = 0.5f;
	Texture playerTexture;
	Texture playerIdleTexture, playerWalk1, playerWalk2, playerWalk3;
	vector<Sprite>  playerSprites;
	Sprite playerIdleSprite, playerWalk1Sprite, playerWalk2Sprite, playerWalk3Sprite;
	Clock clockDash;
};