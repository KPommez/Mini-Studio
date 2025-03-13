#pragma once

#include "includeAll.hpp"

class Plateforme {
public:
    Plateforme(float a, float b, int c);
    void creation(float posX, float posY);
    void platUpdate();

public:
    RectangleShape plat;

private:
    float posX;
    float posY;
    float wayPoint1;
    float wayPoint2;
    int State;
    int i;
    vector<float> point;
};