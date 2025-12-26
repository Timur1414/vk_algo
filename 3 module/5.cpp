#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>


class Graph {
private:
    std::vector<std::vector<std::pair<long long, long long>>> graph;
    long long n;
    std::vector<long long> min_edge;
    std::vector<bool> visited;
    const long long INF = std::numeric_limits<int>::max();

    void prima(long long start) {
        min_edge[start] = 0;
        std::set<std::pair<long long, long long>> set;
        set.insert(std::make_pair(0, start));
        while (!set.empty()) {
            std::pair<long long, long long> first_elem = *set.begin();
            visited[first_elem.second] = true;
            set.erase(set.begin());
            long long u = first_elem.second;
            for (std::pair<long long, long long> item : graph[u]) {
                if (min_edge[item.first] == INF) {
                    min_edge[item.first] = item.second;
                    set.insert(std::make_pair(min_edge[item.first], item.first));
                }
                else if (min_edge[item.first] > item.second && !visited[item.first]) {
                        set.erase(std::make_pair(min_edge[item.first], item.first));
                        min_edge[item.first] = item.second;
                        set.insert(std::make_pair(min_edge[item.first], item.first));
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
        if (std::find_if(graph[from].begin(), graph[from].end(), [to](auto item) {
            return item.first == to;
        }) == graph[from].end()) {
            graph[from].push_back(item1);
            graph[to].push_back(item2);
        }
        else {
            auto found_item1 = std::find_if(graph[from].begin(), graph[from].end(), [to](auto item) {
                return item.first == to;
            });
            auto found_item2 = std::find_if(graph[to].begin(), graph[to].end(), [from](auto item) {
                return item.first == from;
            });
            found_item1->second = std::min(weight, found_item1->second);
            found_item2->second = std::min(weight, found_item2->second);
        }
    }
    long long get_sum_edges() {
        long long sum = 0;
        for (long long i = 0; i < n; i++)
            sum += min_edge[i];
        return sum;
    }
    long long get_min_ostov_weight() {
        min_edge.resize(n, INF);
        visited.resize(n, false);
        prima(0);
        return get_sum_edges();
    }

    friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& in, Graph& graph) {
    long long n = 0, m = 0;
    in >> n >> m;
    graph.n = n;
    graph.graph.resize(n);
    for (long long i = 0; i < m; i++) {
        long long from = 0, to = 0, weight = 0;
        in >> from >> to >> weight;
        from--;
        to--;
        graph.add_edge(from, to, weight);
    }
    return in;
}


int main() {
    // 5. Минимальное остовное дерево (алгоритм Прима).
    Graph graph;
    std::cin >> graph;
    std::cout << graph.get_min_ostov_weight();

    return 0;
}
