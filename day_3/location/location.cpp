#include "location.hpp"
#include <cmath>

Location::Location(double x, double y) : x(x), y(y) {}

double Location::distanceTo(const Location& other) const {
    return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
}

double Location::getX() const { return x; }

double Location::getY() const { return y; }
