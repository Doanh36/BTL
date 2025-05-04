#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"
#include <iostream>
#include <string>

class Transform {
public:
    Vector2D position;
    Vector2D velocity;
    float speed;

    Transform(float x = 0.0f, float y = 0.0f, float s = 0.0f)
        : position(x, y), speed(s), velocity(0, 0) {}

    void Log(std::string msg = "") const {
    }

    void TranslateX(float x) {
        position.X += x;
    }

    void TranslateY(float y) {
        position.Y += y;
    }
};

#endif // TRANSFORM_H
