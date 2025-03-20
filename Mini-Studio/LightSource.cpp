#include "LightSource.hpp"

LightSource::LightSource() {
    Vector2f position =  { 0.0f, 0.0f };
    direction = { 1.0f, 1.0f };
    float radius = 20.0f;
    shape.setPosition(position);
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color(255, 255, 0));
    shape.setOutlineColor(sf::Color(255, 165, 0));
    shape.setOutlineThickness(3.f);

    // Normaliser la direction
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    this->direction = sf::Vector2f(direction.x / length, direction.y / length);
}

void LightSource::setPosition(Vector2f newPoosition) {
    shape.setPosition(newPoosition);
}

void LightSource::setDirection(Vector2f newDirection) {
    float length = std::sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);
    direction = sf::Vector2f(newDirection.x / length, newDirection.y / length);
}

void LightSource::draw(RenderWindow& window) {
    window.draw(shape);
}