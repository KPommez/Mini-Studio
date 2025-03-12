#pragma once

#include "Entity.hpp"
#include "Map.hpp"

class Player : public Entity {
public:
	bool isDashing;
	bool isJumping;
	Sprite playerSprite;

private:
	bool firstInputDetected;
	bool isGoingLeft;
	bool isGoingRight;
	bool isFalling;
	bool canDoubleJump;
	bool hasPlatform;
	bool invertedGravity;
	bool isSpacePressed;
	bool isIdling;
	bool isIdlingAnimationStarted;
	bool isLeftAnimationStarted;
	bool isRightAnimationStarted;
	int spacebarPresses;
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
	Texture playerIdleTextureLeft, playerIdleTextureRight, playerWalk1Left, playerWalk1Right, playerWalk2Left, playerWalk2Right, playerWalk3Left, playerWalk3Right;
	vector<Sprite>  playerSprites;
	Sprite playerIdleSpriteLeft, playerIdleSpriteRight, playerWalk1SpriteLeft, playerWalk1SpriteRight, playerWalk2SpriteLeft, playerWalk2SpriteRight, playerWalk3SpriteLeft, playerWalk3SpriteRight;
	Clock clockDash;

public:
	Player();

public:
	void update(const float& deltaTime, RenderWindow& window) override;
	void draw(RenderWindow& window) override;
	void Colision(RenderWindow& window, const float& deltaTime, vector<RectangleShape>& platforms);
	void resize(RenderWindow& window);
	void loadAssets(RenderWindow& window);

private:
	void inputGestion(const float& deltaTime);
	void jumpGestion(const float& deltaTime, RenderWindow& window);
	void dashGestion(const float& deltaTime, RenderWindow& window);
	void gravityGestion(const float& deltaTime, RenderWindow& window);
	void animationGestion(const float& deltaTime);
};