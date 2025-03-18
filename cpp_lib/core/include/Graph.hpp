#pragma once
#include <vector>
#include <string>

template <typename TWeight=float>
class MatrixGraph 
{
    typedef std::vector<std::vector<TWeight>> Matrix;
    typedef std::vector<std::vector<std::string>> LabelMatrix;
public:
    // Empty constructor
    MatrixGraph();

    MatrixGraph(int nodes);

    MatrixGraph(const Matrix& adjacency_matrix, const LabelMatrix& label_matrix);

    void add_edge(const int src, const int dest, TWeight weight, std::string label);

    int add_node();

    const Matrix& get_adjacency_matrix() const;

    const LabelMatrix& get_label_matrix() const;

private:
    LabelMatrix label_matrix;
    Matrix adjacency_matrix;

};

template <typename TWeight=float>
class AdjacencyListGraph
{
    struct Edge
    {
        int dest;
        TWeight weight;
        std::string label;
    };
    typedef std::vector<std::vector<Edge>> AdjacencyList;
public:
    // Empty constructor
    AdjacencyListGraph();

    AdjacencyListGraph(int nodes);

    AdjacencyListGraph(const AdjacencyList& adjacency_list);

    int add_node();

    void add_edge(const int src, const int dest, const TWeight weight, std::string label);

    const AdjacencyList& get_adjacency_list() const;

private:
    AdjacencyList adjacency_list;
};

template class AdjacencyListGraph<float>;
typedef AdjacencyListGraph<float> WeightedAdjacencyListGraph;

template class AdjacencyListGraph<int>;
typedef AdjacencyListGraph<int> UnweightedAdjacencyListGraph;

template class MatrixGraph<float>;
typedef MatrixGraph<float> WeightedMatrixGraph;

template class MatrixGraph<int>;
typedef MatrixGraph<int> UnweightedMatrixGraph;
