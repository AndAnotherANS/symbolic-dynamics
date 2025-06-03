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


template<typename TWeight>
std::vector<Matrix<TWeight>> sccs_as_matrices(MatrixGraph<TWeight> const& graph)
{
    auto [sccs, n_sccs] = strongly_connected_components(graph);
    Eigen::PermutationMatrix<-1, -1, unsigned> node_permutation(graph.size());
    std::vector<unsigned> scc_sizes(n_sccs + 1);
    for (int &&i :  sccs) ++scc_sizes[i+1];
    auto scc_counters(scc_sizes);
    scc_counters.pop_back();
    for (int node = 0; node < graph.size(); node++)
        node_permutation.indices()(node) = scc_counters[sccs[node]]++;

    Matrix<TWeight> almost_block_matrix = (node_permutation * graph.get_adjacency_matrix()) * node_permutation.transpose();
    std::vector<Matrix<TWeight>> result;
    for (int i = 1; i < scc_sizes.size(); i++)\
        result.push_back(almost_block_matrix.block(scc_sizes[i-1], scc_sizes[i-1], scc_sizes[i], scc_sizes[i]));
    return result;
}