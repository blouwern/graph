#include "Graph.h++"

#include <array>
#include <cstdlib>
#include <string>

auto main() -> int {
    WZC::Graph<std::string> graph;

    std::array v{graph.AddVertex("a"),
                 graph.AddVertex("b"),
                 graph.AddVertex("c"),
                 graph.AddVertex("d"),
                 graph.AddVertex("e")};

    for (auto vertex1 : v) {
        for (auto vertex2 : v) {
            graph.AddEdge(vertex1, vertex2);
        }
    }

    return EXIT_SUCCESS;
}
