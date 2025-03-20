#pragma once

#include "includeAll.hpp"
#include "LightRay.hpp"

// Classe pour représenter un miroir (rectangle orientable)
class Mirror {
private:
    sf::RectangleShape shape;
    sf::Vector2f normal; // Vecteur normal au miroir

    void updateNormal();

public:
    Mirror(sf::Vector2f position, sf::Vector2f size, float rotation = 0.f);

    void setRotation(float rotation);
    void rotate(float angle);

    sf::Vector2f getPosition() const { return shape.getPosition(); }
    sf::Vector2f getSize() const { return shape.getSize(); }
    float getRotation() const { return shape.getRotation(); }
    sf::Vector2f getNormal() const { return normal; }

    bool intersect(const LightRay& ray, sf::Vector2f& intersection, sf::Vector2f& reflectedDirection) const;

    void draw(sf::RenderWindow& window);
};