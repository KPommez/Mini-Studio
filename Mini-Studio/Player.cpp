#include "Player.hpp"

Player::Player() {
	isJumping = false;
    hasPlatform = false;
	shape.setSize(sf::Vector2f(40.f, 40.f));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);
	speed = 350.f;
	velocity = 0.f;
    fallingMovement = 0.f;
	jumpMovement = 5.f;
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

	// Tombe de plus en plus vite jusqu'à atteindre une limite.
    if (shape.getPosition().y < (window.getSize().y - shape.getSize().y) && !hasPlatform && !isJumping) {
        if(fallingMovement < maxFallingForce)
            fallingMovement += deltaTime * gravityConst;
        shape.move(0, fallingMovement);
    }
    else {
        fallingMovement = 0.f;
    }

	// Inputs gauche/droite
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        shape.move(speed * deltaTime, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Q)) {
        shape.move(-speed * deltaTime, 0);
    }

	// Input spacebar pour jump + vérifications d'éligibilité
    if (Keyboard::isKeyPressed(Keyboard::Space) && (shape.getPosition().y >= window.getSize().y - shape.getSize().y || hasPlatform)) {
        isJumping = true;
    }

	// Force d'impulsion du saut qui descend graduellement
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