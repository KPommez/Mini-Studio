#include "Player.hpp"

Player::Player() {
	// Boolean members
	invertedGravity = false;
	hasPlatform     = true;
	isGoingLeft     = false;
	isGoingRight    = false;
	isJumping       = false;
    isDashing       = false;
	canDoubleJump   = true;
	isSpacePressed  = false;
	isFalling       = false;
	// Float members
	speed           = 400.f;
	fallingTime     = 0.f;
	dashingTime     = 0.f;
	fallingMovement = 0.f;
	jumpMovement    = 175.f;
	lastYPos        = 500.f;
	fallingSpeed    = speed;
	spacebarPresses = 0;
}

void Player::resize(sf::RenderWindow& window, const Vector2f& size) {
	shape.setSize(size);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(Vector2f(100, window.getSize().y - shape.getSize().y - 40.f));
}

void Player::update(const float& deltaTime, sf::RenderWindow& window) {
	gravityGestion(deltaTime, window);
	jumpGestion(deltaTime, window);
	dashGestion(deltaTime, window);
	// Inputs left & right
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		isGoingRight = true;
		isGoingLeft = false;
		shape.move(speed * 2.f * deltaTime, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		isGoingLeft = true;
		isGoingRight = false;
		shape.move(-speed * 2.f * deltaTime, 0);
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
			shape.move(0, -jumpMovement * deltaTime * 9.f);
		}
		else {
			shape.move(0, jumpMovement * deltaTime * 9.f);
		}
	}
	else {
		jumpMovement = 175.f;
	}
}

void Player::gravityGestion(const float& deltaTime, RenderWindow& window) {
	// Keeps falling faster until he reaches a certain limit (gravity inversible)
	if (!invertedGravity) {
		if ((shape.getPosition().y < (window.getSize().y - shape.getSize().y)) && !hasPlatform && !isJumping) {
			isFalling = true;
			if (fallingMovement < maxFallingForce) {
				fallingMovement += deltaTime * gravityConst;
			}
			if (shape.getPosition().y > (window.getSize().y - shape.getSize().y))
				shape.setPosition(0, 0);
			else
				shape.move(0, fallingMovement * deltaTime * fallingSpeed);
		}
		else {
			fallingMovement = 0.f;
			isFalling = false;
		}
	}
	else {
		if (shape.getPosition().y > 0 && !hasPlatform && !isJumping) {
			isFalling = true;
			if (fallingMovement < maxFallingForce) {
				fallingMovement += deltaTime * gravityConst;
			}
			shape.move(0, -fallingMovement * deltaTime * fallingSpeed);
		}
		else {
			fallingMovement = 0.f;
			isFalling = false;
		}
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
	cout << shape.getPosition().y << endl;
	if (shape.getPosition().x <= 0) {
		shape.move(speed * deltaTime, 0);
	}
	hasPlatform = false;
	isFalling = true;
	for (auto& platform : platforms) {
		if (shape.getGlobalBounds().intersects(platform.getGlobalBounds()) || (shape.getPosition().y - shape.getSize().y == platform.getPosition().y)) {
			hasPlatform = true;
			isFalling = false;
			spacebarPresses = 0;
		}
	}
	if ((shape.getPosition().y <= 0) || hasPlatform) {
		shape.move(0, 0);
		isFalling = false;
	}
	if ((shape.getPosition().y >= (window.getSize().y - shape.getSize().y)) || hasPlatform)
	{
		shape.move(0, 0);
		isFalling = false;
	}
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(shape);
}