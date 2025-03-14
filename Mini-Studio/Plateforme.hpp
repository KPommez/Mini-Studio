#pragma once

#include "includeAll.hpp"

class Plateforme {
public:
    Plateforme(float a, float b, int c);
    void creation(float posX, float posY);
    void platUpdate(const float& deltaTime);
    RectangleShape plat;

private:
    float deltaTime;
    float posX;
    float posY;
    float wayPoint1;
    float wayPoint2;
    float deplacementX;
    float deplacementY;
    int State;
    int i;
    

    Vector2f position;
    enum  MOVEMENTSIDE { LEFT, RIGHT };
    MOVEMENTSIDE moveSide;
};