#pragma once

#include "Entity.hpp"
#include "Player.hpp"

class SolarPanel : public Entity {
public:
	SolarPanel();
	void create(Vector2f pos, RenderWindow& window);
	void update(const float& deltaTime, RenderWindow& window) override;
	void draw(RenderWindow& window) override;
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getSegments();
	bool isOn;
	Sprite spriteOff, spriteOn, spriteGlobal;
	Texture textureOff, textureOn;
	Vector2f position; // Position of the solar panel
};