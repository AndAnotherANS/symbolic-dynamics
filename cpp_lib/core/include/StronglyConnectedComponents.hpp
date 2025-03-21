#pragma once

#include "Graph.hpp"

namespace detail {

// Helper struct for the evaluation of
// Tarjan's strongly connected components algorithm
// Based on https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm
template<typename TWeight>
struct StronglyConnectedComponentsMatrixGraphTarjan {

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

    const std::vector<int>& get_strongly_connected_components() const {
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

} // namespace detail

// A structure for storing the return value of strongly_connected_components algorithm
struct StronglyConnectedComponentsRV {
    std::vector<int> strongly_connected_components;
    int number_of_strongly_connected_components;
};

// Tarjan's strongly connected components algorithm
template<typename TWeight>
StronglyConnectedComponentsRV
strongly_connected_components(MatrixGraph<TWeight> const& graph) {
    // TODO: replace with "graph is empty" check once implemented
    if (graph.get_adjacency_matrix().empty()) {
        return {{}, 0};
    }
    auto sccmg = detail::StronglyConnectedComponentsMatrixGraphTarjan(graph);
    sccmg.calculate_strongly_connected_components();
    return {
        // TODO: check if this requires an explicit move
        sccmg.strongly_connected_components,
        sccmg.strongly_connected_component
    };
}
