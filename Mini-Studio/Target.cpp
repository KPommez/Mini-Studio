#include "Target.hpp"

Target::Target() {
    isLit = false;
    Vector2f position = {1500, 1000};
    float radius = 15.0f;
    shape.setPosition(position);
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color(100, 100, 100));
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(2.f);
}

void Target::setLit(bool lit) {
    isLit = lit;
    if (isLit) {
        shape.setFillColor(sf::Color(255, 100, 100));
        shape.setOutlineColor(sf::Color::Yellow);
    }
    else {
        shape.setFillColor(sf::Color(100, 100, 100));
        shape.setOutlineColor(sf::Color::Red);
    }
}

void Target::draw(sf::RenderWindow& window) {
    window.draw(shape);
}