#pragma once

#include "includeAll.hpp"

class Entity {
public:
	RectangleShape shape;
	Texture texture;
	Sprite sprite;
	string type;

public:
	virtual void update(const float& deltaTime, RenderWindow& window) = 0;
	virtual void draw(RenderWindow& window) = 0;

public:
	//virtual ~Entity();
};