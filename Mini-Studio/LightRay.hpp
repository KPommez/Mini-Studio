#pragma once

#include "includeAll.hpp"

class LightRay {
private:
    sf::Vector2f origin;
    sf::Vector2f direction;
    sf::VertexArray line;
    float maxLength;
    sf::Color color;

public:
    LightRay(sf::Vector2f origin, sf::Vector2f direction, float maxLength = 1000.f, sf::Color color = sf::Color(255, 255, 100, 200));

    void setOrigin(sf::Vector2f newOrigin);
    void setDirection(sf::Vector2f newDirection);

    sf::Vector2f getOrigin() const { return origin; }
    sf::Vector2f getDirection() const { return direction; }
    float getMaxLength() const { return maxLength; }

    void draw(RenderWindow& window);
};