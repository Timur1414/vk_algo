#ifndef VK_ALGO_ARC_GRAPH_H
#define VK_ALGO_ARC_GRAPH_H
#include "base_graph.h"


class ArcGraph : public IGraph {
private:
    std::vector<std::pair<int, int>> graph;
public:
    ArcGraph();
    ArcGraph(const IGraph&);
    ~ArcGraph();

    void AddEdge(int, int);
    int VerticesCount() const;
    std::vector<int> GetNextVertices(int) const;
    std::vector<int> GetPrevVertices(int) const;
};


#endif //VK_ALGO_ARC_GRAPH_H
