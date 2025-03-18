#include "Graph.hpp"
#include <string>
#include <vector>

template <typename TWeight>
MatrixGraph<TWeight>::MatrixGraph() {}

template <typename TWeight>
MatrixGraph<TWeight>::MatrixGraph(int nodes) {
    adjacency_matrix = std::vector<std::vector<TWeight>>(nodes, std::vector<TWeight>(nodes, TWeight()));
    label_matrix = std::vector<std::vector<std::string>>(nodes, std::vector<std::string>(nodes, ""));
}

template <typename TWeight>
MatrixGraph<TWeight>::MatrixGraph(const Matrix& adjacency_matrix, const LabelMatrix& label_matrix)
    : adjacency_matrix(adjacency_matrix), label_matrix(label_matrix) {}

template <typename TWeight>
int MatrixGraph<TWeight>::add_node() 
{
    for (auto& row : adjacency_matrix) 
    {
        row.push_back(TWeight());
    }
    adjacency_matrix.push_back(std::vector<TWeight>(adjacency_matrix.size() + 1, TWeight()));
    
    for (auto& row : label_matrix) 
    {
        row.push_back("");
    }
    label_matrix.push_back(std::vector<std::string>(label_matrix.size() + 1, ""));

    return adjacency_matrix.size() - 1;
}

template <typename TWeight>
void MatrixGraph<TWeight>::add_edge(const int src, const int dest, TWeight weight, std::string label) 
{
    adjacency_matrix[src][dest] = weight;
    label_matrix[src][dest] = label;
}

template <typename TWeight>
const typename MatrixGraph<TWeight>::Matrix& MatrixGraph<TWeight>::get_adjacency_matrix() const 
{
    return adjacency_matrix;
}

template <typename TWeight>
const typename MatrixGraph<TWeight>::LabelMatrix& MatrixGraph<TWeight>::get_label_matrix() const 
{
    return label_matrix;
}

template <typename TWeight>
AdjacencyListGraph<TWeight>::AdjacencyListGraph() {}

template <typename TWeight>
AdjacencyListGraph<TWeight>::AdjacencyListGraph(int nodes) 
{
    adjacency_list = std::vector<std::vector<Edge>>(nodes, std::vector<Edge>());
}

template <typename TWeight>
AdjacencyListGraph<TWeight>::AdjacencyListGraph(const AdjacencyList& adjacency_list)
    : adjacency_list(adjacency_list) {}

template <typename TWeight>
int AdjacencyListGraph<TWeight>::add_node() 
{
    adjacency_list.push_back(std::vector<Edge>());
    return adjacency_list.size() - 1;
}

template <typename TWeight>
void AdjacencyListGraph<TWeight>::add_edge(const int src, const int dest, const TWeight weight, std::string label) 
{
    Edge edge = {dest, weight, label};
    adjacency_list[src].push_back(edge);
}

template <typename TWeight>
const typename AdjacencyListGraph<TWeight>::AdjacencyList& AdjacencyListGraph<TWeight>::get_adjacency_list() const 
{
    return adjacency_list;
}
