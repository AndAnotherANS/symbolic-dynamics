#pragma once
#include "Utils.hpp"
#include "eigen3/Eigen/Dense"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "Matrix.hpp"

template <typename TWeight = double> struct Edge
{
    unsigned int source = 0;
    unsigned int dest = 0;
    TWeight weight = 0;
    Word label = Word();

    bool operator<(const Edge &other) const
    {
        if (source == other.source)
            return dest < other.dest;
        return source < other.source;
    }
};

struct Node
{
    int index;
    Word label;

    bool operator<(const Node &other) const
    {
        return index < other.index;
    }
};

template <typename TWeight = double> class Graph
{
  public:
    virtual void add_edge(unsigned int src, unsigned int dest, TWeight weight, Word label) = 0;

    virtual void remove_edge(unsigned int src, unsigned int dest) = 0;

    virtual unsigned int add_node(Word label) = 0;

    [[nodiscard]] virtual std::vector<Edge<TWeight>> edges() const = 0;

    [[nodiscard]] virtual std::vector<Node> nodes() const;

    [[nodiscard]] virtual bool edge_exists(unsigned int src, unsigned int dest) const;

    [[nodiscard]] virtual TWeight get_edge_weight(unsigned int src, unsigned int dest) const = 0;

    [[nodiscard]] virtual Word get_edge_label(unsigned int src, unsigned int dest) const = 0;

    [[nodiscard]] virtual Word get_node_label(unsigned int index) const;

    virtual void set_node_label(unsigned int index, Word label);

    virtual void set_edge_label(unsigned int src, unsigned int dest, Word label) = 0;

    virtual void set_edge_weight(unsigned int src, unsigned int dest, TWeight weight) = 0;

    [[nodiscard]] virtual std::vector<unsigned int> neighbors(unsigned int index) const = 0;

    [[nodiscard]] virtual unsigned int size() const = 0;

    [[nodiscard]] virtual bool empty() const;

    virtual ~Graph() = default;

  protected:
    virtual void validate_indices(unsigned int src, unsigned int dest) const;
    std::vector<Word> node_labels = {};
};

template <typename TWeight = double> class MatrixGraph : public Graph<TWeight>
{

  public:
    typedef std::vector<std::vector<Word>> LabelMatrix;

    // Empty constructor
    MatrixGraph() = default;

    explicit MatrixGraph(unsigned int nodes);

    MatrixGraph(unsigned int nodes, const std::vector<Word> &labels);

    MatrixGraph(Matrix<TWeight> adjacency_matrix, LabelMatrix label_matrix);

    MatrixGraph(const MatrixGraph &) = default;

    MatrixGraph &operator=(const MatrixGraph &other);

    void add_edge(unsigned int src, unsigned int dest, TWeight weight, Word label) override;

    void remove_edge(unsigned int src, unsigned int dest) override;

    int unsigned add_node(Word label) override;

    std::vector<Edge<TWeight>> edges() const override;

    [[nodiscard]] TWeight get_edge_weight(unsigned int src, unsigned int dest) const override;

    [[nodiscard]] Word get_edge_label(unsigned int src, unsigned int dest) const override;

    void set_edge_label(unsigned int src, unsigned int dest, Word label) override;

    void set_edge_weight(unsigned int src, unsigned int dest, TWeight weight) override;

    [[nodiscard]] std::vector<unsigned int> neighbors(unsigned int index) const override;

    [[nodiscard]] unsigned int size() const override;

    const Matrix<TWeight> &get_adjacency_matrix() const;

    [[nodiscard]] const LabelMatrix &get_label_matrix() const;

    ~MatrixGraph() override = default;

  protected:
    LabelMatrix label_matrix = {};
    Matrix<TWeight> adjacency_matrix = {};
};

