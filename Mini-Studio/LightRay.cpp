#include "LightRay.hpp"

LightRay::LightRay(sf::Vector2f origin, sf::Vector2f direction, float maxLength, sf::Color color)
    : origin(origin), direction(direction), maxLength(maxLength), color(color) {
    // Normaliser la direction
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    this->direction = sf::Vector2f(direction.x / length, direction.y / length);

    // Initialiser la ligne du rayon
    line = sf::VertexArray(sf::Lines, 2);
    line[0].position = origin;
    line[0].color = color;
    line[1].position = origin + this->direction * maxLength;
    line[1].color = color;
}

void LightRay::setOrigin(sf::Vector2f newOrigin) {
    origin = newOrigin;
    line[0].position = origin;
    line[1].position = origin + direction * maxLength;
}

void LightRay::setDirection(sf::Vector2f newDirection) {
    // Normaliser la direction
    float length = std::sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);
    direction = sf::Vector2f(newDirection.x / length, newDirection.y / length);
    line[1].position = origin + direction * maxLength;
}

void LightRay::draw(sf::RenderWindow& window) {
    window.draw(line);
}