#include <vector>
#include <iostream>
#include <set>
#include <limits>
#include <algorithm>


class Graph {
private:
    std::vector<std::vector<std::pair<long long, long long>>> graph;
    long long n;
    std::vector<long long> distances;
    const long long INF = std::numeric_limits<int>::max();

    void dijkstra(long long start) {
        distances[start] = 0;
        std::set<std::pair<long long, long long>> set;
        set.insert(std::make_pair(0, start));
        while (!set.empty()) {
            std::pair<long long, long long> first_elem = *set.begin();
            set.erase(set.begin());
            long long u = first_elem.second;
            for (std::pair<long long, long long> item : graph[u]) {
                if (distances[item.first] == INF) {
                    distances[item.first] = distances[u] + item.second;
                    set.insert(std::make_pair(distances[item.first], item.first));
                }
                else if (distances[item.first] > distances[u] + item.second) {
                        set.erase(std::make_pair(distances[item.first], item.first));
                        distances[item.first] = distances[u] + item.second;
                        set.insert(std::make_pair(distances[item.first], item.first));
                    }
            }
        }
    }
public:
    Graph() {
        n = 0;
    }
    Graph(long long n) {
        this->n = n;
        graph.resize(n);
    }

    void add_edge(long long from, long long to, long long weight) {
        std::pair<long long, long long> item1 = std::make_pair(to, weight);
        std::pair<long long, long long> item2 = std::make_pair(from, weight);
        if (std::find(graph[from].begin(), graph[from].end(), item1) == graph[from].end()) {
            graph[from].push_back(item1);
            graph[to].push_back(item2);
        }
        else {
            auto found_item1 = std::find(graph[from].begin(), graph[from].end(), item1);
            auto found_item2 = std::find(graph[to].begin(), graph[to].end(), item2);
            found_item1->second = std::min(weight, found_item1->second);
            found_item2->second = std::min(weight, found_item2->second);
        }
    }
    long long get_distance(long long start, long long end) {
        distances.resize(n, INF);
        dijkstra(start);
        return distances[end];
    }

    friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& in, Graph& graph) {
    long long n = 0, m = 0;
    in >> n >> m;
    graph.n = n;
    graph.graph.resize(n);
    for (long long i = 0; i < m; i++) {
        long long u = 0, v = 0, w = 0;
        in >> u >> v >> w;
        graph.add_edge(u, v, w);
    }
    return in;
}


int main() {
    // 3. Кратчайший путь между городами.
    Graph graph;
    std::cin >> graph;
    long long start = 0, end = 0;
    std::cin >> start >> end;
    std::cout << graph.get_distance(start, end);

    return 0;
}