template <typename TWeight = double> class AdjacencyListGraph : public Graph<TWeight>
{
  public:
    typedef std::vector<std::unordered_map<int, Edge<TWeight>>> AdjacencyList;

    // Empty constructor
    AdjacencyListGraph() = default;

    explicit AdjacencyListGraph(unsigned int nodes);

    explicit AdjacencyListGraph(AdjacencyList adjacency_list);

    AdjacencyListGraph(const AdjacencyListGraph &) = default;

    AdjacencyListGraph &operator=(const AdjacencyListGraph &);

    int unsigned add_node(Word label) override;

    void add_edge(unsigned int src, unsigned int dest, TWeight weight, Word label) override;

    void remove_edge(unsigned int src, unsigned int dest) override;

    std::vector<Edge<TWeight>> edges() const override;

    TWeight get_edge_weight(unsigned int src, unsigned int dest) const override;

    [[nodiscard]] Word get_edge_label(unsigned int src, unsigned int dest) const override;

    void set_edge_label(unsigned int src, unsigned int dest, Word label) override;

    void set_edge_weight(unsigned int src, unsigned int dest, TWeight weight) override;

    [[nodiscard]] std::vector<unsigned int> neighbors(unsigned int index) const override;

    [[nodiscard]] unsigned int size() const override;

    const AdjacencyList &get_adjacency_list() const;

    ~AdjacencyListGraph() override = default;

  protected:
    AdjacencyList adjacency_list = {};
};

// Graph implementations
template <typename TWeight> bool Graph<TWeight>::edge_exists(unsigned int src, unsigned int dest) const
{
    // We assume by design that weight of 0 means no edge
    return get_edge_weight(src, dest) != TWeight();
}

template <typename TWeight> bool Graph<TWeight>::empty() const
{
    return size() == 0;
}

template <typename TWeight> Word Graph<TWeight>::get_node_label(unsigned int index) const
{
    this->validate_indices(index, 0);
    return node_labels[index];
}

template <typename TWeight> std::vector<Node> Graph<TWeight>::nodes() const
{
    std::vector<Node> nodes;
    for (int i = 0; i < node_labels.size(); i++)
    {
        Node node = {i, node_labels[i]};
        nodes.push_back(node);
    }
    return nodes;
}

template <typename TWeight> void Graph<TWeight>::set_node_label(unsigned int index, Word label)
{
    if (index > node_labels.size())
    {
        return; // todo: log warning
    }

    node_labels[index] = std::move(label);
}

template <typename TWeight> void Graph<TWeight>::validate_indices(unsigned int src, unsigned int dest) const
{
    if (src >= size() || dest >= size())
    {
        throw std::out_of_range("Source or destination index out of range");
    }
}

// MatrixGraph implementations

template <typename TWeight> MatrixGraph<TWeight>::MatrixGraph(unsigned int nodes)
{
    adjacency_matrix = Matrix<TWeight>::Zero(nodes, nodes);
    label_matrix = std::vector(nodes, std::vector(nodes, Word()));
    this->node_labels = std::vector(nodes, Word());
}

template <typename TWeight> MatrixGraph<TWeight>::MatrixGraph(unsigned int nodes, const std::vector<Word> &labels)
{
    if (labels.size() != nodes)
    {
        throw std::invalid_argument("Number of labels must match number of nodes");
    }
    adjacency_matrix = Matrix<TWeight>::Zero(nodes, nodes);
    label_matrix = std::vector(nodes, std::vector(nodes, Word()));
    this->node_labels = labels;
}

template <typename TWeight>
MatrixGraph<TWeight>::MatrixGraph(Matrix<TWeight> adjacency_matrix, LabelMatrix label_matrix)
    : label_matrix(std::move(label_matrix)), adjacency_matrix(std::move(adjacency_matrix))
{
}

template <typename TWeight> MatrixGraph<TWeight> &MatrixGraph<TWeight>::operator=(const MatrixGraph &other)
{
    this->node_labels = other.node_labels;
    this->adjacency_matrix = other.adjacency_matrix;
    this->label_matrix = other.label_matrix;
    return *this;
}

template <typename TWeight> unsigned int MatrixGraph<TWeight>::add_node(Word label)
{
    unsigned int new_size = this->size() + 1;
    adjacency_matrix.conservativeResize(new_size, new_size);
    Eigen::Matrix<TWeight, 1, -1> zeros = Eigen::Matrix<TWeight, 1, -1>::Zero(new_size);
    adjacency_matrix.row(new_size-1) << zeros;
    Eigen::Matrix<TWeight, -1, 1> zeros_col = Eigen::Matrix<TWeight, -1, 1>::Zero(new_size);
    adjacency_matrix.col(new_size-1) << zeros_col;

    for (auto &row : label_matrix)
    {
        row.emplace_back();
    }
    label_matrix.emplace_back(label_matrix.size() + 1, Word());

    this->node_labels.push_back(label);
    return this->size() - 1;
}

