#ifndef VK_ALGO_MATRIX_GRAPH_H
#define VK_ALGO_MATRIX_GRAPH_H
#include "base_graph.h"


class MatrixGraph : public IGraph {
private:
    std::vector<std::vector<int>> graph;
    int n;
public:
    MatrixGraph();
    MatrixGraph(int);
    MatrixGraph(const IGraph&);
    ~MatrixGraph();

    void AddEdge(int, int);
    int VerticesCount() const;
    std::vector<int> GetNextVertices(int) const;
    std::vector<int> GetPrevVertices(int) const;
};


#endif //VK_ALGO_MATRIX_GRAPH_H
