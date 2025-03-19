#pragma once

#include "includeAll.hpp"

class LuminousBeam {
public:
    LuminousBeam();
    void create(const sf::Vector2f& startingPoint);
    void updateTrajectory();
    void draw(sf::RenderWindow& window);
    void setSurfaceRotation(size_t index, float angle);
    float getSurfaceRotation(size_t index) const;

private:
    bool checkIntersection(const sf::RectangleShape& rectangle, const sf::Vector2f& rayPos, const sf::Vector2f& rayDir, sf::Vector2f& intersection, sf::Vector2f& normal);
    sf::Vector2f reflectVector(const sf::Vector2f& incident, const sf::Vector2f& normal);

private:
    std::vector<sf::RectangleShape> surfaces;
    sf::Vector2f initialBeamPosition;
    sf::Vector2f beamDirection;
    std::vector<sf::Vector2f> beamPath;
    float lineThickness; // Épaisseur du rayon
};