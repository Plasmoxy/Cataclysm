
#include "vectorutil.hpp"
#include <string>

// constructors

Vec2f::Vec2f(): x(0), y(0) {}
Vec2f::Vec2f(float x, float y): x(x), y(y) {}

// math

Vec2f Vec2f::operator+(Vec2f v) {
    return Vec2f(x + v.x, y + v.y);
}

Vec2f Vec2f::operator-(Vec2f v) {
    return Vec2f(x - v.x, y - v.y);
}

Vec2f Vec2f::operator*(Vec2f v) {
    return Vec2f(x * v.x, y * v.y);
}

Vec2f Vec2f::operator/(Vec2f v) {
    return Vec2f(x / v.x, y / v.y);
}

float Vec2f::dot(Vec2f v) {
    return x*v.x + y*v.y;
}

// utilities

std::string Vec2f::toString() {
    return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
}