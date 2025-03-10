#include "Player.hpp"

Player::Player() {
	shape.setSize(sf::Vector2f(40.f, 40.f));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);
	speed = 200.f;
	velocity = 100.f;
}

void Player::update(const float& deltaTime) {
	cout << (1.f / deltaTime) << endl;
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(shape);
}