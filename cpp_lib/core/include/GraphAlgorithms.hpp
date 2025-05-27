#pragma once

#include <limits>

#include "Graph.hpp"
#include "detail/GraphAlgorithms.hpp"

// A structure for storing the return value of strongly_connected_components
// algorithm
struct StronglyConnectedComponentsRV {
    std::vector<unsigned int> strongly_connected_components;
    unsigned int number_of_strongly_connected_components;
};

// Tarjan's strongly connected components algorithm
template<typename TWeight>
StronglyConnectedComponentsRV
strongly_connected_components(Graph<TWeight> const& graph) {
    auto context = detail::strongly_connected_components(graph);
    return {context.sccs, context.current_scc};
}

// Period of a graph
//
// The greatest number k >= 1 that divides the length of all cycles of
// the graph or 0 if the graph is acyclic
template<typename TWeight>
int period(Graph<TWeight> const& graph) {
    const auto& [_, gcd] = detail::period(graph);
    return gcd;
}

// Test if the graph is aperiodic
template<typename TWeight>
bool is_aperiodic(Graph<TWeight> const& graph) {
    return period(graph) == 1;
}

// Test if the graph is primitive
template<typename TWeight>
bool is_primitive(Graph<TWeight> const& graph) {
    const auto& [context, gcd] = detail::period(graph);
    return context.current_scc == 1 && gcd == 1;
}
