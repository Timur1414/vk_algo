#include "../include/TSP.h"
#include <algorithm>


double TspSolver::get_weight_solution(const std::vector<Point>& points) {
    double sum = 0;
    for (int i = 1; i < points.size(); i++)
        sum += points[i - 1].get_distance(points[i]);
    sum += points.back().get_distance(points.front());
    return sum;
}

TspSolver::TspSolver() {}

TspSolver::TspSolver(const Graph& graph) {
    this->graph = graph;
    for (auto& it : this->graph.get_graph())
        points.push_back(it.first);
}

std::pair<double, double> TspSolver::compare_solve() {
    const double ostov_solution = graph.get_min_ostov_weight() * 2;
    double best_solution = get_weight_solution(points);
    do {
        double cur_weight = get_weight_solution(points);
        best_solution = std::min(best_solution, cur_weight);
    } while (std::next_permutation(points.begin(), points.end()));
    return std::make_pair(ostov_solution, best_solution);
}
