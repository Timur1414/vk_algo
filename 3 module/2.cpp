#include <iostream>
#include <vector>
#include <queue>
#include <cmath>


class Graph {
private:
    std::vector<std::vector<int>> graph;
    std::vector<bool> visited;
    std::vector<int> distances;
    std::vector<int> count_min_distances;
    int n;

    void bfs(int start) {
        std::queue<int> queue;
        queue.push(start);
        visited[start] = true;
        distances[start] = 0;
        count_min_distances[start] = 1;
        while (!queue.empty()) {
            int v = queue.front();
            queue.pop();
            for (int u : graph[v]) {
                if (!visited[u]) {
                    if (distances[u] == distances[v] + 1) {
                        count_min_distances[u] += count_min_distances[v];
                    }
                    else if (distances[u] > distances[v] + 1) {
                        distances[u] = distances[v] + 1;
                        count_min_distances[u] = count_min_distances[v];
                    }
                    queue.push(u);
                    visited[u] = true;
                }
                else {
                    if (distances[u] == distances[v] + 1) {
                        count_min_distances[u] += count_min_distances[v];
                    }
                }
            }
        }
    }
public:
    Graph() {
        n = 0;
    }
    Graph(int n) {
        this->n = n;
        graph.resize(n);
    }

    void add_edge(int from, int to) {
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    int get_count_min_distances(int start, int end) {
        visited.resize(n, false);
        distances.resize(n, pow(10, 9));
        count_min_distances.resize(n, 0);
        bfs(start);
        return count_min_distances[end];
    }

    friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& in, Graph& graph) {
    int u = 0, n = 0;
    in >> u >> n;
    graph.graph.resize(u);
    graph.n = u;
    for (int i = 0; i < n; i++) {
        int from = 0, to = 0;
        in >> from >> to;
        graph.add_edge(from, to);
    }
    return in;
}

int main() {
    // 2. Количество разных путей.
    Graph graph;
    std::cin >> graph;
    int start = 0, end = 0;
    std::cin >> start >> end;
    std::cout << graph.get_count_min_distances(start, end);

    return 0;
}