#include "Player.hpp"

Player::Player() {
	// Boolean members
	isIdling                 = true;
	isIdlingAnimationStarted = true;
	isAnimationStarted       = false;
	invertedGravity          = false;
	hasPlatform              = true;
	isGoingLeft              = false;
	isGoingRight             = true;
	isJumping                = false;
    isDashing                = false;
	canDoubleJump            = true;
	isSpacePressed           = false;
	isFalling                = false;
	hasPressedS              = false;
	hadPlatformWhenJumped    = true;
	canMove					 = true;
	// Float members
	speed           = 400.f;
	fallingTime     = 0.f;
	dashingTime     = 0.f;
	fallingMovement = 0.f;
	jumpMovement    = 175.f;
	lastYPos        = 500.f;
	fallingSpeed    = speed;
	spacebarPresses = 0;
	countSide       = 0;
	animationTime   = 0.f;
}

void Player::resize(RenderWindow& window) {
	playerSprite = playerSprites[0];
	playerSprite.setPosition(Vector2f(window.getSize().x / 2.f - playerSprite.getGlobalBounds().width / 2.f, window.getSize().y - playerSprite.getGlobalBounds().height - window.getSize().y / 10.f));
}

void Player::loadAssets(RenderWindow& window) {
	// Loading the assets
	playerIdleTexture.loadFromFile("Assets/Player/idle.png");
	playerWalk1.loadFromFile("Assets/Player/walk1.png");
	playerWalk2.loadFromFile("Assets/Player/walk2.png");
	playerWalk3.loadFromFile("Assets/Player/walk3.png");
	// Setting the default player's texture
	playerTexture = playerIdleTexture;
	// Applying textures
	playerIdleSprite.setTexture(playerIdleTexture);
	playerWalk1Sprite.setTexture(playerWalk1);
	playerWalk2Sprite.setTexture(playerWalk2);
	playerWalk3Sprite.setTexture(playerWalk3);
	// Adding them to the vector of sprites
	playerSprites.reserve(4);
	playerSprites.emplace_back(playerIdleSprite);
	playerSprites.emplace_back(playerWalk1Sprite);
	playerSprites.emplace_back(playerWalk2Sprite);
	playerSprites.emplace_back(playerWalk3Sprite);
	// Applying a new scale to all the loaded sprites
	float ratio = playerTexture.getSize().y / (float)window.getSize().y;
	for (auto& _sprite : playerSprites) {
		_sprite.scale(ratio / 4.f, ratio / 4.f);
	}
}

void Player::update(const float& deltaTime, RenderWindow& window) {
	inputGestion(deltaTime, window);
	animationGestion(deltaTime);
	gravityGestion(deltaTime, window);
	jumpGestion(deltaTime, window);
	dashGestion(deltaTime, window);
}

void Player::inputGestion(const float& deltaTime, RenderWindow& window) {
	bool hasInput = false;
	// Inputs left & right
	if (canMove && (playerSprite.getPosition().x < 50.f * window.getSize().x - playerSprite.getGlobalBounds().width && (Keyboard::isKeyPressed(Keyboard::D) || Joystick::getAxisPosition(0,Joystick::X) >= 10))) {
		isGoingRight = true;
		isGoingLeft = false;
		isIdling = false;
		playerSprite.move(speed * 2.f * deltaTime, 0);
		hasInput = true;
	}
	if (canMove && (playerSprite.getPosition().x >= playerSprite.getGlobalBounds().width && (Keyboard::isKeyPressed(Keyboard::Q) || Joystick::getAxisPosition(0, Joystick::X) <= -10))) {
		isGoingLeft = true;
		isGoingRight = false;
		isIdling = false;
		playerSprite.move(-speed * 2.f * deltaTime, 0);
		hasInput = true;
	}
	if (canMove && (Keyboard::isKeyPressed(Keyboard::S) || Joystick::getAxisPosition(0, Joystick::Y) >= 50)) {
		if (!(playerSprite.getPosition().y >= window.getSize().y - playerSprite.getGlobalBounds().height - window.getSize().y / 10.f)) {
			hasPressedS = true;
		}
		else {
			hasPressedS = false;
		}
	}
	if (!hasInput) {
		isIdling = true;
	}
	else {
		isIdling = false;
	}
}

