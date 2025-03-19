#include "LuminousBeam.hpp"

LuminousBeam::LuminousBeam() : lineThickness(10.0f) {} // Initialiser l'épaisseur du rayon

void LuminousBeam::create(const sf::Vector2f& startingPoint) {
    // Définir les rectangles avec rotation
    sf::RectangleShape rect1(sf::Vector2f(200, 200));
    rect1.setPosition(100, 100);
    rect1.setFillColor(sf::Color::Transparent);
    rect1.setOutlineThickness(2);
    rect1.setOutlineColor(sf::Color::White);
    rect1.setRotation(30); // Rotation de 30 degrés

    sf::RectangleShape rect2(sf::Vector2f(200, 200));
    rect2.setPosition(500, 500);
    rect2.setFillColor(sf::Color::Transparent);
    rect2.setOutlineThickness(2);
    rect2.setOutlineColor(sf::Color::White);
    rect2.setRotation(-45); // Rotation de -45 degrés

    surfaces.push_back(rect1);
    surfaces.push_back(rect2);

    initialBeamPosition = startingPoint;
    beamDirection = { 1.0f, 0.5f }; // Direction initiale horizontale
    updateTrajectory(); // Calculer la trajectoire initiale
}

void LuminousBeam::setSurfaceRotation(size_t index, float angle) {
    if (index < surfaces.size()) {
        surfaces[index].setRotation(angle);
    }
}

float LuminousBeam::getSurfaceRotation(size_t index) const {
    if (index < surfaces.size()) {
        return surfaces[index].getRotation();
    }
    return 0.0f;
}

sf::Vector2f LuminousBeam::reflectVector(const sf::Vector2f& incident, const sf::Vector2f& normal) {
    float dotProduct = 2.0f * (incident.x * normal.x + incident.y * normal.y);
    return incident - sf::Vector2f(dotProduct * normal.x, dotProduct * normal.y);
}

bool LuminousBeam::checkIntersection(const sf::RectangleShape& rectangle, const sf::Vector2f& rayPos, const sf::Vector2f& rayDir, sf::Vector2f& intersection, sf::Vector2f& normal) {
    sf::FloatRect bounds = rectangle.getGlobalBounds();
    float angle = rectangle.getRotation() * 3.14159265358979323846f / 180.0f; // Convertir en radians

    // Calculer la normale en fonction de l'angle de rotation
    normal = sf::Vector2f(std::cos(angle), std::sin(angle));

    // Ajuster les limites pour tenir compte de l'épaisseur de la bordure
    float outlineOffset = rectangle.getOutlineThickness();
    sf::FloatRect adjustedBounds(bounds.left + outlineOffset, bounds.top + outlineOffset,
        bounds.width - 2 * outlineOffset, bounds.height - 2 * outlineOffset);

    // Vérifier les intersections avec les bords ajustés du rectangle
    sf::Vector2f rotatedRayDir = sf::Vector2f(rayDir.x * std::cos(angle) - rayDir.y * std::sin(angle),
        rayDir.x * std::sin(angle) + rayDir.y * std::cos(angle));

    if (rotatedRayDir.x != 0) {
        float tLeft = (adjustedBounds.left - rayPos.x) / rotatedRayDir.x;
        float tRight = (adjustedBounds.left + adjustedBounds.width - rayPos.x) / rotatedRayDir.x;
        if (tLeft >= 0 && tLeft <= 1) {
            intersection = rayPos + rayDir * tLeft;
            if (intersection.y >= adjustedBounds.top && intersection.y <= adjustedBounds.top + adjustedBounds.height) {
                normal = sf::Vector2f(-std::cos(angle), -std::sin(angle));
                return true;
            }
        }
        if (tRight >= 0 && tRight <= 1) {
            intersection = rayPos + rayDir * tRight;
            if (intersection.y >= adjustedBounds.top && intersection.y <= adjustedBounds.top + adjustedBounds.height) {
                normal = sf::Vector2f(std::cos(angle), std::sin(angle));
                return true;
            }
        }
    }

    if (rotatedRayDir.y != 0) {
        float tTop = (adjustedBounds.top - rayPos.y) / rotatedRayDir.y;
        float tBottom = (adjustedBounds.top + adjustedBounds.height - rayPos.y) / rotatedRayDir.y;
        if (tTop >= 0 && tTop <= 1) {
            intersection = rayPos + rayDir * tTop;
            if (intersection.x >= adjustedBounds.left && intersection.x <= adjustedBounds.left + adjustedBounds.width) {
                normal = sf::Vector2f(-std::sin(angle), -std::cos(angle));
                return true;
            }
        }
        if (tBottom >= 0 && tBottom <= 1) {
            intersection = rayPos + rayDir * tBottom;
            if (intersection.x >= adjustedBounds.left && intersection.x <= adjustedBounds.left + adjustedBounds.width) {
                normal = sf::Vector2f(std::sin(angle), std::cos(angle));
                return true;
            }
        }
    }

    return false;
}

void LuminousBeam::updateTrajectory() {
    beamPath.clear();
    sf::Vector2f currentPosition = initialBeamPosition;
    sf::Vector2f currentDirection = beamDirection;
    beamPath.push_back(currentPosition);

    const float stepSize = 1.0f; // Réduire la distance parcourue par itération
    const int maxIterations = 3000; // Augmenter le nombre d'itérations

    for (int i = 0; i < maxIterations; ++i) {
        bool collisionDetected = false;
        for (const auto& rectangle : surfaces) {
            sf::Vector2f intersection;
            sf::Vector2f normal;

            if (checkIntersection(rectangle, currentPosition, currentDirection, intersection, normal)) {
                currentDirection = reflectVector(currentDirection, normal);
                currentPosition = intersection;
                beamPath.push_back(intersection);
                collisionDetected = true;
                break;
            }
        }

        if (!collisionDetected) {
            currentPosition += currentDirection * stepSize;
            beamPath.push_back(currentPosition);
        }
    }
}

void LuminousBeam::draw(sf::RenderWindow& window) {
    for (const auto& rectangle : surfaces) {
        window.draw(rectangle);
    }

    // Dessiner des rectangles pour simuler l'épaisseur du rayon
    for (size_t i = 1; i < beamPath.size(); ++i) {
        sf::Vector2f start = beamPath[i - 1];
        sf::Vector2f end = beamPath[i];

        sf::Vector2f direction = end - start;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        sf::Vector2f perpendicular(-direction.y, direction.x);
        perpendicular *= lineThickness / 2.0f;

        sf::RectangleShape line(sf::Vector2f(length, lineThickness));
        line.setFillColor(sf::Color::Yellow);
        line.setPosition(start.x + perpendicular.x, start.y + perpendicular.y);

        float angle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159265358979323846f;
        line.setRotation(angle);

        window.draw(line);
    }
}