#include "Pétrifeu.hpp"

Petrifeu::Petrifeu(Vector2f pos, Player* players) {
	player = players;
	position = pos;
	shape.setPosition(pos);
	shape.setFillColor(Color::Magenta);
	shape.setSize({ 50, 50 });
	zone.setSize({ 200,300 });
	zone.setFillColor(Color::White);
}
void Petrifeu::update(const float& deltaTime, RenderWindow& window) {
	shape.setPosition({ player->shape.getPosition().x + 700, player->shape.getPosition().y- 200});
	zone.setPosition({ player->shape.getPosition().x + 900, 0});
}

void Petrifeu::draw(RenderWindow& window) {
	window.draw(zone);
	window.draw(shape);
}