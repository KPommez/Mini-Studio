#include "SolarPanel.hpp"

SolarPanel::SolarPanel() {
	isOn = false;
}

void SolarPanel::create(Vector2f pos, RenderWindow& window) {
	position = pos;
	isOn = false;
	shape.setPosition(pos);
	shape.setFillColor(Color::Transparent);
	shape.setSize(Vector2f(300.0f, 260.0f));
	textureOff.loadFromFile("Assets/SolarPanel/solarPanelOff.png");
	textureOn.loadFromFile("Assets/SolarPanel/solarPanelOn.png");
	spriteOff.setScale(0.3f, 0.3f);
	spriteOn.setScale (0.3f, 0.3f);
	spriteOff.setTexture(textureOff);
	spriteOn.setTexture(textureOn);
	spriteOff.setPosition(pos);
	spriteOn.setPosition(pos);
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

std::vector<std::pair<sf::Vector2f, sf::Vector2f>> SolarPanel::getSegments() {
	sf::Vector2f pos = spriteGlobal.getPosition();
	sf::Vector2f size = { spriteGlobal.getGlobalBounds().width, spriteGlobal.getGlobalBounds().height };

	return {
		{ sf::Vector2f(pos.x, pos.y), sf::Vector2f(pos.x + size.x, pos.y) },
		{ sf::Vector2f(pos.x + size.x, pos.y), sf::Vector2f(pos.x + size.x, pos.y + size.y) },
		{ sf::Vector2f(pos.x + size.x, pos.y + size.y), sf::Vector2f(pos.x, pos.y + size.y) },
		{ sf::Vector2f(pos.x, pos.y + size.y), sf::Vector2f(pos.x, pos.y) }
	};
}

void SolarPanel::draw(RenderWindow& window) {
	window.draw(spriteGlobal);
}