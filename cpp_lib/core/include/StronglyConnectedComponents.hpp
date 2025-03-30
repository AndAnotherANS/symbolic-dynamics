#pragma once

#include <limits>

#include "Graph.hpp"
#include "detail/StronglyConnectedComponents.hpp"

// A structure for storing the return value of strongly_connected_components algorithm
struct StronglyConnectedComponentsRV {
    std::vector<unsigned int> strongly_connected_components;
    unsigned int number_of_strongly_connected_components;
};

// Tarjan's strongly connected components algorithm
template<typename TWeight>
StronglyConnectedComponentsRV
strongly_connected_components(Graph<TWeight> const& graph) {
    constexpr auto unsigned_int_max = std::numeric_limits<unsigned int>::max();
    auto const n = graph.size();
    auto context = detail::StrongconnectContext<TWeight> {
        .neighbors = std::vector<std::vector<unsigned int>>(n),
        .indices = std::vector<unsigned int>(n, unsigned_int_max),
        .lowlinks = std::vector<unsigned int>(n, unsigned_int_max),
        .scc_stack = {},
        .sccs = std::vector<unsigned int>(n, unsigned_int_max),
        .on_scc_stack = std::vector(n, false),
        .current_index = 0,
        .current_scc = 0,
    };

    for (unsigned int v = 0; v < n; ++v) {
        context.neighbors.at(v) = graph.neighbors(v);
    }

    for (unsigned int v = 0; v < n; ++v) {
        if (context.indices.at(v) == unsigned_int_max) {
            detail::strongconnect(v, context);
        }
    }

    return {context.sccs, context.current_scc};
}
