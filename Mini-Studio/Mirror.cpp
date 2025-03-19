#include "Mirror.hpp"

Mirror::Mirror(const Vector2f& pos, const Vector2f& size, const float& startingAngle) {
	m_pos = pos;
	m_size = size;
	m_angle = startingAngle;
	m_isTrigerred = false;
}

Vector2f Mirror::getPosition() const {
	return m_pos;
}

void Mirror::rotate(const float& deltaTime) {
	sprite.rotate(100.f * deltaTime);
	m_angle = sprite.getRotation();
}

void Mirror::draw(RenderWindow& window) {
	window.draw(sprite);
}