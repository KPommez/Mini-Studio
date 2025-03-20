#pragma once

#include "includeAll.hpp"

class Plateforme {
public:
    Plateforme(float a, float b, int c, Texture d);
    void creation(float posX, float posY);
    void platUpdate(const float& deltaTime);
    RectangleShape plat;
    Texture tex;
    float deplacementX;
    float deplacementY;

private:
    float deltaTime;
    float posX;
    float posY;
    float wayPoint1;
    float wayPoint2;  
    int State;
    int i;
    

    Vector2f position;
    enum  MOVEMENTSIDE { LEFT, RIGHT };
    MOVEMENTSIDE moveSide;
};