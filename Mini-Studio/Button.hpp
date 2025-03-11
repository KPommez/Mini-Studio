#pragma once
#include "includeAll.hpp"

class Rectangle {
public:
    int tailleX;
    int tailleY;
    float posX;
    float posY;
    int R;
    int G;
    int B;

    Rectangle(int a, int b, float c, float d, int e, int f, int g) : tailleX(a), tailleY(b), posX(c), posY(d), R(e), G(f), B(g) {}

    RectangleShape creation() {
        RectangleShape shape1(Vector2f(tailleX, tailleY)); // Rayon de 50 pixels
        shape1.setPosition(posX, posY);
        shape1.setFillColor(Color(R, G, B));
        return shape1;
    }
};