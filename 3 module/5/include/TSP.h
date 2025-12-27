#ifndef VK_ALGO_TSP_H
#define VK_ALGO_TSP_H
#include "graph.h"


class TspSolver {
private:
    Graph graph;
    std::vector<Point> points;

    double get_weight_solution(const std::vector<Point>&);
public:
    TspSolver();
    TspSolver(const Graph&);

    std::pair<double, double> compare_solve();
};

#endif //VK_ALGO_TSP_H
