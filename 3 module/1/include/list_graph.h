#ifndef VK_ALGO_LIST_GRAPH_H
#define VK_ALGO_LIST_GRAPH_H
#include "base_graph.h"
#include <list>


class ListGraph : public IGraph {
private:
    std::vector<std::list<int>> graph;
    int n;
public:
    ListGraph();
    ListGraph(int);
    ListGraph(const IGraph&);
    ~ListGraph();

    void AddEdge(int, int);
    int VerticesCount() const;
    std::vector<int> GetNextVertices(int) const;
    std::vector<int> GetPrevVertices(int) const;
};


#endif //VK_ALGO_LIST_GRAPH_H
