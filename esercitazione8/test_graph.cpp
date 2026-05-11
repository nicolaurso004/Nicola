#include <iostream>
#include <cassert>
#include "graph.hpp"

int main() {
    std::cout << "--- INIZIO TEST GRAFO ---" << std::endl;

    // 1. Test arco
    unidirected_edge<int> e1(10, 5); 
    std::cout << "Test Arco (10,5): " << e1 << std::endl;
    assert(e1.from() == 5 && e1.to() == 10);

    // 2. Test grafo
    unidirected_graph<int> g1;
    g1.add_edge(1, 2);
    g1.add_edge(2, 3);
    g1.add_edge(1, 3);

    std::cout << "Nodi in g1: " << g1.all_nodes().size() << " (attesi: 3)" << std::endl;
    assert(g1.all_nodes().size() == 3);

    auto n_1 = g1.neighbours(1);
    std::cout << "Vicini di 1: ";
    for(auto n : n_1) std::cout << n << " ";
    std::cout << std::endl;

    unidirected_edge<int> target_edge(3, 2);
    size_t idx = g1.edge_number(target_edge);
    std::cout << "L'arco {2-3} ha indice: " << idx << std::endl;
    assert(g1.edge_at(idx) == target_edge);

    // 3. Test Differenza
    unidirected_graph<int> g2;
    g2.add_edge(1, 2);
    g2.add_edge(4, 5);

    unidirected_graph<int> diff = g1 - g2;
    std::cout << "Archi in (g1 - g2): " << diff.all_edges().size() << " (attesi: 2)" << std::endl;
    assert(diff.all_edges().size() == 2);

    std::cout << "--- TUTTI I TEST SUPERATI ---" << std::endl;
    return 0;
}