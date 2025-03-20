#include "SolarPanel.hpp"

SolarPanel::SolarPanel(Vector2f pos, Player* players, RenderWindow& window) {
	player = players;
	position = pos;
	shape.setPosition(pos);
	shape.setFillColor(Color::Transparent);
	shape.setSize(Vector2f(50.0f, 300.0f));
	faisceau = 0;
	textureOff.loadFromFile("Assets/SolarPanel/solarPanelOff.png");
	textureOn.loadFromFile("Assets/SolarPanel/solarPanelOn.png");
	spriteOff.setTexture(textureOff);
	spriteOn.setTexture(textureOn);
}

void SolarPanel::draw(RenderWindow& window) {
	window.draw(shape); // Draw the shape
}
void SolarPanel::update(const float& deltaTime, RenderWindow& window) {
	switch (isOn) {
	case true:
		spriteGlobal = spriteOn;
		break;
	case false:
		spriteGlobal = spriteOff;
		break;
	}
}