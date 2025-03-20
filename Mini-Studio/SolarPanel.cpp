#include "SolarPanel.hpp"

SolarPanel::SolarPanel(Vector2f pos, Player* players, RenderWindow& window) {
	player = players;
	position = pos;
	shape.setPosition(pos);
	shape.setFillColor(Color::Transparent);
	shape.setSize(Vector2f(50.0f, 300.0f));
	faisceau = 0;
	
}

void SolarPanel::draw(RenderWindow& window) {
	window.draw(shape); // Draw the shape
}
void SolarPanel::update(const float& deltaTime, RenderWindow& window) {

}