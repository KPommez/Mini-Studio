#include "Player.hpp"

Player::Player() {
	shape.setSize(sf::Vector2f(40.f, 40.f));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);
	speed = 350.f;
	gravity = 100.f;
}

void Player::update(const float& deltaTime) {
	

}

void Player::draw(sf::RenderWindow& window) {
	window.draw(shape);
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