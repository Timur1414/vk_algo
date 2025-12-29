#include "include/arc_graph.h"
#include "include/list_graph.h"
#include "include/matrix_graph.h"
#include "include/set_graph.h"
#include <iostream>


bool check_graphs(const IGraph& a, IGraph& b) {
    if (a.VerticesCount() != b.VerticesCount())
        return false;
    int n = a.VerticesCount();
    for (int i = 0; i < n; i++) {
        std::vector<int> a_vertices = a.GetNextVertices(i);
        std::vector<int> b_vertices = b.GetNextVertices(i);
        if (a_vertices != b_vertices)
            return false;
    }
    return true;
}

void add_all_edges(IGraph& graph) {
    // картинка графа есть в файле graph.png
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 3);
    graph.AddEdge(0, 4);
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 4);
    graph.AddEdge(3, 2);
    graph.AddEdge(4, 5);
    graph.AddEdge(5, 0);
}


int main() {
    int n = 6;
    ArcGraph arc_graph;
    add_all_edges(arc_graph);

    ListGraph list_graph(n);
    add_all_edges(list_graph);

    MatrixGraph matrix_graph(n);
    add_all_edges(matrix_graph);

    SetGraph set_graph(n);
    add_all_edges(set_graph);

    std::cout << (check_graphs(arc_graph, list_graph) ? "Arc graph and List graph are equal\n" : "Arc graph and List graph are not equal\n");
    std::cout << (check_graphs(arc_graph, matrix_graph) ? "Arc graph and Matrix graph are equal\n" : "Arc graph and Matrix graph are not equal\n");
    std::cout << (check_graphs(arc_graph, set_graph) ? "Arc graph and Set graph are equal\n" : "Arc graph and Set graph are not equal\n");
    std::cout << (check_graphs(list_graph, matrix_graph) ? "List graph and Matrix graph are equal\n" : "List graph and Matrix graph are not equal\n");
    std::cout << (check_graphs(list_graph, set_graph) ? "List graph and Set graph are equal\n" : "List graph and Set graph are not equal\n");
    std::cout << (check_graphs(matrix_graph, set_graph) ? "Matrix graph and Set graph are equal\n" : "Matrix graph and Set graph are not equal\n");

    return 0;
}
