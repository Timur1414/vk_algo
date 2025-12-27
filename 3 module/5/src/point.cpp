#include "../include/point.h"
#include <cmath>
#include <functional>
#include <numbers>


Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

double Point::get_distance(const Point& oth) const {
    return sqrt(pow(x - oth.x, 2) + pow(y - oth.y, 2));
}

bool Point::operator==(const Point& oth) const {
    return (x == oth.x && y == oth.y);
}


unsigned int Hasher::operator()(const Point& point) const {
    return std::hash<double>()(point.x) ^ std::hash<double>()(point.y);
}

bool Point::operator<(const Point& oth) const {
    Point zero(0, 0);
    double distance1 = get_distance(zero);
    double distance2 = oth.get_distance(zero);
    return distance1 < distance2;
}


Point generate_point() {
    double r = static_cast<double>(std::rand()) / RAND_MAX;
    double fi = static_cast<double>(std::rand()) / RAND_MAX;
    if (r == 0)
        r = 1;
    if (fi == 0)
        fi = 1;
    double x = cos(2 * std::numbers::pi * fi) * sqrt(-2 * log(r));
    double y = sin(2 * std::numbers::pi * fi) * sqrt(-2 * log(r));
    return Point(x, y);
}
