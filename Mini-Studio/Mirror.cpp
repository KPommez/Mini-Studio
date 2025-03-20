#include "Game.hpp"

Mirror::Mirror(sf::Vector2f position, sf::Vector2f size, float rotation) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setOrigin(size.x / 2.f, size.y / 2.f); // Centrer l'origine
    shape.setRotation(rotation);
    shape.setFillColor(sf::Color(200, 200, 200));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.f);
    updateNormal();
}

void Mirror::updateNormal() {
    float angle = shape.getRotation() * M_PI / 180.f;
    normal = sf::Vector2f(std::sin(angle), -std::cos(angle));
}

void Mirror::setRotation(float rotation) {
    shape.setRotation(rotation);
    updateNormal();
}

void Mirror::rotate(float angle) {
    shape.rotate(angle);
    updateNormal();
}

bool Mirror::intersect(const LightRay& ray, sf::Vector2f& intersection, sf::Vector2f& reflectedDirection) const {
    // Récupérer les données du rayon
    sf::Vector2f rayOrigin = ray.getOrigin();
    sf::Vector2f rayDirection = ray.getDirection();

    // Calculer les points du rectangle
    sf::Transform transform = shape.getTransform();
    sf::Vector2f points[4] = {
        shape.getTransform().transformPoint(shape.getPoint(0)),
        shape.getTransform().transformPoint(shape.getPoint(1)),
        shape.getTransform().transformPoint(shape.getPoint(2)),
        shape.getTransform().transformPoint(shape.getPoint(3))
    };

    // Vérifier l'intersection avec chaque segment du rectangle
    for (int i = 0; i < 4; ++i) {
        sf::Vector2f p1 = points[i];
        sf::Vector2f p2 = points[(i + 1) % 4];

        // Calculer l'intersection entre le rayon et le segment
        sf::Vector2f s1 = p2 - p1;
        sf::Vector2f s2 = rayDirection;

        float denominator = -s2.x * s1.y + s1.x * s2.y;
        if (std::abs(denominator) < 0.0001f) continue; // Lignes parallèles

        float s = (-s1.y * (rayOrigin.x - p1.x) + s1.x * (rayOrigin.y - p1.y)) / denominator;
        float t = (s2.x * (rayOrigin.y - p1.y) - s2.y * (rayOrigin.x - p1.x)) / denominator;

        if (s >= 0 && s <= ray.getMaxLength() && t >= 0 && t <= 1) {
            intersection = rayOrigin + s * rayDirection;

            sf::Vector2f edgeVector = s1 / std::sqrt(s1.x * s1.x + s1.y * s1.y);
            sf::Vector2f localNormal = sf::Vector2f(-edgeVector.y, edgeVector.x);
            // Formule de réflexion: R = I - 2 * (I·N) * N
            float dot = rayDirection.x * localNormal.x + rayDirection.y * localNormal.y;
            reflectedDirection = rayDirection - 2.f * dot * localNormal;
            return true;
        }
    }

    return false;
}

void Mirror::draw(RenderWindow& window) {
    window.draw(shape);
}

// GAME

// Fonction pour tracer le chemin du rayon avec des rebonds
std::vector<LightRay> Game::traceLightPath(const LightSource& source, const std::vector<Mirror>& mirrors, Target& target, int maxReflections) {
    std::vector<LightRay> rays;

    sf::Vector2f currentOrigin = source.getPosition();
    sf::Vector2f currentDirection = source.getDirection();

    target.setLit(false);

    sf::Vector2f testIntersection;
    sf::Vector2f testReflected;

    for (int i = 0; i < maxReflections; ++i) {
        LightRay ray(currentOrigin, currentDirection);
        rays.push_back(ray);

        // Trouver le miroir le plus proche avec lequel le rayon actuel va intersecter
        float closestDistance = std::numeric_limits<float>::max();
        bool hasIntersection = false;
        sf::Vector2f closestIntersection;
        sf::Vector2f reflectedDir;
        int closestMirrorIndex = -1;

        for (size_t j = 0; j < mirrors.size(); ++j) {
            sf::Vector2f intersection;
            sf::Vector2f reflectedDirection;

            if (mirrors[j].intersect(ray, intersection, reflectedDirection)) {
                float distance = std::sqrt(std::pow(intersection.x - currentOrigin.x, 2) +
                    std::pow(intersection.y - currentOrigin.y, 2));

                if (distance < closestDistance) {
                    closestDistance = distance;
                    closestIntersection = intersection;
                    reflectedDir = reflectedDirection;
                    closestMirrorIndex = j;
                    hasIntersection = true;
                }
            }
        }

        // Vérifier si le rayon atteint la cible
        sf::Vector2f targetPos = target.getPosition();
        float targetRadius = target.getRadius();

        // Vérifier l'intersection avec la cible
        sf::Vector2f v = targetPos - currentOrigin;
        float a = currentDirection.x * currentDirection.x + currentDirection.y * currentDirection.y;
        float b = 2.0f * (v.x * currentDirection.x + v.y * currentDirection.y);
        float c = v.x * v.x + v.y * v.y - targetRadius * targetRadius;

        float discriminant = b * b - 4 * a * c;

        if (discriminant >= 0) {
            float t1 = (-b + std::sqrt(discriminant)) / (2 * a);
            float t2 = (-b - std::sqrt(discriminant)) / (2 * a);

            // Vérifier si l'intersection est dans la direction du rayon et plus proche que l'intersection avec un miroir
            if ((t1 > 0 && t1 < closestDistance) || (t2 > 0 && t2 < closestDistance)) {
                target.setLit(true);

                // Si le rayon atteint la cible, on arrête la simulation
                if (!hasIntersection || closestDistance > std::min(t1, t2)) {
                    break;
                }
            }
        }

        if (!hasIntersection) break;

        // Mettre à jour pour le prochain rayon
        currentOrigin = closestIntersection;
        currentDirection = reflectedDir;
    }

    return rays;
}