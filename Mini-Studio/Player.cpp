#include "Player.hpp"

Player::Player() {
	// Boolean members
	isIdling                 = true;
	isIdlingAnimationStarted = true;
	isLeftAnimationStarted   = false;
	isRightAnimationStarted  = false;
	invertedGravity          = false;
	hasPlatform              = true;
	isGoingLeft              = false;
	isGoingRight             = true;
	isJumping                = false;
    isDashing                = false;
	canDoubleJump            = true;
	isSpacePressed           = false;
	isFalling                = false;
	// Float members
	speed           = 400.f;
	fallingTime     = 0.f;
	dashingTime     = 0.f;
	fallingMovement = 0.f;
	jumpMovement    = 175.f;
	lastYPos        = 500.f;
	fallingSpeed    = speed;
	spacebarPresses = 0;
	animationTime   = 0.f;
}

void Player::resize(sf::RenderWindow& window) {
	playerTexture.loadFromFile("Assets/Player/idle_Right.png");
	float ratio = playerTexture.getSize().y / (float)window.getSize().y;
	playerSprite.setTexture(playerTexture);
	playerSprite.scale(ratio / 6.5f, ratio / 6.5f);
	playerSprite.setPosition(Vector2f(100, window.getSize().y - playerSprite.getLocalBounds().height - 40.f));
}

void Player::loadAssets(RenderWindow& window) {
	playerTexture.loadFromFile("Assets/Player/idle_Right.png");
	float ratio = playerTexture.getSize().y / (float)window.getSize().y;
	// Loading the assets
	playerIdleTextureLeft.loadFromFile("Assets/Player/idle_Left.png");
	playerWalk1Left.loadFromFile("Assets/Player/walk1_Left.png");
	playerWalk2Left.loadFromFile("Assets/Player/walk2_Left.png");
	playerWalk3Left.loadFromFile("Assets/Player/walk3_Left.png");
	playerIdleTextureRight.loadFromFile("Assets/Player/idle_Right.png");
	playerWalk1Right.loadFromFile("Assets/Player/walk1_Right.png");
	playerWalk2Right.loadFromFile("Assets/Player/walk2_Right.png");
	playerWalk3Right.loadFromFile("Assets/Player/walk3_Right.png");
	// Transferring them to sprites
	playerIdleSpriteLeft.setTexture(playerIdleTextureLeft);
	playerIdleSpriteLeft.scale(ratio / 6.5f, ratio / 6.5f);
	playerWalk1SpriteLeft.setTexture(playerWalk1Left);
	playerWalk1SpriteLeft.scale(ratio / 6.5f, ratio / 6.5f);
	playerWalk2SpriteLeft.setTexture(playerWalk2Left);
	playerWalk2SpriteLeft.scale(ratio / 6.5f, ratio / 6.5f);
	playerWalk3SpriteLeft.setTexture(playerWalk3Left);
	playerWalk3SpriteLeft.scale(ratio / 6.5f, ratio / 6.5f);
	playerIdleSpriteRight.setTexture(playerIdleTextureRight);
	playerIdleSpriteRight.scale(ratio / 6.5f, ratio / 6.5f);
	playerWalk1SpriteRight.setTexture(playerWalk1Right);
	playerWalk1SpriteRight.scale(ratio / 6.5f, ratio / 6.5f);
	playerWalk2SpriteRight.setTexture(playerWalk2Right);
	playerWalk2SpriteRight.scale(ratio / 6.5f, ratio / 6.5f);
	playerWalk3SpriteRight.setTexture(playerWalk3Right);
	playerWalk3SpriteRight.scale(ratio / 6.5f, ratio / 6.5f);
	// Adding them to the vector of sprites
	playerSprites.reserve(8);
	playerSprites.emplace_back(playerIdleSpriteLeft);
	playerSprites.emplace_back(playerWalk1SpriteLeft);
	playerSprites.emplace_back(playerWalk2SpriteLeft);
	playerSprites.emplace_back(playerWalk3SpriteLeft);
	playerSprites.emplace_back(playerIdleSpriteRight);
	playerSprites.emplace_back(playerWalk1SpriteRight);
	playerSprites.emplace_back(playerWalk2SpriteRight);
	playerSprites.emplace_back(playerWalk3SpriteRight);
}

void Player::update(const float& deltaTime, sf::RenderWindow& window) {
	inputGestion(deltaTime);
	animationGestion(deltaTime);
	gravityGestion(deltaTime, window);
	jumpGestion(deltaTime, window);
	dashGestion(deltaTime, window);
}

void Player::inputGestion(const float& deltaTime) {
	// Inputs left & right
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		isGoingRight = true;
		isGoingLeft = false;
		isIdling = false;
		playerSprite.move(speed * 2.f * deltaTime, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		isGoingLeft = true;
		isGoingRight = false;
		isIdling = false;
		playerSprite.move(-speed * 2.f * deltaTime, 0);
	}
	if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::Q) && !Keyboard::isKeyPressed(Keyboard::F)) {
		isIdling = true;
	}
	else {
		isIdling = false;
	}
}

