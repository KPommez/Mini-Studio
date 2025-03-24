#pragma once

#include "Entity.hpp"
#include "Map.hpp"

class Player : public Entity {
public:
	Player();

public:
	void update(const float& deltaTime, RenderWindow& window) override;
	void draw(RenderWindow& window) override;
	void Colision(RenderWindow& window, const float& deltaTime, vector<RectangleShape> platforms, vector<Plateforme*> platformsMobile);
	void resize(RenderWindow& window);
	void loadAssets(RenderWindow& window);
	Texture& getTexture();
	vector<Sprite>  playerSprites;

public:
	bool isDashing;
	bool canMove;
	bool isIdling;
	bool isGoingLeft;
	bool isGoingRight;
	bool hasPressedS;
	Sprite playerSprite;
	int hitcount;
	float screenWidthLimit;

private:
	void inputGestion(const float& deltaTime, RenderWindow& window);
	void jumpGestion(const float& deltaTime, RenderWindow& window);
	void dashGestion(const float& deltaTime, RenderWindow& window);
	void gravityGestion(const float& deltaTime, RenderWindow& window);
	void animationGestion(const float& deltaTime);

private:
	bool loaded = false;
	bool hadPlatformWhenJumped;
	bool isJumping;
	bool isFalling;
	bool canDoubleJump;
	bool hasPlatform;
	bool hasMovingPlatform;
	bool invertedGravity;
	bool isSpacePressed;
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
	Clock clockDash;
	Texture playerTexture;
	Texture 
		playerIdleTexture, 
		playerWalk1, playerWalk2, playerWalk3, 
		playerJump1, playerJump2, playerJump3, playerJump4;
	
	Sprite 
		playerIdleSprite, 
		playerWalk1Sprite, playerWalk2Sprite, playerWalk3Sprite, 
		playerJump1Sprite, playerJump2Sprite, playerJump3Sprite, playerJump4Sprite;
};