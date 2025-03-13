#pragma once
#include "includeAll.hpp"
class Plateforme
{
    public:
        float posX;
        float posY;
        float wayPoint1;
        float wayPoint2;
        int State;
        int i;
        vector<float> point;

        RectangleShape plat;
        
       

        Plateforme(float a, float b, int c);

        void creation(float posX, float posY);

        void platUpdate();
        
};

