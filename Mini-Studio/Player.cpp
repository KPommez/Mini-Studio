#include "Player.hpp"

Player::Player() {
	// Boolean members
	invertedGravity = false;
	hasPlatform     = false;
	isGoingLeft     = false;
	isGoingRight    = false;
	isJumping       = false;
    hasPlatform     = false;
    isDashing       = false;
	canDoubleJump   = true;
	isTuching       = false;
	isSpacePressed  = false;
	isFalling       = true;
	// Float members
	speed           = 350.f;
	fallingTime     = 0.f;
	dashingTime     = 0.f;
	velocity        = 0.f;
	fallingMovement = 0.f;
	jumpMovement    = 350.f;
	lastYPos        = 500.f;
	spacebarPresses = 0;
	// Player's shape definition
	shape.setSize(sf::Vector2f(40.f, 40.f));
}

void Player::resize(sf::RenderWindow& window) {
	shape.setSize(sf::Vector2f(window.getSize().y / 16.f, (window.getSize().y / 8.f)));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 0);
}

void Player::update(const float& deltaTime, sf::RenderWindow& window) {
	/*if (!invertedGravity) {
		floorLevel = window.getSize().y - shape.getSize().y;
	}
	else {
		floorLevel = 0;
	}*/
	gravityGestion(deltaTime, window);
	jumpGestion(deltaTime, window, 1.f);
	dashGestion(deltaTime, window);
	// Inputs left & right
	if (Keyboard::isKeyPressed(Keyboard::D) || Joystick::getAxisPosition(0,Joystick::X) >= 10) {
		isGoingRight = true;
		isGoingLeft = false;
		shape.move(speed * deltaTime, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q) || Joystick::getAxisPosition(0, Joystick::X) <= -10) {
		isGoingLeft = true;
		isGoingRight = false;
		shape.move(-speed * deltaTime, 0);
	}
}

void Player::jumpGestion(const float& deltaTime, RenderWindow& window, const float& jumpDuration) {
	if (spacebarPresses > 0) {
		cout << "Jumps : " << spacebarPresses << endl;
	}
	else {
		canDoubleJump = true;
		isJumping = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) || Joystick::isButtonPressed(0,0) && canDoubleJump && !isJumping) {
		if (spacebarPresses < 2) {
			canDoubleJump = true;
			isJumping = true;
		}
		else {
			canDoubleJump = false;
		}
		spacebarPresses++;
	}
	
	// Impulsion force slowly going down
		// First case : still on the ground, first jump
	if (isJumping && hasPlatform) {
		if (jumpMovement > 0) {
			jumpMovement -= deltaTime * gravityConst * 4.f;
		}
		else {
			isJumping = false;
		}
		if (!invertedGravity) {
			shape.move(0, -jumpMovement);
		}
		else {
			shape.move(0, jumpMovement);
		}
	}
		// Second case : Falling off a platform
	else if (isJumping && !hasPlatform && spacebarPresses == 1) {
		if (jumpMovement > 0) {
			jumpMovement -= deltaTime * gravityConst * 5.f;
		}
		else {
			isJumping = false;
		}
		if (!invertedGravity) {
			shape.move(0, -jumpMovement);
		}
		else {
			shape.move(0, jumpMovement);
		}
	}
		// Third case : Double jump
	else if (isJumping && !hasPlatform && spacebarPresses == 2) {
		if (jumpMovement > 0) {
			jumpMovement -= deltaTime * gravityConst * 5.f;
		}
		else {
			isJumping = false;
		}
		if (!invertedGravity) {
			shape.move(0, -jumpMovement);
		}
		else {
			shape.move(0, jumpMovement);
		}
	}
	else {
		jumpMovement = 15.f;
	}
}

void Player::gravityGestion(const float& deltaTime, RenderWindow& window) {
	// Keeps falling faster until he reaches a certain limit (gravity inversible)
	if (!invertedGravity) {
		if (shape.getPosition().y < (window.getSize().y - shape.getSize().y) && !hasPlatform && !isJumping) {
			isFalling = true;
			if (fallingMovement < maxFallingForce) {
				fallingMovement += deltaTime * gravityConst * 4.f;
			}
			shape.move(0, fallingMovement);
		}
		else {
			fallingMovement = 0.f;
		}
	}
	else {
		if (shape.getPosition().y > 0 && !hasPlatform && !isJumping) {
			isFalling = true;
			if (fallingMovement < maxFallingForce) {
				fallingMovement += deltaTime * gravityConst * 4.f;
			}
			shape.move(0, -fallingMovement);
		}
		else {
			fallingMovement = 0.f;
		}
	}
}

void Player::dashGestion(const float& deltaTime, RenderWindow& window) {
	if (Keyboard::isKeyPressed(Keyboard::F) || Joystick::isButtonPressed(0,5))
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
			shape.move((float)-dashSpeed * deltaTime, 0);
		}
		else if (isGoingRight && dashingTime < 0.25f)
		{
			shape.move((float)dashSpeed * deltaTime, 0);
		}
		else
		{
			isDashing = false;
		}
	}
}

void Player::Colision(RenderWindow& window, const float& deltaTime, vector<RectangleShape>& platforms) {
	if (shape.getPosition().x <= 0) {
		shape.move(speed * deltaTime, 0);
	}
	/*if (shape.getPosition().x >= window.getSize().x - shape.getSize().x)
	{
		shape.move(-speed * deltaTime, 0);
	}*/
	hasPlatform = false;
	isFalling = true;
	for (auto& platform : platforms) {
		if (shape.getGlobalBounds().intersects(platform.getGlobalBounds())) {
			hasPlatform = true;
			isFalling = false;
			spacebarPresses = 0;
		}
	}
	if (shape.getPosition().y <= 0 || hasPlatform) {
		shape.move(0, 0);
		isFalling = false;
	}
	if (shape.getPosition().y >= window.getSize().y - shape.getSize().y || hasPlatform)
	{
		shape.move(0, 0);
		isFalling = false;
	}
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(shape);
}