void Player::gravityGestion(const float& deltaTime, RenderWindow& window) {
	// Keeps falling faster until he reaches a certain limit (gravity inversible)
	float floorLevel = window.getSize().y - window.getSize().y / 10.f - playerSprite.getGlobalBounds().height;
	if (!invertedGravity) {
		if (!isJumping && !hasPlatform) {
			isFalling = true;
			if (fallingMovement < maxFallingForce) {
				fallingMovement += deltaTime * gravityConst;
			}
			if (playerSprite.getPosition().y > floorLevel) {
				playerSprite.setPosition(playerSprite.getPosition().x, floorLevel);
				hasPlatform = true;
			}
			else {
				if (hasPlatform) {
					playerSprite.move(0, 0);
				}
				else {
					playerSprite.move(0, fallingMovement * deltaTime * fallingSpeed);
				}
			}
		}
		else {
			fallingMovement = 0.f;
			isFalling = false;
		}
	}
	else {
		if (playerSprite.getPosition().y > 0 && !hasPlatform && !isJumping) {
			isFalling = true;
			if (hasPressedS) {
				hasPressedS = false;
			}
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
	if (canMove && ((Keyboard::isKeyPressed(Keyboard::Space) || Joystick::isButtonPressed(0, 1)) && canDoubleJump && !isJumping)) {
		if (spacebarPresses < 2) {
			if (spacebarPresses == 0) {
				if (isFalling) {
					hadPlatformWhenJumped = false;
				}
				canDoubleJump = true;
				isJumping = true;
			}
			if (spacebarPresses == 1 && !hadPlatformWhenJumped) {
				canDoubleJump = false;
			}
			else {
				canDoubleJump = true;
				isJumping = true;
			}
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
	if (canDoubleJump && isJumping) { 
		if (jumpMovement > 0) {
			jumpMovement -= deltaTime * speed;
		}
		else {
			isJumping = false;
		}
		if (!invertedGravity) {
			playerSprite.move(0, -jumpMovement * deltaTime * 9.81f);
		}
		else {
			playerSprite.move(0, jumpMovement * deltaTime * 9.81f);
		}
	}
	else {
		jumpMovement = 175.f;
	}
}

void Player::dashGestion(const float& deltaTime, RenderWindow& window) {
	if (Keyboard::isKeyPressed(Keyboard::LShift) || Joystick::isButtonPressed(0,5)) {
		isDashing = true;
	}
	if (clockDash.getElapsedTime().asSeconds() >= 2 && !isDashing) {
		clockDash.restart();
		dashingTime = 0;
	}
	if (isDashing) {
		dashingTime += deltaTime;
		if (isGoingLeft && dashingTime < 0.25f) {
			playerSprite.move((float)-dashSpeed * deltaTime, 0);
		}
		else if (isGoingRight && dashingTime < 0.25f) {
			playerSprite.move((float)dashSpeed * deltaTime, 0);
		}
		else {
			isDashing = false;
		}
	}
}

void Player::animationGestion(const float& deltaTime) {
	Vector2f scale = sprite.getScale();
	animationTime += deltaTime;
	if (!isIdling) {
		if (!isAnimationStarted) {
			isAnimationStarted = true;
			isIdlingAnimationStarted = false;
			animationTime = 0.f;
		}
		// Restart the animation loop after 0.5 seconds
		if (animationTime > 0.75f) {
			animationTime = 0.f;
		}
		else if (animationTime < .25f) {
			playerSprites[1].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[1];
		}
		else if (animationTime < .5f) {
			playerSprites[2].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[2];
		}
		else {
			playerSprites[3].setPosition(playerSprite.getPosition());
			playerSprite = playerSprites[3];
		}
	}
	// Idle
	else {
		if (!isIdlingAnimationStarted) {
			isIdlingAnimationStarted = true;
			isAnimationStarted = false;
			animationTime = 0.f;
		}
		playerSprites[0].setPosition(playerSprite.getPosition());
		playerSprite = playerSprites[0];
	}
	if (isGoingLeft) {
		playerSprite.scale(-abs(scale.x), scale.y);
	}
	else {
		playerSprite.scale(abs(scale.x), scale.y);
	}
}

void Player::Colision(RenderWindow& window, const float& deltaTime, vector<RectangleShape> platforms, vector<Plateforme*> platformsMobile) {
	float posY;
	float floorLevel = window.getSize().y - window.getSize().y / 10.f - playerSprite.getGlobalBounds().height;
	if (!invertedGravity) {
		posY = playerSprite.getPosition().y + playerSprite.getGlobalBounds().height;
	}
	else {
		posY = playerSprite.getPosition().y - playerSprite.getGlobalBounds().height;
	}
	if (playerSprite.getPosition().x <= 0) {
		playerSprite.move(speed * 2.f * deltaTime, 0);
		isIdling = true;
		isIdlingAnimationStarted = true;
	}
	hasPlatform = false;
	if (playerSprite.getPosition().y >= floorLevel) {
		isFalling = false;
		isJumping = false;
		hasPlatform = true;
		canDoubleJump = true;
		hadPlatformWhenJumped = true;
		playerSprite.setPosition(playerSprite.getPosition().x, floorLevel);
		spacebarPresses = 0;
	}
	else {
		int count = 0;
		for (auto& platform : platforms) {
			if (playerSprite.getGlobalBounds().intersects(platform.getGlobalBounds()) && !hasPressedS) {
				if (isFalling) {
					isJumping = false;
					isFalling = false;
					canDoubleJump = true;
					hadPlatformWhenJumped = true;
					spacebarPresses = 0;
					playerSprite.move(0, 0);
				}
				hasPlatform = true;
				cout << "Platform" << endl;
				count++;
			}
		}
		for (auto& platform : platformsMobile) {
			if (playerSprite.getGlobalBounds().intersects(platform->plat.getGlobalBounds()) && !hasPressedS) {
				if (isFalling) {
					isJumping = false;
					isFalling = false;
					canDoubleJump = true;
					hadPlatformWhenJumped = true;
					spacebarPresses = 0;
					playerSprite.move(0, 0);
				}
				hasPlatform = true;
				cout << "Platform" << endl;
				count++;
			}
		}
		if (!count) {
			isFalling   = true;
			hasPlatform = false;
		}
	}
	for (auto& platform : platforms) {
		if (playerSprite.getGlobalBounds().intersects(platform.getGlobalBounds()) && !hasPressedS && posY > platform.getPosition().y && !isJumping) {
			playerSprite.setPosition(playerSprite.getPosition().x, platform.getPosition().y - playerSprite.getGlobalBounds().height + 0.1f);
		}
	}
	for (auto& platform : platformsMobile) {
		if (playerSprite.getGlobalBounds().intersects(platform->plat.getGlobalBounds()) && !hasPressedS && posY > platform->plat.getPosition().y && !isJumping) {
			playerSprite.setPosition(playerSprite.getPosition().x, platform->plat.getPosition().y - playerSprite.getGlobalBounds().height + 0.1f);
		}
	}
}

void Player::draw(RenderWindow& window) {
	window.draw(playerSprite);
}