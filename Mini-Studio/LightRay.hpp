#pragma once

#include "includeAll.hpp"

// Structure pour représenter un rayon
class Ray {
public:
    sf::Vector2f origin;
    sf::Vector2f direction;
    sf::VertexArray line;

    void create(sf::Vector2f orig, sf::Vector2f dir) {
		origin = orig;
		direction = dir;
        // Normaliser la direction
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        direction.x /= length;
        direction.y /= length;

        // Initialiser la ligne
        line = sf::VertexArray(sf::Lines, 2);
        line[0].position = origin;
        line[0].color = sf::Color(255, 218, 0);
        line[1].color = sf::Color(255, 218, 0);
    }

    void update(const sf::Vector2f& endPoint) {
        line[1].position = endPoint;
    }

    void drawSegment(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, sf::Color startColor, sf::Color endColor) {
        // Calculer la direction perpendiculaire
        sf::Vector2f rayDir = end - start;
        float rayLength = std::sqrt(rayDir.x * rayDir.x + rayDir.y * rayDir.y);
        if (rayLength < 0.001f) return; // Éviter division par zéro

        rayDir /= rayLength;
        sf::Vector2f perpDir(-rayDir.y, rayDir.x);

        // Créer un quad pour le segment avec épaisseur
        sf::VertexArray quad(sf::Quads, 4);

        // La moitié de l'épaisseur dans la direction perpendiculaire
        sf::Vector2f offset = perpDir * (10.f / 2.f);

        // Définir les quatre coins du quad
        quad[0].position = start + offset;
        quad[0].color = startColor;

        quad[1].position = end + offset;
        quad[1].color = endColor;

        quad[2].position = end - offset;
        quad[2].color = endColor;

        quad[3].position = start - offset;
        quad[3].color = startColor;

        window.draw(quad);

        // Ajouter un cercle au point d'origine pour un meilleur rendu
        sf::CircleShape circle(10.f / 2.f);
        circle.setFillColor(startColor);
        circle.setOrigin(10.f / 2.f, 10.f / 2.f);
        circle.setPosition(start);
        window.draw(circle);

        // Ajouter un cercle au point d'intersection pour un meilleur rendu
        sf::CircleShape endCircle(10.f / 2.f);
        endCircle.setFillColor(endColor);
        endCircle.setOrigin(10.f / 2.f, 10.f / 2.f);
        endCircle.setPosition(end);
        window.draw(endCircle);
    }
};

// Structure pour représenter un rectangle déplaçable
struct Mirror {
    sf::RectangleShape shape;
    bool isSelected;
    sf::Vector2f grabOffset;

    Mirror(float x, float y, float width, float height, float thickness, sf::Color color) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(thickness);
        isSelected = false;
    }

    bool contains(sf::Vector2f point) {
        sf::FloatRect bounds = shape.getGlobalBounds();
        return bounds.contains(point);
    }

    void select(sf::Vector2f mousePos) {
        isSelected = true;
        grabOffset = shape.getPosition() - mousePos;
    }

    void deselect() {
        isSelected = false;
    }

    void move(sf::Vector2f mousePos) {
        if (isSelected) {
            shape.setPosition(mousePos + grabOffset);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getSegments() {
        sf::Vector2f pos = shape.getPosition();
        sf::Vector2f size = shape.getSize();
        float rotationAngle = shape.getRotation();

        // Convert the rotation angle to radians
        float radians = rotationAngle * (M_PI / 180.f);

        // Calculate the cosine and sine of the rotation angle
        float cosAngle = std::cos(radians);
        float sinAngle = std::sin(radians);

        // Define the original points of the rectangle relative to the center
        std::vector<sf::Vector2f> originalPoints = {
            sf::Vector2f(-size.x / 2.f, -size.y / 2.f), // Top-left
            sf::Vector2f(size.x / 2.f, -size.y / 2.f),  // Top-right
            sf::Vector2f(size.x / 2.f, size.y / 2.f),   // Bottom-right
            sf::Vector2f(-size.x / 2.f, size.y / 2.f)   // Bottom-left
        };

        // Rotate each point around the center
        std::vector<sf::Vector2f> rotatedPoints;
        for (const auto& point : originalPoints) {
            sf::Vector2f rotatedPoint;
            rotatedPoint.x = point.x * cosAngle - point.y * sinAngle;
            rotatedPoint.y = point.x * sinAngle + point.y * cosAngle;
            rotatedPoints.push_back(rotatedPoint + pos);
        }

        // Create the segments from the rotated points
        return {
            // Top segment
            { rotatedPoints[0], rotatedPoints[1] },
            // Right segment
            { rotatedPoints[1], rotatedPoints[2] },
            // Bottom segment
            { rotatedPoints[2], rotatedPoints[3] },
            // Left segment
            { rotatedPoints[3], rotatedPoints[0] }
        };
    }
};

// Fonction pour calculer l'intersection entre un rayon et un segment
bool raySegmentIntersection(
    const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection,
    const sf::Vector2f& segStart, const sf::Vector2f& segEnd,
    sf::Vector2f& intersection, float& distance
) {
    sf::Vector2f segDir = segEnd - segStart;
    sf::Vector2f segNormal(-segDir.y, segDir.x);
    float segLength = std::sqrt(segDir.x * segDir.x + segDir.y * segDir.y);
    segDir /= segLength;
    segNormal /= segLength;

    float dotProduct = rayDirection.x * segNormal.x + rayDirection.y * segNormal.y;

    // Si parallèle, pas d'intersection
    if (std::abs(dotProduct) < 0.0001f) {
        return false;
    }

    sf::Vector2f toSeg = segStart - rayOrigin;
    float t = (toSeg.x * segNormal.x + toSeg.y * segNormal.y) / dotProduct;

    // L'intersection est derrière le rayon
    if (t < 0) {
        return false;
    }

    // Calculer le point d'intersection
    intersection = rayOrigin + rayDirection * t;

    // Vérifier si l'intersection est sur le segment
    sf::Vector2f toIntersection = intersection - segStart;
    float projOnSeg = toIntersection.x * segDir.x + toIntersection.y * segDir.y;

    if (projOnSeg < 0 || projOnSeg > segLength) {
        return false;
    }

    distance = t;
    return true;
}

// Fonction pour calculer la direction réfléchie
sf::Vector2f reflect(const sf::Vector2f& direction, const sf::Vector2f& normal) {
    float dot = direction.x * normal.x + direction.y * normal.y;
    return sf::Vector2f(
        direction.x - 2 * dot * normal.x,
        direction.y - 2 * dot * normal.y
    );
}

// Fonction pour ajouter un rectangle flottant à la position du clic
Mirror createRectangle(sf::Vector2f position, sf::Vector2f size) {
    return Mirror(
        position.x,
        position.y,
        size.x, size.y,
        2.f,            // Thickness
        sf::Color::White
    );
}

void updateMirrors(vector<Mirror>& mirrors) {
    for (auto& mirror : mirrors) {
        
    }
}