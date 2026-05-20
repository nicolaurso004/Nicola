#include <iostream>
#include <cassert>
#include "graph.hpp"
#include "algorithms.hpp"

int main() {
    std::cout << "--- TEST ALGORITMI SU GRAFI ---" << std::endl;

    // Creiamo un grafo di esempio: 1-2, 1-3, 2-4, 3-4
    unidirected_graph<int> G;
    G.add_edge(1, 2);
    G.add_edge(1, 3);
    G.add_edge(2, 4);
    G.add_edge(3, 4);

    // 1. Test BFS (con FIFO)
    fifo<int> q;
    auto bfs_tree = graph_visit(G, 1, q);
    std::cout << "BFS completata. Archi nell'albero: " << bfs_tree.all_edges().size() << std::endl;
    assert(bfs_tree.all_edges().size() == 3); // Un albero di 4 nodi ha 3 archi

    // 2. Test DFS (con LIFO)
    lifo<int> s;
    auto dfs_tree = graph_visit(G, 1, s);
    std::cout << "DFS completata. Archi nell'albero: " << dfs_tree.all_edges().size() << std::endl;
    assert(dfs_tree.all_edges().size() == 3);

    // 3. Test DFS Ricorsiva
    auto r_dfs_tree = recursive_dfs(G, 1);
    std::cout << "DFS Ricorsiva completata." << std::endl;
    assert(r_dfs_tree.all_edges().size() == 3);

    // 4. Test Dijkstra
    auto dists = dijkstra(G, 1);
    std::cout << "Distanze da nodo 1:" << std::endl;
    for (auto const& [node, dist] : dists) {
        std::cout << "  Nodo " << node << ": " << dist << std::endl;
    }
    assert(dists[4] == 2); // Il cammino minimo 1->2->4 o 1->3->4 è lungo 2

    std::cout << "--- TUTTI I TEST SUPERATI ---" << std::endl;
    return 0;
}