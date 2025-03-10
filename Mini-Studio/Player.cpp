#include "Player.hpp"

Player::Player() {
	isJumping = false;
    hasPlatform = false;
	shape.setSize(sf::Vector2f(40.f, 40.f));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);
	speed = 350.f;
	velocity = 100.f;
    fallingTime = 0.f;
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
        shape.move(0, -200 * deltaTime);
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        shape.move(0, 200 * deltaTime);
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        shape.move(200 * deltaTime, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Q)) {
        shape.move(-200 * deltaTime, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        isJumping = true;
    }

    if (isJumping && hasPlatform) {

    }

}

void Player::draw(sf::RenderWindow& window) {
	window.draw(shape);
}