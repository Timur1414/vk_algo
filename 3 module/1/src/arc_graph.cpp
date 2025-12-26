#include "../include/arc_graph.h"
#include <set>


ArcGraph::ArcGraph() {}

ArcGraph::ArcGraph(const IGraph& oth) {
    int n = oth.VerticesCount();
    for (int i = 0; i < n; i++) {
        std::vector<int> v = oth.GetNextVertices(i);
        for (int j : v)
            AddEdge(i, j);
    }
}

ArcGraph::~ArcGraph() {
    graph.clear();
}

void ArcGraph::AddEdge(int from, int to) {
    graph.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
    std::set<int> all_vertex;
    for (auto pair : graph) {
        all_vertex.insert(pair.first);
        all_vertex.insert(pair.second);
    }
    return all_vertex.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (auto pair : graph)
        if (pair.first == vertex)
            res.push_back(pair.second);
    return res;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (auto pair : graph)
        if (pair.second == vertex)
            res.push_back(pair.first);
    return res;
}
