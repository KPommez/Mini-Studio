#pragma once

#include "includeAll.hpp"

class Entity {
public:
	// rectangle pour test tech
	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	virtual void update(const float& deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

public:
	//virtual ~Entity();
};