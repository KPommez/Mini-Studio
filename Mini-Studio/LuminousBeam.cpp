#include "LuminousBeam.hpp"

LuminousBeam::LuminousBeam() {}

void LuminousBeam::create(const Vector2f& startingPoint, const int& thickness, const Color& color) {
	m_startingPoint = startingPoint;
	m_path.push_back(m_startingPoint);
	m_thickness = thickness;
	m_fillColor = color;
	m_length = 2000;
	surface.setPointCount(4);
	surface.setPoint(0, sf::Vector2f(0, 0));
	surface.setPoint(1, sf::Vector2f(1920, 100));
	surface.setPoint(2, sf::Vector2f(1200, 200));
	surface.setPoint(3, sf::Vector2f(0, 300));
	surface.setFillColor(sf::Color::Transparent);
	surface.setOutlineThickness(2);
	surface.setOutlineColor(sf::Color::Transparent);
}

sf::Vector2f LuminousBeam::reflectVector(const sf::Vector2f& incident, const sf::Vector2f& normal) {
	float dotProduct = 2.0f * (incident.x * normal.x + incident.y * normal.y);
	return incident - sf::Vector2f(dotProduct * normal.x, dotProduct * normal.y);
}

void LuminousBeam::update() {
	// Mise à jour de la position du faisceau lumineux
	m_startingPoint += m_direction;
	m_path.push_back(m_startingPoint);

	// Détection des collisions avec la surface
	for (size_t i = 0; i < surface.getPointCount(); ++i) {
		sf::Vector2f edge = surface.getPoint(i) - surface.getPoint((i + 1) % surface.getPointCount());
		sf::Vector2f normal(-edge.y, edge.x);
		normal /= std::sqrt(normal.x * normal.x + normal.y * normal.y);

		sf::Vector2f toBeam = m_startingPoint - surface.getPoint(i);
		if (toBeam.x * normal.x + toBeam.y * normal.y < 0) {
			normal = -normal;
		}

		if (toBeam.x * normal.x + toBeam.y * normal.y < 0.0f) {
			m_direction = reflectVector(m_direction, normal);
			break;
		}
	}
}

void LuminousBeam::draw(RenderWindow& window) {
	window.draw(surface);
	// Dessin du trajet complet du faisceau lumineux
	sf::VertexArray beamTrail(sf::Lines, m_path.size());
	for (size_t i = 0; i < m_path.size(); ++i) {
		beamTrail[i].position = m_path[i];
		beamTrail[i].color = sf::Color::Blue;
	}
	window.draw(beamTrail);
}