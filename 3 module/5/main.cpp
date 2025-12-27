#include <algorithm>
#include "include/graph.h"
#include <ctime>
#include "include/TSP.h"


double calculate_mean(const std::vector<double>& arr) {
    double sum = 0;
    std::for_each(arr.begin(), arr.end(), [&sum](double x) {
        sum += x;
    });
    return sum / arr.size();
}

double calculate_variance(const std::vector<double>& arr, double mean) {
    double sum = 0;
    std::for_each(arr.begin(), arr.end(), [&sum, mean](double x) {
        sum += (x - mean) * (x - mean);
    });
    return sum / arr.size();
}


int main() {
    // Темиров Тимур - ttemir0v
    // 5. Приближенное решение метрической неориентированной задачи коммивояжера.
    std::srand(std::time({}));
    const int min_size = 2, max_size = 10;
    const int attempts = 15;
    for (int size = min_size; size <= max_size; size++) {
        std::cout << "Size: " << size << std::endl;
        std::vector<double> diff;
        for (int i = 0; i < attempts; i++) {
            Graph graph = generate_random_graph(size);
            TspSolver solver(graph);
            std::pair<double, double> weights = solver.compare_solve();
            diff.push_back(weights.first - weights.second);
        }
        double mean = calculate_mean(diff);
        double variance = calculate_variance(diff, mean);
        std::cout << "Mean difference: " << mean << std::endl;
        std::cout << "Variance of difference: " << variance << std::endl;
        std::cout << "===================================\n";
    }


    return 0;
}
