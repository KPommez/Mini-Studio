#pragma once

#include "Mirror.hpp"

class LuminousBeam {
public:
	LuminousBeam();
	void create(const Vector2f& startingPoint, const int& thickness, const Color& color);
	void rotateBeam(const float& deltaTime, const Mirror& mirror);
	void draw(RenderWindow& window);

private:
	ConvexShape shape;
	Vector2f m_startingPoint;
	int m_thickness;
	int m_length;
	Color m_fillColor;
};