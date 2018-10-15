#pragma once

#include <string>

class Vec2f {
public:
    float x;
    float y;

    Vec2f();
    Vec2f(float _x, float _y);

    Vec2f operator +(Vec2f);
    Vec2f operator -(Vec2f);
    Vec2f operator *(Vec2f);
    Vec2f operator /(Vec2f);

    float dot(Vec2f);

    std::string toString();
};