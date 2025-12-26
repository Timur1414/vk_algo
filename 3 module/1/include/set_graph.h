#ifndef VK_ALGO_SET_GRAPH_H
#define VK_ALGO_SET_GRAPH_H
#include "base_graph.h"
#include <set>


class SetGraph : public IGraph {
private:
    std::vector<std::set<int>> graph;
    int n;
public:
    SetGraph();
    SetGraph(int);
    SetGraph(const IGraph&);
    ~SetGraph();

    void AddEdge(int, int);
    int VerticesCount() const;
    std::vector<int> GetNextVertices(int) const;
    std::vector<int> GetPrevVertices(int) const;
};


#endif //VK_ALGO_SET_GRAPH_H
