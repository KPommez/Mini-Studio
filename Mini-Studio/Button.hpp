#pragma once

#include "includeAll.hpp"

class Rectangle {
public:
    float tailleX;
    float tailleY;
    float posX;
    float posY;
    int R;
    int G;
    int B;

    Rectangle(float sizeX, float sizeY, float xPos, float yPos, int red, int green, int blue) : 
        tailleX(sizeX), tailleY(sizeY), posX(xPos), posY(yPos), R(red), G(green), B(blue) {}

    RectangleShape creation() const {
        RectangleShape rect(Vector2f(tailleX, tailleY)); // Rayon de 50 pixels
        rect.setPosition(posX, posY);
        rect.setFillColor(Color(R, G, B));
        return rect;
    }
};