#ifndef LOCATION_HPP
#define LOCATION_HPP

class Location {
public:
    Location(double x, double y);
    bool operator==(const Location& other) const {
        return x == other.x && y == other.y;
    }

    // Calcule la distance euclidienne jusqu'à une autre Location.
    double distanceTo(const Location& other) const;

    double getX() const;
    double getY() const;

private:
    double x, y;
};

#endif
