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
	// Float members
	speed           = 350.f;
	fallingTime     = 0.f;
	dashingTime     = 0.f;
	velocity        = 0.f;
	fallingMovement = 0.f;
	jumpMovement    = 350.f;
	// Player's shape definition
	shape.setSize(sf::Vector2f(40.f, 40.f));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);
}

void Player::resize(sf::RenderWindow& window) {
	shape.setSize(sf::Vector2f(window.getSize().y / 16.f, (window.getSize().y / 8.f)));
}

void Player::gravityGestion(const float& deltaTime, RenderWindow& window) {
	// Keeps falling faster until he reaches a certain limit (gravity inversible)
	if (!invertedGravity) {
		if (shape.getPosition().y < (window.getSize().y - shape.getSize().y) && !hasPlatform && !isJumping) {
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

void Player::jumpGestion(const float& deltaTime, RenderWindow& window, const float& jumpDuration) {
	if (Keyboard::isKeyPressed(Keyboard::Space) && (shape.getPosition().y >= window.getSize().y - shape.getSize().y || hasPlatform || shape.getPosition().y <= 0)) {
		isJumping = true;
	}
	// Impulsion force slowly going down
	if (isJumping) {
		if (jumpMovement > 0) {
			jumpMovement -= deltaTime * gravityConst * 2.f;
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

void Player::update(const float& deltaTime, sf::RenderWindow& window) {
	gravityGestion(deltaTime, window);
	jumpGestion(deltaTime, window, 1.f);
	dashGestion(deltaTime, window);
	// Inputs left & right
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		isGoingLeft = false;
		isGoingRight = true;
		shape.move(speed * deltaTime, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		isGoingLeft = true;
		isGoingRight = false;
		shape.move(-speed * deltaTime, 0);
	}
}

void Player::Colision(RenderWindow& window, const float& deltaTime, vector<RectangleShape>& platforms) {
	if (shape.getPosition().x <= 0)
	{
		shape.move(speed * deltaTime, 0);
	}
	/*if (shape.getPosition().x >= window.getSize().x - shape.getSize().x)
	{
		shape.move(-speed * deltaTime, 0);
	}*/
	if (shape.getPosition().y <= 0 || hasPlatform)
	{
		shape.move(0, 0);
	}
	if (shape.getPosition().y >= window.getSize().y - shape.getSize().y || hasPlatform)
	{
		shape.move(0, 0);
	}

	int count = 0;
	for (auto& platform : platforms) {
		if (shape.getGlobalBounds().intersects(platform.getGlobalBounds())) {
			hasPlatform = true;
			count++;
		}
	}
	if (!count) {
		hasPlatform = false;
	}
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(shape);
}