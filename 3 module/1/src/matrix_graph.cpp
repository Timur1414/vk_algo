#include "../include/matrix_graph.h"


MatrixGraph::MatrixGraph() {
    n = 0;
}

MatrixGraph::MatrixGraph(int n) {
    this->n = n;
    graph.resize(n, std::vector<int>(n, 0));
}

MatrixGraph::MatrixGraph(const IGraph& oth) {
    this->n = oth.VerticesCount();
    graph.resize(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        std::vector<int> v = oth.GetNextVertices(i);
        for (int j : v)
            AddEdge(i, j);
    }
}

MatrixGraph::~MatrixGraph() {
    for (auto& v : graph)
        v.clear();
    graph.clear();
}

void MatrixGraph::AddEdge(int from, int to) {
    graph[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return n;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (int i = 0; i < n; i++)
        if (graph[vertex][i])
            res.push_back(i);
    return res;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (int i = 0; i < n; i++)
        if (graph[i][vertex])
            res.push_back(i);
    return res;
}
