#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdexcept>

/* --- CLASSE ARCO (unidirected_edge) --- */
template<typename T>
class unidirected_edge {
    T from_, to_;

public:
    // Il costruttore garantisce sempre che from < to
    unidirected_edge(const T& n1, const T& n2) {
        if (n1 < n2) {
            from_ = n1;
            to_ = n2;
        } else {
            from_ = n2;
            to_ = n1;
        }
    }

    T from() const { return from_; }
    T to() const { return to_; }

    // Operatori richiesti
    bool operator<(const unidirected_edge& other) const {
        if (from_ != other.from_) return from_ < other.from_;
        return to_ < other.to_;
    }

    bool operator==(const unidirected_edge& other) const {
        return from_ == other.from_ && to_ == other.to_;
    }

    friend std::ostream& operator<<(std::ostream& os, const unidirected_edge& e) {
        os << "{" << e.from_ << " - " << e.to_ << "}";
        return os;
    }
};

/* --- CLASSE GRAFO (unidirected_graph) --- */
template<typename T>
class unidirected_graph {
    std::set<T> nodes_;
    std::set<unidirected_edge<T>> edges_set_;
    std::vector<unidirected_edge<T>> edges_vec_;
    std::map<T, std::set<T>> adjacency_list_;

public:
    unidirected_graph() = default;
    unidirected_graph(const unidirected_graph& other) = default;

    void add_edge(const T& n1, const T& n2) {
        unidirected_edge<T> new_edge(n1, n2);
        
        if (edges_set_.find(new_edge) == edges_set_.end()) {
            edges_set_.insert(new_edge);
            edges_vec_.push_back(new_edge);
            nodes_.insert(n1);
            nodes_.insert(n2);
            
            adjacency_list_[n1].insert(n2);
            adjacency_list_[n2].insert(n1);
        }
    }

    std::set<T> neighbours(const T& node) const {
        auto it = adjacency_list_.find(node);
        if (it != adjacency_list_.end()) {
            return it->second;
        }
        return std::set<T>();
    }

    std::set<T> all_nodes() const { return nodes_; }
    
    const std::vector<unidirected_edge<T>>& all_edges() const {
        return edges_vec_;
    }

    size_t edge_number(const unidirected_edge<T>& edge) const {
        auto it = std::find(edges_vec_.begin(), edges_vec_.end(), edge);
        if (it == edges_vec_.end()) {
            throw std::runtime_error("Arco non trovato");
        }
        return std::distance(edges_vec_.begin(), it);
    }

    unidirected_edge<T> edge_at(size_t index) const {
        if (index >= edges_vec_.size()) {
            throw std::out_of_range("Indice arco errato");
        }
        return edges_vec_[index];
    }

    unidirected_graph operator-(const unidirected_graph& other) const {
        unidirected_graph result;
        for (const auto& e : this->edges_vec_) {
            if (std::find(other.edges_vec_.begin(), other.edges_vec_.end(), e) == other.edges_vec_.end()) {
                result.add_edge(e.from(), e.to());
            }
        }
        return result;
    }
};

#endif