#include "../include/set_graph.h"
#include <algorithm>


SetGraph::SetGraph() {
    n = 0;
}

SetGraph::SetGraph(int n) {
    this->n = n;
    graph.resize(n);
}

SetGraph::SetGraph(const IGraph& oth) {
    this->n = oth.VerticesCount();
    graph.resize(n);
    for (int i = 0; i < n; i++) {
        std::vector<int> v = oth.GetNextVertices(i);
        for (int j : v)
            AddEdge(i, j);
    }
}

SetGraph::~SetGraph() {
    for (auto& v : graph)
        v.clear();
    graph.clear();
}

void SetGraph::AddEdge(int from, int to) {
    graph[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return n;
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    std::set<int> v = graph[vertex];
    for (int j : v)
        res.push_back(j);
    return res;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (int i = 0; i < n; i++) {
        std::set<int> v = graph[i];
        if (std::find(v.begin(), v.end(), vertex) != v.end())
            res.push_back(i);
    }
    return res;
}
