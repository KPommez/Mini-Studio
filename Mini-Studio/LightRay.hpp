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
        line[0].color = sf::Color::Red;
        line[1].color = sf::Color::Yellow;
    }

    void update(const sf::Vector2f& endPoint) {
        line[1].position = endPoint;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(line);
    }
};

// Structure pour représenter un rectangle déplaçable
struct Mirror {
    sf::RectangleShape shape;
    bool isSelected;
    sf::Vector2f grabOffset;

    Mirror(float x, float y, float width, float height, sf::Color color) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2.f);
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

        return {
            // Segment haut
            { sf::Vector2f(pos.x, pos.y), sf::Vector2f(pos.x + size.x, pos.y) },
            // Segment droite
            { sf::Vector2f(pos.x + size.x, pos.y), sf::Vector2f(pos.x + size.x, pos.y + size.y) },
            // Segment bas
            { sf::Vector2f(pos.x + size.x, pos.y + size.y), sf::Vector2f(pos.x, pos.y + size.y) },
            // Segment gauche
            { sf::Vector2f(pos.x, pos.y + size.y), sf::Vector2f(pos.x, pos.y) }
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
Mirror createRectangle(sf::Vector2f position) {
    return Mirror(
        position.x,
        position.y,
        50.f, 100.f, // taille
        sf::Color(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55, 200) // couleur aléatoire
    );
}