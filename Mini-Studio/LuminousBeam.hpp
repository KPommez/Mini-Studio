#pragma once

#include "Mirror.hpp"

class LuminousBeam {
public:
	LuminousBeam();
	void create(const Vector2f& startingPoint, const int& thickness, const Color& color);
	void update();
	void draw(RenderWindow& window);

private:
	sf::Vector2f reflectVector(const sf::Vector2f& incident, const sf::Vector2f& normal);

private:
	ConvexShape surface;
	Vector2f m_startingPoint;
	Vector2f m_direction;
	int m_thickness;
	int m_length;
	Color m_fillColor;
	vector<Vector2f> m_path;
};