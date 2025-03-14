#include "Eolienne.hpp"

Eolienne::Eolienne(Vector2f pos) {
	Position = pos;
	shape.setPosition(pos);
	shape.setFillColor(Color::Cyan);
	shape.setSize(Vector2f(50.0f, 50.0f));
}

void Eolienne::update(const float& deltaTime, RenderWindow& window) {}

void Eolienne::draw(RenderWindow& window) {
	window.draw(shape);
}