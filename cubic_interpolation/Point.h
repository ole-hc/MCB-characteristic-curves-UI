#pragma once
#include "libs.h"

class Point
{
private:
    float x;
    float y;
public:
    Point(float _x, float _y);
    ~Point();
    float getX();
    float getY();
};
