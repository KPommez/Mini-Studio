#pragma once

#include "includeAll.hpp"

class Mirror {
public:
	Mirror(const Vector2f& pos, const Vector2f& size, const float& startingAngle);

public:
	void rotate(const float& deltaTime);
	void draw(RenderWindow& window);

private:
	RectangleShape hitbox;
	Texture texture;
	Sprite sprite;
	Vector2f       m_size;
	Vector2f       m_pos;
	float          m_angle;
	bool           m_isTrigerred;
};