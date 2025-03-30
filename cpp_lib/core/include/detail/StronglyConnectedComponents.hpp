#pragma once

#include <cassert>

#include "Graph.hpp"

namespace detail {

// Helper struct for the evaluation of
// Tarjan's strongly connected components algorithm
// Based on https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm
template<typename TWeight>
struct [[deprecated]] StronglyConnectedComponentsMatrixGraphTarjan {
    StronglyConnectedComponentsMatrixGraphTarjan() = default;

    StronglyConnectedComponentsMatrixGraphTarjan(
        MatrixGraph<TWeight> const& graph
    ) :
        graph(&graph),
        indices(graph.get_adjacency_matrix().size(), -1),
        lowlinks(graph.get_adjacency_matrix().size(), -1),
        stack {},
        on_stack(graph.get_adjacency_matrix().size(), -1),
        strongly_connected_components(graph.get_adjacency_matrix().size(), -1),
        index {0},
        strongly_connected_component {0} {}

    void strongconnect(int v) {
        assert(graph != nullptr);
        auto const& adjacency_matrix = graph->get_adjacency_matrix();
        auto const n = adjacency_matrix.size();
        indices[v] = index;
        lowlinks[v] = index;
        ++index;
        stack.push_back(v);
        on_stack[v] = true;

        for (int w = 0; w < n; ++w) {
            // TODO: replace with "edge doesn't exist" check once implemented
            if (adjacency_matrix[v][w] == TWeight(0)) {
                continue;
            }
            if (indices[w] == -1) {
                strongconnect(w);
                lowlinks[v] = std::min(lowlinks[v], lowlinks[w]);
            } else if (on_stack[w]) {
                lowlinks[v] = std::min(lowlinks[v], indices[w]);
            }
        }

        if (lowlinks[v] == indices[v]) {
            int w = -1;
            do {
                w = stack.back();
                stack.pop_back();
                on_stack[w] = false;
                strongly_connected_components[w] = strongly_connected_component;
            } while (w != v);
            ++strongly_connected_component;
        }
    }

    void calculate_strongly_connected_components() {
        for (int v = 0; v < graph->get_adjacency_matrix().size(); ++v) {
            if (indices[v] == -1) {
                strongconnect(v);
            }
        }
    }

    int count_strongly_connected_components() const {
        return strongly_connected_component;
    }

    std::vector<int> const& get_strongly_connected_components() const {
        return strongly_connected_components;
    }

    // non-owning pointer
    MatrixGraph<TWeight> const* graph = nullptr;
    std::vector<int> indices = {};
    std::vector<int> lowlinks = {};
    std::vector<int> stack = {};
    std::vector<bool> on_stack = {};
    std::vector<int> strongly_connected_components = {};
    int index = 0;
    int strongly_connected_component = 0;
};

template<typename TWeight>
struct StrongconnectContext {
    std::vector<std::vector<int>> neighbors;
    std::vector<int> indices;
    std::vector<int> lowlinks;
    std::vector<int> scc_stack;
    std::vector<bool> on_scc_stack;
    std::vector<int> sccs;
    int current_index;
    int current_scc;
};

template<typename TWeight>
void strongconnect(int initial, StrongconnectContext<TWeight>& c) {
    using NeighborsIter = std::vector<int>::iterator;
    using DFSContext = std::pair<int, NeighborsIter>;

    auto dfs_stack =
        std::vector {DFSContext {initial, c.neighbors.at(initial).begin()}};

    while (!dfs_stack.empty()) {
        auto [v, iter] = dfs_stack.back();
        dfs_stack.pop_back();

        if (c.indices.at(v) == -1) {
            c.indices.at(v) = c.current_index;
            c.lowlinks.at(v) = c.current_index;
            c.scc_stack.emplace_back(v);
            c.on_scc_stack.at(v) = true;
            ++c.current_index;
        } else {
            auto w = *iter;
            c.lowlinks.at(v) = std::min(c.lowlinks.at(v), c.lowlinks.at(w));

            ++iter;
        }

        auto skip = false;
        for (; iter != c.neighbors.at(v).end(); ++iter) {
            auto w = *iter;

            if (c.indices.at(w) == -1) {
                dfs_stack.emplace_back(v, iter);
                dfs_stack.emplace_back(w, c.neighbors.at(w).begin());
                skip = true;
                break;
            } else if (c.on_scc_stack.at(w)) {
                c.lowlinks.at(v) = std::min(c.lowlinks.at(v), c.indices.at(w));
            }
        }

        if (skip) {
            continue;
        }

        if (c.lowlinks.at(v) == c.indices.at(v)) {
            auto w = -1;
            do {
                w = c.scc_stack.back();
                c.scc_stack.pop_back();
                c.on_scc_stack.at(w) = false;
                c.sccs.at(w) = c.current_scc;
            } while (w != v);
            ++c.current_scc;
        }
    }
}

} // namespace detail
