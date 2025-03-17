#include "LuminousBeam.hpp"

LuminousBeam::LuminousBeam() {}

void LuminousBeam::create(const Vector2f& startingPoint, const int& thickness, const Color& color) {
	m_startingPoint = /*startingPoint*/Vector2f{900.f, 900.f};
	m_thickness = thickness;
	m_fillColor = color;
	m_length = 2000;                                                                      // Mettre INT_MAX quand ça marchera
	shape.setPointCount(4);
	shape.setPoint(0, m_startingPoint);                                                   // Haut gauche
	shape.setPoint(1, m_startingPoint + Vector2f{ (float)m_thickness, 0.f });             // Haut droite
	shape.setPoint(2, m_startingPoint + Vector2f{ 0.f,                (float)m_length }); // Bas gauche
	shape.setPoint(3, m_startingPoint + Vector2f{ (float)m_thickness, (float)m_length }); // Bas droite
	shape.setFillColor(m_fillColor);
}

void LuminousBeam::rotateBeam(const float& deltaTime, const Mirror& mirror) {

}

void LuminousBeam::draw(RenderWindow& window) {
	window.draw(shape);
}