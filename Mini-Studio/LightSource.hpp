#pragma once

#include "includeAll.hpp"

// Classe pour représenter la source de lumière (le soleil)
class LightSource {
private:
    sf::CircleShape shape;
    sf::Vector2f direction;

public:
    LightSource();

    sf::Vector2f getPosition() const { return shape.getPosition(); }
    sf::Vector2f getDirection() const { return direction; }

    void setPosition(sf::Vector2f newPosition);
    void setDirection(sf::Vector2f newDirection);
    void draw(RenderWindow& window);
};