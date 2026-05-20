#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <stack>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include "graph.hpp"

/* --- 3.1 ADAPTER PATTERN (LIFO e FIFO) --- */

template <typename T>
class lifo {
    std::stack<T> s;
public:
    void put(const T& val) { s.push(val); }
    T get() { T val = s.top(); s.pop(); return val; }
    bool empty() const { return s.empty(); }
};

template <typename T>
class fifo {
    std::queue<T> q;
public:
    void put(const T& val) { q.push(val); }
    T get() { T val = q.front(); q.pop(); return val; }
    bool empty() const { return q.empty(); }
};

/* --- 3.2 VISITA GENERICA (BFS/DFS) --- */

template <typename T, typename Container>
unidirected_graph<T> graph_visit(const unidirected_graph<T>& G, const T& source, Container& C) {
    unidirected_graph<T> tree;
    std::set<T> visited;

    C.put(source);
    visited.insert(source);

    while (!C.empty()) {
        T u = C.get();
        for (const auto& v : G.neighbours(u)) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                tree.add_edge(u, v);
                C.put(v);
            }
        }
    }
    return tree;
}

/* --- DFS RICORSIVA --- */

template <typename T>
void recursive_dfs_helper(const unidirected_graph<T>& G, const T& u, std::set<T>& visited, unidirected_graph<T>& tree) {
    visited.insert(u);
    for (const auto& v : G.neighbours(u)) {
        if (visited.find(v) == visited.end()) {
            tree.add_edge(u, v);
            recursive_dfs_helper(G, v, visited, tree);
        }
    }
}

template <typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& G, const T& source) {
    unidirected_graph<T> tree;
    std::set<T> visited;
    recursive_dfs_helper(G, source, visited, tree);
    return tree;
}

/* --- 3.3 DIJKSTRA --- */

template <typename T>
std::map<T, double> dijkstra(const unidirected_graph<T>& G, const T& source) {
    std::map<T, double> distances;
    for (auto n : G.all_nodes()) distances[n] = 1e18; // Infinito
    distances[source] = 0;

    // Usiamo una coda di priorità (min-priority queue)
    using pii = std::pair<double, T>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        double d = pq.top().first;
        T u = pq.top().second;
        pq.pop();

        if (d > distances[u]) continue;

        for (auto v : G.neighbours(u)) {
            // In questo grafo non pesato, ogni arco vale 1
            if (distances[u] + 1 < distances[v]) {
                distances[v] = distances[u] + 1;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

#endif