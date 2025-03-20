#pragma once

#include "includeAll.hpp"

// Classe pour représenter la cible (où le rayon doit arriver)
class Target {
private:
    CircleShape shape;
    bool isLit;

public:
    Target();

    Vector2f getPosition() const { return shape.getPosition(); }
    float getRadius() const { return shape.getRadius(); }

    void setLit(bool lit);
    bool isIlluminated() const { return isLit; }

    void draw(RenderWindow& window);
};