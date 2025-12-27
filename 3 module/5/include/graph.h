#ifndef VK_ALGO_GRAPH_H
#define VK_ALGO_GRAPH_H
#include "point.h"
#include <vector>
#include <limits>
#include <iostream>
#include <unordered_map>


class Graph {
private:
    std::unordered_map<Point, std::vector<Point>, Hasher> graph;
    long long n;
    std::unordered_map<Point, double, Hasher> min_edge;
    std::unordered_map<Point, bool, Hasher> visited;
    const double INF = std::numeric_limits<int>::max();

    void prima(const Point&);
public:
    Graph();
    Graph(long long);

    Graph& operator=(const Graph&);

    std::unordered_map<Point, std::vector<Point>, Hasher> get_graph();
    void add_edge(const Point&, const Point&);
    double get_sum_edges() const;
    double get_min_ostov_weight();
};


Graph generate_random_graph(int);

#endif //VK_ALGO_GRAPH_H