template <typename TWeight>
void MatrixGraph<TWeight>::add_edge(const unsigned int src, const unsigned int dest, TWeight weight, Word label)
{
    this->validate_indices(src, dest);
    if (weight == TWeight() || this->edge_exists(src, dest))
    {
        return;
    }
    adjacency_matrix(src, dest) = weight;
    label_matrix[src][dest] = label;
}

template <typename TWeight> void MatrixGraph<TWeight>::remove_edge(const unsigned int src, const unsigned int dest)
{
    this->validate_indices(src, dest);
    if (!this->edge_exists(src, dest))
    {
        return; // todo: log warning if edge does not exist
    }
    adjacency_matrix(src, dest) = TWeight();
    label_matrix[src][dest] = Word();
}

template <typename TWeight> [[nodiscard]] std::vector<Edge<TWeight>> MatrixGraph<TWeight>::edges() const
{
    std::vector<Edge<TWeight>> edges;
    for (unsigned int i = 0; i < this->size(); i++) // first ordered by rows (sources)
    {
        for (unsigned int j = 0; j < this->size(); j++) // second ordered by columns (destinations)
        {
            if (adjacency_matrix(i, j) != TWeight())
            {
                Edge<TWeight> edge = {i, j, adjacency_matrix(i, j), label_matrix[i][j]};
                edges.push_back(edge);
            }
        }
    }
    return edges;
}

template <typename TWeight> TWeight MatrixGraph<TWeight>::get_edge_weight(unsigned int src, unsigned int dest) const
{
    this->validate_indices(src, dest);
    return adjacency_matrix(src, dest);
}

template <typename TWeight> Word MatrixGraph<TWeight>::get_edge_label(unsigned int src, unsigned int dest) const
{
    this->validate_indices(src, dest);
    return label_matrix[src][dest];
}

template <typename TWeight>
void MatrixGraph<TWeight>::set_edge_label(unsigned int src, unsigned int dest, Word label)
{
    this->validate_indices(src, dest);
    if (!this->edge_exists(src, dest))
    {
        return; // todo: log warning
    }

    label_matrix[src][dest] = label;
}

template <typename TWeight>
void MatrixGraph<TWeight>::set_edge_weight(unsigned int src, unsigned int dest, TWeight weight)
{
    this->validate_indices(src, dest);
    if (!this->edge_exists(src, dest))
    {
        return; // todo: log warning
    }
    adjacency_matrix(src, dest) = weight;
}

