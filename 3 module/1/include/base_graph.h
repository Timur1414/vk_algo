//
// Created by timat on 26.12.2025.
//

#ifndef VK_ALGO_BASE_GRAPH_H
#define VK_ALGO_BASE_GRAPH_H
#include <vector>


struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


#endif //VK_ALGO_BASE_GRAPH_H
