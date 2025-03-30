#pragma once

#include "Graph.hpp"
#include "detail/StronglyConnectedComponents.hpp"

// A structure for storing the return value of strongly_connected_components algorithm
struct StronglyConnectedComponentsRV {
    std::vector<int> strongly_connected_components;
    int number_of_strongly_connected_components;
};

// Tarjan's strongly connected components algorithm
template<typename TWeight>
StronglyConnectedComponentsRV
strongly_connected_components(Graph<TWeight> const& graph) {
    auto const n = graph.size();
    auto context = detail::StrongconnectContext<TWeight> {
        .neighbors = std::vector<std::vector<int>>(n),
        .indices = std::vector<int>(n, -1),
        .lowlinks = std::vector<int>(n, -1),
        .scc_stack = {},
        .on_scc_stack = std::vector(n, false),
        .sccs = std::vector<int>(n, -1),
        .current_index = 0,
        .current_scc = 0,
    };

    for (int v = 0; v < n; ++v) {
        context.neighbors.at(v) = graph.neighbors(v);
    }

    for (int v = 0; v < n; ++v) {
        if (context.indices.at(v) == -1) {
            detail::strongconnect(v, context);
        }
    }

    return {context.sccs, context.current_scc};
}
