#include "../include/graph.h"
#include <algorithm>
#include <set>


Graph::Graph() {
    n = 0;
}

Graph::Graph(long long n) {
    this->n = n;
}

Graph& Graph::operator=(const Graph& oth) {
    n = oth.n;
    graph = oth.graph;
    min_edge = oth.min_edge;
    visited = oth.visited;
    return *this;
}

std::unordered_map<Point, std::vector<Point>, Hasher> Graph::get_graph() {
    return graph;
}

void Graph::add_edge(const Point& from, const Point& to) {
    graph[from].push_back(to);
    graph[to].push_back(from);
}

double Graph::get_sum_edges() const {
    double sum = 0;
    for (auto it = min_edge.begin(); it != min_edge.end(); it++)
        sum += it->second;
    return sum;
}

double Graph::get_min_ostov_weight() {
    for (auto it = graph.begin(); it != graph.end(); it++) {
        min_edge[it->first] = INF;
        visited[it->first] = false;
    }
    prima(graph.begin()->first);
    return get_sum_edges();
}

void Graph::prima(const Point& start) {
    min_edge[start] = 0;
    std::set<std::pair<long long, Point>> set;
    set.insert(std::make_pair(0, start));
    while (!set.empty()) {
        std::pair<long long, Point> first_elem = *set.begin();
        Point cur_point = first_elem.second;
        visited[cur_point] = true;
        set.erase(set.begin());
        for (Point next_point : graph[cur_point]) {
            if (min_edge[next_point] == INF) {
                min_edge[next_point] = cur_point.get_distance(next_point);
                set.insert(std::make_pair(min_edge[next_point], next_point));
            }
            else if (min_edge[next_point] > cur_point.get_distance(next_point) && !visited[next_point]) {
                set.erase(std::make_pair(min_edge[next_point], next_point));
                min_edge[next_point] = cur_point.get_distance(next_point);
                set.insert(std::make_pair(min_edge[next_point], next_point));
            }
        }
    }
}


Graph generate_random_graph(int n) {
    Graph graph(n);
    std::vector<Point> points;
    for (int i = 0; i < n; i++)
        points.push_back(generate_point());
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            graph.add_edge(points[i], points[j]);
    return graph;
}
