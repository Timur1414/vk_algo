#ifndef VK_ALGO_POINT_H
#define VK_ALGO_POINT_H


class Hasher;

class Point {
private:
    double x;
    double y;

    friend class Hasher;
public:
    Point();
    Point(double, double);

    double get_distance(const Point&) const;

    bool operator==(const Point&) const;
    bool operator<(const Point&) const;
};


class Hasher {
public:
    unsigned int operator()(const Point&) const;
};


Point generate_point();

#endif //VK_ALGO_POINT_H