template <typename TWeight> std::vector<unsigned int> MatrixGraph<TWeight>::neighbors(unsigned int index) const
{
    this->validate_indices(index, 0);
    std::vector<unsigned int> neighbors;
    for (int i = 0; i < this->size(); i++)
    {
        if (adjacency_matrix(index, i) != TWeight())
        {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

template <typename TWeight> unsigned int MatrixGraph<TWeight>::size() const
{
    return adjacency_matrix.rows();
}

template <typename TWeight>
const Matrix<TWeight> &MatrixGraph<TWeight>::get_adjacency_matrix() const
{
    return adjacency_matrix;
}

template <typename TWeight>
const typename MatrixGraph<TWeight>::LabelMatrix &MatrixGraph<TWeight>::get_label_matrix() const
{
    return label_matrix;
}

// AdjacencyListGraph implementations

template <typename TWeight> AdjacencyListGraph<TWeight>::AdjacencyListGraph(unsigned int nodes)
{
    adjacency_list = std::vector<std::unordered_map<int, Edge<TWeight>>>(nodes);
    this->node_labels = std::vector<Word>(nodes, Word());
}

template <typename TWeight>
AdjacencyListGraph<TWeight>::AdjacencyListGraph(AdjacencyList adjacency_list)
    : adjacency_list(std::move(adjacency_list))
{
}

template <typename TWeight>
AdjacencyListGraph<TWeight> &AdjacencyListGraph<TWeight>::operator=(const AdjacencyListGraph &other)
{
    this->node_labels = other.node_labels;
    this->adjacency_list = other.adjacency_list;
    return *this;
}

template <typename TWeight> unsigned int AdjacencyListGraph<TWeight>::add_node(Word label)
{
    adjacency_list.push_back(std::unordered_map<int, Edge<TWeight>>());
    this->node_labels.push_back(label);

    return adjacency_list.size() - 1;
}

template <typename TWeight>
void AdjacencyListGraph<TWeight>::add_edge(const unsigned int src, const unsigned int dest, const TWeight weight,
                                           Word label)
{
    this->validate_indices(src, dest);
    if (weight == TWeight() || this->edge_exists(src, dest))
    {
        return;
    }
    Edge<TWeight> edge = {src, dest, weight, label};
    adjacency_list[src][dest] = edge;
}

template <typename TWeight>
void AdjacencyListGraph<TWeight>::remove_edge(const unsigned int src, const unsigned int dest)
{
    this->validate_indices(src, dest);
    if (!this->edge_exists(src, dest))
    {
        return; // todo: log warning if edge does not exist
    }

    adjacency_list[src].erase(dest);
}

template <typename TWeight> std::vector<Edge<TWeight>> AdjacencyListGraph<TWeight>::edges() const
{
    std::vector<Edge<TWeight>> edges;
    for (int i = 0; i < adjacency_list.size(); i++)
    {
        for (auto &it : adjacency_list[i])
        {
            edges.push_back(it.second);
        }
    }
    std::sort(edges.begin(), edges.end());
    return edges;
}

template <typename TWeight>
TWeight AdjacencyListGraph<TWeight>::get_edge_weight(unsigned int src, unsigned int dest) const
{
    this->validate_indices(src, dest);
    if (adjacency_list[src].find(dest) != adjacency_list[src].end())
    {
        return adjacency_list[src].at(dest).weight;
    }
    return TWeight();
}

template <typename TWeight>
Word AdjacencyListGraph<TWeight>::get_edge_label(unsigned int src, unsigned int dest) const
{
    this->validate_indices(src, dest);
    if (adjacency_list[src].find(dest) != adjacency_list[src].end())
    {
        return adjacency_list[src].at(dest).label;
    }
    return {};
}

template <typename TWeight>
void AdjacencyListGraph<TWeight>::set_edge_label(unsigned int src, unsigned int dest, Word label)
{
    this->validate_indices(src, dest);
    if (this->edge_exists(src, dest))
    {
        adjacency_list[src][dest].label = label;
    }
}

template <typename TWeight>
void AdjacencyListGraph<TWeight>::set_edge_weight(unsigned int src, unsigned int dest, TWeight weight)
{
    this->validate_indices(src, dest);
    if (this->edge_exists(src, dest))
    {
        adjacency_list[src][dest].weight = weight;
    }
}

template <typename TWeight> std::vector<unsigned int> AdjacencyListGraph<TWeight>::neighbors(unsigned int index) const
{
    this->validate_indices(index, 0);
    std::vector<unsigned int> neighbors;
    for (auto &it : adjacency_list[index])
    {
        neighbors.push_back(it.first);
    }
    return neighbors;
}

template <typename TWeight> unsigned int AdjacencyListGraph<TWeight>::size() const
{
    return adjacency_list.size();
}

template <typename TWeight>
const typename AdjacencyListGraph<TWeight>::AdjacencyList &AdjacencyListGraph<TWeight>::get_adjacency_list() const
{
    return adjacency_list;
}

template class AdjacencyListGraph<double>;
typedef AdjacencyListGraph<> WeightedAdjacencyListGraph;

template class AdjacencyListGraph<unsigned int>;
typedef AdjacencyListGraph<int> UnweightedAdjacencyListGraph;

template class MatrixGraph<double>;
typedef MatrixGraph<> WeightedMatrixGraph;

class UnweightedMatrixGraph final : public MatrixGraph<unsigned int>
{
  public:
    // Empty constructor
    UnweightedMatrixGraph() = default;

    explicit UnweightedMatrixGraph(unsigned int nodes);

    UnweightedMatrixGraph(unsigned int nodes, const std::vector<Word> &labels) : MatrixGraph(nodes, labels) {};

    UnweightedMatrixGraph(Matrix<unsigned int> adjacency_matrix, LabelMatrix label_matrix) : MatrixGraph(std::move(adjacency_matrix), std::move(label_matrix)) {};

    UnweightedMatrixGraph(const UnweightedMatrixGraph &) = default;

    [[nodiscard]] UnweightedMatrixGraph complement() const;
};

inline UnweightedMatrixGraph UnweightedMatrixGraph::complement() const
{
    Matrix<unsigned int>  edge_matrix;
    edge_matrix.resize(size(), size());
    edge_matrix.fill(1);
    for (auto && edge: edges())
        edge_matrix(edge.source, edge.dest) = 0;
    std::vector<std::vector<Word>>  label_matrix;
    for (unsigned int i = 0; i < size(); ++i)
        label_matrix.emplace_back(size(), Word());

    return {edge_matrix, label_matrix};
}