void Player::gravityGestion(const float& deltaTime, RenderWindow& window) {
	// Keeps falling faster until he reaches a certain limit (gravity inversible)
	if (!invertedGravity) {
		if ((playerSprite.getPosition().y < (window.getSize().y - playerSprite.getGlobalBounds().height)) && !hasPlatform && !isJumping) {
			isFalling = true;
			if (fallingMovement < maxFallingForce) {
				fallingMovement += deltaTime * gravityConst;
			}
			if (playerSprite.getPosition().y > (window.getSize().y - playerSprite.getGlobalBounds().height))
				playerSprite.setPosition(0, 0);
			else
				playerSprite.move(0, fallingMovement * deltaTime * fallingSpeed);
		}
		else {
			fallingMovement = 0.f;
			isFalling = false;
		}
	}
	else {
		if (playerSprite.getPosition().y > 0 && !hasPlatform && !isJumping) {
			isFalling = true;
			if (fallingMovement < maxFallingForce) {
				fallingMovement += deltaTime * gravityConst;
			}
			playerSprite.move(0, -fallingMovement * deltaTime * fallingSpeed);
		}
		else {
			fallingMovement = 0.f;
			isFalling = false;
		}
	}
}

void Player::jumpGestion(const float& deltaTime, RenderWindow& window) {
	if (Keyboard::isKeyPressed(Keyboard::Space) && canDoubleJump && !isJumping) {
		if (spacebarPresses < 2) {
			canDoubleJump = true;
			isJumping = true;
		}
		else {
			canDoubleJump = false;
		}
		spacebarPresses++;
	}
	if (spacebarPresses == 0) {
		canDoubleJump = true;
		isJumping = false;
	}
	// Impulsion force slowly going down
	if ((isJumping && hasPlatform) || (isJumping && !hasPlatform && spacebarPresses == 1) || (isJumping && !hasPlatform && spacebarPresses == 2)) {
		if (jumpMovement > 0) {
			cout << jumpMovement << endl;
			jumpMovement -= deltaTime * speed;
		}
		else {
			isJumping = false;
		}
		if (!invertedGravity) {
			playerSprite.move(0, -jumpMovement * deltaTime * 9.f);
		}
		else {
			playerSprite.move(0, jumpMovement * deltaTime * 9.f);
		}
	}
	else {
		jumpMovement = 175.f;
	}
}

void Player::dashGestion(const float& deltaTime, RenderWindow& window) {
	if (Keyboard::isKeyPressed(Keyboard::F))
	{
		isDashing = true;
	}
	if (clockDash.getElapsedTime().asSeconds() >= 2 && !isDashing)
	{
		clockDash.restart();
		dashingTime = 0;
	}
	if (isDashing)
	{
		dashingTime += deltaTime;
		if (isGoingLeft && dashingTime < 0.25f)
		{
			playerSprite.move((float)-dashSpeed * deltaTime, 0);
		}
		else if (isGoingRight && dashingTime < 0.25f)
		{
			playerSprite.move((float)dashSpeed * deltaTime, 0);
		}
		else
		{
			isDashing = false;
		}
	}
}

void Player::animationGestion(const float& deltaTime) {
	animationTime += deltaTime;
	// Going left (index 1 to 3)
	if (isGoingLeft && !isIdling) {
		if (!isLeftAnimationStarted) {
			isLeftAnimationStarted = true;
			isRightAnimationStarted = false;
			isIdlingAnimationStarted = false;
			animationTime = 0.f;
		}
		// Restart the animation loop after 0.5 seconds
		if (animationTime > .5f) {
			animationTime = 0.f;
		}
		else if (animationTime < (.5f / 3.f)) {
			playerSprites[1].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[1];
		}
		else if (animationTime < (.5f / 2.f)) {
			playerSprites[2].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[2];
		}
		else {
			playerSprites[3].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[3];
		}
	}
	// Going right (index 5 to 7)
	else if (isGoingRight && !isIdling) {
		if (!isRightAnimationStarted) {
			isRightAnimationStarted = true;
			isLeftAnimationStarted = false;
			isIdlingAnimationStarted = false;
			animationTime = 0.f;
		}
		// Restart the animation loop after 0.5 seconds
		if (animationTime > .5f) {
			animationTime = 0.f;
		}
		else if (animationTime < (.5f / 3.f)) {
			playerSprites[5].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[5];
		}
		else if (animationTime < (.5f / 2.f)) {
			playerSprites[6].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[6];
		}
		else {
			playerSprites[7].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[7];
		}
	}
	// Idle (left : 0, right : 4)
	else {
		if (!isIdlingAnimationStarted) {
			isIdlingAnimationStarted = true;
			isLeftAnimationStarted = false;
			isRightAnimationStarted = false;
			animationTime = 0.f;
		}
		if (isGoingLeft) {
			playerSprites[0].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[0];
		}
		else {
			playerSprites[4].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[4];
		}
	}
}

void Player::Colision(RenderWindow& window, const float& deltaTime, vector<RectangleShape>& platforms) {
	cout << playerSprite.getPosition().y << endl;
	if (playerSprite.getPosition().x <= 0) {
		playerSprite.move(speed * deltaTime, 0);
	}
	hasPlatform = false;
	isFalling = true;
	for (auto& platform : platforms) {
		if (playerSprite.getGlobalBounds().intersects(platform.getGlobalBounds()) || (playerSprite.getPosition().y - playerSprite.getGlobalBounds().height == platform.getPosition().y)) {
			hasPlatform = true;
			isFalling = false;
			spacebarPresses = 0;
		}
	}
	if ((playerSprite.getPosition().y <= 0) || hasPlatform) {
		playerSprite.move(0, 0);
		isFalling = false;
	}
	if ((playerSprite.getPosition().y >= (window.getSize().y - playerSprite.getGlobalBounds().height)) || hasPlatform)
	{
		playerSprite.move(0, 0);
		isFalling = false;
	}
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(playerSprite);
}