#include "Player.hpp"

Player::Player() {
	// Boolean members
	isGoingLeft  = false;
	isGoingRight = false;
	isJumping    = false;
    hasPlatform  = false;
    isDashing    = false;
	// Float members
	speed           = 350.f;
	fallingTime     = 0.f;
	dashingTime     = 0.f;
	velocity        = 0.f;
	fallingMovement = 0.f;
	jumpMovement    = 5.f;
	// Player's shape definition
	shape.setSize(sf::Vector2f(40.f, 40.f));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);
	// temporary : testing collisions
	for (int i = 1; i < 11; ++i) {
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(250.f, 30.f));
		rect.setPosition(i * 250.f, 1080 - (i * 60.f));
		rect.setFillColor(sf::Color::White);
		platforms.push_back(rect);
	}
}

void Player::resize(sf::RenderWindow& window) {
	shape.setSize(sf::Vector2f(window.getSize().x / 20.f, (window.getSize().y / 4.f) * (3.f/4.f)));
}

void Player::update(const float& deltaTime, sf::RenderWindow& window) {

	// Keeps falling faster until he reaches a certain limit
    if (shape.getPosition().y < (window.getSize().y - shape.getSize().y) && !hasPlatform && !isJumping) {
        if(fallingMovement < maxFallingForce)
            fallingMovement += deltaTime * gravityConst;
        shape.move(0, fallingMovement);
    }
    else {
        fallingMovement = 0.f;
    }

	// Inputs left & right
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        isGoingRight = true;
        isGoingLeft = false;
        shape.move(speed * deltaTime, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Q)) {
        isGoingLeft = true;
        isGoingRight = false;
        shape.move(-speed * deltaTime, 0);
    }

	// Input spacebar for jumping / F for dashing (once every 2 seconds, temporary timing)
    if (Keyboard::isKeyPressed(Keyboard::Space) && (shape.getPosition().y >= window.getSize().y - shape.getSize().y || hasPlatform)) {
        isJumping = true;
    }if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
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
            shape.move((float)-deltaTime * dashSpeed, 0);
        }
        else if (isGoingRight && dashingTime < 0.25f)
        {
            shape.move((float)deltaTime * dashSpeed, 0);
        }
        else
        {
            isDashing = false;
        }
    }

	// Impulsion force slowly going down
	if (isJumping) {
		if (jumpMovement > 0)
			jumpMovement -= deltaTime * jumpForce;
		else {
			isJumping = false;
		}
		shape.move(0, -jumpMovement);
	}
	else {
		jumpMovement = 5.f;
	}
}

void Player::Colision(RenderWindow& window, const float& deltaTime) {
	// Collisions with the window borders
	if (shape.getPosition().x <= 0)
	{
		shape.move(speed * deltaTime, 0);
	}
	if (shape.getPosition().x >= window.getSize().x - shape.getSize().x)
	{
		shape.move(-speed * deltaTime, 0);
	}
	if (shape.getPosition().y <= 0)
	{
		shape.move(0, speed * deltaTime);
	}
	if (shape.getPosition().y >= window.getSize().y - shape.getSize().y)
	{
		shape.move(0, 0);
	}

	// Collisions with platforms
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
	for (auto& platform : platforms) {
		window.draw(platform);
	}
}