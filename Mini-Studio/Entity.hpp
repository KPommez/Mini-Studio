#pragma once

#include "includeAll.hpp"

class Entity {
public:
	// rectangle pour test tech
	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;
	string type;
public:
	virtual void update(const float& deltaTime, sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

public:
	//virtual ~Entity();
};