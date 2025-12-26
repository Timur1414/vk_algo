#include "../include/list_graph.h"

ListGraph::ListGraph() {
    n = 0;
}

ListGraph::ListGraph(int n) {
    this->n = n;
    graph.resize(n);
}

ListGraph::ListGraph(const IGraph& oth) {
    this->n = oth.VerticesCount();
    graph.resize(n);
    for (int i = 0; i < n; i++) {
        std::vector<int> v = oth.GetNextVertices(i);
        for (int j : v)
            AddEdge(i, j);
    }
}

ListGraph::~ListGraph() {
    for (auto& list : graph)
        list.clear();
    graph.clear();
}

void ListGraph::AddEdge(int from, int to) {
    graph[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return n;
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (int v : graph[vertex])
        res.push_back(v);
    return res;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (int i = 0; i < n; i++) {
        if (find(graph[i].begin(), graph[i].end(), vertex) != graph[i].end())
            res.push_back(i);
    }
    return res;
}
