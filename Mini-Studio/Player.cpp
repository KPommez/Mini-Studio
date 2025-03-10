#include "Player.hpp"

Player::Player() {
	isJumping = false;
    hasPlatform = false;
    isDashing = false;
	shape.setSize(sf::Vector2f(40.f, 40.f));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);
	speed = 350.f;
    fallingTime = 0.f;
    dashingTime = 0;
}

void Player::update(const float& deltaTime, sf::RenderWindow& window) {

    if (shape.getPosition().y < (window.getSize().y - shape.getSize().y) && !hasPlatform) {
        if(fallingTime < maxFallingSpeed)
            fallingTime += deltaTime * gravityConst;
        shape.move(0, fallingTime);
    }
    else {
        fallingTime = 0.f;
    }

    if (Keyboard::isKeyPressed(Keyboard::Z)) {
        shape.move(0, -speed * deltaTime);
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        shape.move(0, speed * deltaTime);
    }
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
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        isJumping = true;
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
            shape.move(-dashSpeed, 0);
        }
        else if (isGoingRight && dashingTime < 0.25f)
        {
            shape.move(dashSpeed, 0);
        }
        else
        {
            isDashing = false;
        }
    }
    
}

void Player::Colision(RenderWindow& window, const float& deltaTime) {
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
		shape.move(0, -speed * deltaTime);
	}
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(shape);
}