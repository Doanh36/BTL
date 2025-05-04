#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <cmath>

class Vector2D {
public:
    float X, Y;

    Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}

    // addition +
    inline Vector2D operator+(const Vector2D& v2) const {
        return Vector2D(X + v2.X, Y + v2.Y);
    }

    // subtraction -
    inline Vector2D operator-(const Vector2D& v2) const {
        return Vector2D(X - v2.X, Y - v2.Y);
    }

    void Log(std::string msg = "") const {
        std::cout << msg << " (X, Y) = (" << X << ", " << Y << ")\n";
    }
};

#endif // VECTOR 2D_H
