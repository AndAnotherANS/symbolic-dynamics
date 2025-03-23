#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

template <typename TWeight=double>
struct Edge
{
    int source;
    int dest;
    TWeight weight;
    std::string label;
};

struct Node
{
    int index;
    std::string label;
};

template <typename TWeight=double>
class Graph
{
public:

    virtual void add_edge(const int src, const int dest, TWeight weight, std::string label="") = 0;

    virtual void remove_edge(const int src, const int dest) = 0;

    virtual int add_node(std::string label="") = 0;

    virtual std::vector<Edge<TWeight> > edges() const = 0;

    virtual std::vector<Node> nodes() const;

    virtual bool edge_exists(int src, int dest) const;

    virtual TWeight get_edge_weight(int src, int dest) const = 0;

    virtual std::string get_edge_label(int src, int dest) const = 0;

    virtual std::string get_node_label(int index) const;

    virtual void set_node_label(int index, std::string label);

    virtual void set_edge_label(int src, int dest, std::string label) = 0;

    virtual void set_edge_weight(int src, int dest, TWeight weight) = 0;

    virtual std::vector<int> neighbors(int index) const = 0;

    virtual int size() const = 0;

    virtual bool empty() const;

protected:
    virtual void validate_indices(int src, int dest=0) const;
    std::vector<std::string> node_labels = {};
};

template <typename TWeight=double>
class MatrixGraph : public Graph<TWeight>
{
    typedef std::vector<std::vector<TWeight>> Matrix;
    typedef std::vector<std::vector<std::string>> LabelMatrix;
public:
    // Empty constructor
    MatrixGraph();

    MatrixGraph(int nodes);

    MatrixGraph(const Matrix& adjacency_matrix, const LabelMatrix& label_matrix);

    virtual void add_edge(const int src, const int dest, TWeight weight, std::string label) override;

    virtual void remove_edge(const int src, const int dest) override;

    virtual int add_node(std::string label) override;

    virtual std::vector<Edge<TWeight> > edges() const override;

    virtual TWeight get_edge_weight(int src, int dest) const override;

    virtual std::string get_edge_label(int src, int dest) const override;

    virtual void set_edge_label(int src, int dest, std::string label) override;

    virtual void set_edge_weight(int src, int dest, TWeight weight) override;

    virtual std::vector<int> neighbors(int index) const override;

    virtual int size() const override;

    const Matrix& get_adjacency_matrix() const;

    const LabelMatrix& get_label_matrix() const;

protected:
    LabelMatrix label_matrix = {};
    Matrix adjacency_matrix = {};

};

template <typename TWeight=double>
class AdjacencyListGraph: public Graph<TWeight>
{

    typedef std::vector<std::unordered_map<int, Edge<TWeight> > > AdjacencyList;
public:
    // Empty constructor
    AdjacencyListGraph();

    AdjacencyListGraph(int nodes);

    AdjacencyListGraph(const AdjacencyList& adjacency_list);

    virtual int add_node(std::string label="") override;

    virtual void add_edge(const int src, const int dest, const TWeight weight, std::string label);

    virtual void remove_edge(const int src, const int dest);

    virtual std::vector<Edge<TWeight> > edges() const override;

    virtual TWeight get_edge_weight(int src, int dest) const override;

    virtual std::string get_edge_label(int src, int dest) const override;

    virtual void set_edge_label(int src, int dest, std::string label) override;

    virtual void set_edge_weight(int src, int dest, TWeight weight) override;

    virtual std::vector<int> neighbors(int index) const override;

    virtual int size() const override;

    const AdjacencyList& get_adjacency_list() const;

protected:
    AdjacencyList adjacency_list = {};
};


// Graph implementations
template <typename TWeight>
bool Graph<TWeight>::edge_exists(int src, int dest) const
{
    // We assume by design that weight of 0 means no edge
    return get_edge_weight(src, dest) != TWeight();
}

template <typename TWeight>
bool Graph<TWeight>::empty() const
{
    return size() == 0;
}

template <typename TWeight>
std::string Graph<TWeight>::get_node_label(int index) const
{
    this->validate_indices(index);
    return node_labels[index];
}

template <typename TWeight>
std::vector<Node> Graph<TWeight>::nodes() const
{
    std::vector<Node> nodes;
    for (int i = 0; i < node_labels.size(); i++)
    {
        Node node = {i, node_labels[i]};
        nodes.push_back(node);
    }
    return nodes;
}

template <typename TWeight>
void Graph<TWeight>::set_node_label(int index, std::string label) 
{
    if (index < 0 || index > node_labels.size())
    {
        return; // todo: log warning
    }
    
    node_labels[index] = label;
}

template <typename TWeight>
void Graph<TWeight>::validate_indices(int src, int dest) const
{
    if(src < 0 || src >= size() || dest < 0 || dest >= size())
    {
        throw std::out_of_range("Source or destination index out of range");
    }
}

// MatrixGraph implementations
template <typename TWeight>
MatrixGraph<TWeight>::MatrixGraph() {}

template <typename TWeight>
MatrixGraph<TWeight>::MatrixGraph(int nodes) {
    adjacency_matrix = std::vector<std::vector<TWeight>>(nodes, std::vector<TWeight>(nodes, TWeight()));
    label_matrix = std::vector<std::vector<std::string>>(nodes, std::vector<std::string>(nodes, ""));
    this->node_labels = std::vector<std::string>(nodes, "");
}

template <typename TWeight>
MatrixGraph<TWeight>::MatrixGraph(const Matrix& adjacency_matrix, const LabelMatrix& label_matrix)
    : adjacency_matrix(adjacency_matrix), label_matrix(label_matrix) {}

template <typename TWeight>
int MatrixGraph<TWeight>::add_node(std::string label) 
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

    this->node_labels.push_back(label);
    return adjacency_matrix.size() - 1;
}

template <typename TWeight>
void MatrixGraph<TWeight>::add_edge(const int src, const int dest, TWeight weight, std::string label)
{
    this->validate_indices(src, dest);
    if (weight == TWeight() || this->edge_exists(src, dest))
    {
        return;
    }
    adjacency_matrix[src][dest] = weight;
    label_matrix[src][dest] = label;
}

template <typename TWeight>
void MatrixGraph<TWeight>::remove_edge(const int src, const int dest) 
{
    this->validate_indices(src, dest);
    if (!this->edge_exists(src, dest))
    {
        return; // todo: log warning if edge does not exist
    }
    adjacency_matrix[src][dest] = TWeight();
    label_matrix[src][dest] = "";
}

template <typename TWeight>
std::vector<Edge<TWeight> > MatrixGraph<TWeight>::edges() const 
{
    std::vector<Edge<TWeight> > edges;
    for (int i = 0; i < adjacency_matrix.size(); i++) 
    {
        for (int j = 0; j < adjacency_matrix[i].size(); j++) 
        {
            if (adjacency_matrix[i][j] != TWeight()) 
            {
                Edge<TWeight> edge = {i, j, adjacency_matrix[i][j], label_matrix[i][j]};
                edges.push_back(edge);
            }
        }
    }
    return edges;
}


template <typename TWeight>
TWeight MatrixGraph<TWeight>::get_edge_weight(int src, int dest) const 
{
    this->validate_indices(src, dest);
    return adjacency_matrix[src][dest];
}

template <typename TWeight>
std::string MatrixGraph<TWeight>::get_edge_label(int src, int dest) const 
{
    this->validate_indices(src, dest);
    return label_matrix[src][dest];
}


template <typename TWeight>
void MatrixGraph<TWeight>::set_edge_label(int src, int dest, std::string label) 
{
    this->validate_indices(src, dest);
    if (!this->edge_exists(src, dest))
    {
        return; // todo: log warning
    }
    
    label_matrix[src][dest] = label;
}

template <typename TWeight>
void MatrixGraph<TWeight>::set_edge_weight(int src, int dest, TWeight weight) 
{
    this->validate_indices(src, dest);
    if (!this->edge_exists(src, dest))
    {
        return; // todo: log warning
    }
    adjacency_matrix[src][dest] = weight;
}

template <typename TWeight>
std::vector<int> MatrixGraph<TWeight>::neighbors(int index) const 
{
    this->validate_indices(index);
    std::vector<int> neighbors;
    for (int i = 0; i < adjacency_matrix[index].size(); i++) 
    {
        if (adjacency_matrix[index][i] != TWeight()) 
        {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

template <typename TWeight>
int MatrixGraph<TWeight>::size() const 
{
    return adjacency_matrix.size();
}

template <typename TWeight>
const typename MatrixGraph<TWeight>::Matrix&  MatrixGraph<TWeight>::get_adjacency_matrix() const 
{
    return adjacency_matrix;
}

template <typename TWeight>
const typename MatrixGraph<TWeight>::LabelMatrix&  MatrixGraph<TWeight>::get_label_matrix() const 
{
    return label_matrix;
}

// AdjacencyListGraph implementations

template <typename TWeight>
AdjacencyListGraph<TWeight>::AdjacencyListGraph() {}

template <typename TWeight>
AdjacencyListGraph<TWeight>::AdjacencyListGraph(int nodes) 
{
    adjacency_list = std::vector<std::unordered_map<int, Edge<TWeight>>>(nodes);
    this->node_labels = std::vector<std::string>(nodes, "");
}

template <typename TWeight>
AdjacencyListGraph<TWeight>::AdjacencyListGraph(const AdjacencyList& adjacency_list)
    : adjacency_list(adjacency_list) {}

template <typename TWeight>
int AdjacencyListGraph<TWeight>::add_node(std::string label) 
{
    adjacency_list.push_back(std::unordered_map<int, Edge<TWeight> >());
    this->node_labels.push_back(label);
    
    return adjacency_list.size() - 1;
}

template <typename TWeight>
void AdjacencyListGraph<TWeight>::add_edge(const int src, const int dest, const TWeight weight, std::string label) 
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
void AdjacencyListGraph<TWeight>::remove_edge(const int src, const int dest) 
{
    this->validate_indices(src, dest);
    if (!this->edge_exists(src, dest))
    {
        return; // todo: log warning if edge does not exist
    }
    
    adjacency_list[src].erase(dest);
}

template <typename TWeight>
std::vector<Edge<TWeight> > AdjacencyListGraph<TWeight>::edges() const 
{
    std::vector<Edge<TWeight> > edges;
    for (int i = 0; i < adjacency_list.size(); i++) 
    {
        for (auto& it : adjacency_list[i]) 
        {
            edges.push_back(it.second);
        }
    }
    return edges;
}

template <typename TWeight>
TWeight AdjacencyListGraph<TWeight>::get_edge_weight(int src, int dest) const 
{
    this->validate_indices(src, dest);
    if (adjacency_list[src].find(dest) != adjacency_list[src].end()) 
    {
        return adjacency_list[src].at(dest).weight;
    }
    return TWeight();
}

template <typename TWeight>
std::string AdjacencyListGraph<TWeight>::get_edge_label(int src, int dest) const 
{
    this->validate_indices(src, dest);
    if (adjacency_list[src].find(dest) != adjacency_list[src].end()) 
    {
        return adjacency_list[src].at(dest).label;
    }
    return "";
}

template <typename TWeight>
void AdjacencyListGraph<TWeight>::set_edge_label(int src, int dest, std::string label) 
{
    this->validate_indices(src, dest);
    if (this->edge_exists(src, dest))
    {
        adjacency_list[src][dest].label = label;
    }
}

template <typename TWeight>
void AdjacencyListGraph<TWeight>::set_edge_weight(int src, int dest, TWeight weight) 
{
    this->validate_indices(src, dest);
    if (this->edge_exists(src, dest))
    {
        adjacency_list[src][dest].weight = weight;
    }
}

template <typename TWeight>
std::vector<int> AdjacencyListGraph<TWeight>::neighbors(int index) const 
{
    this->validate_indices(index);
    std::vector<int> neighbors;
    for (auto& it : adjacency_list[index]) 
    {
        neighbors.push_back(it.first);
    }
    return neighbors;
}

template <typename TWeight>
int AdjacencyListGraph<TWeight>::size() const 
{
    return adjacency_list.size();
}

template <typename TWeight>
const typename AdjacencyListGraph<TWeight>::AdjacencyList& AdjacencyListGraph<TWeight>::get_adjacency_list() const 
{
    return adjacency_list;
}



template class AdjacencyListGraph<double>;
typedef AdjacencyListGraph<double> WeightedAdjacencyListGraph;

template class AdjacencyListGraph<int>;
typedef AdjacencyListGraph<int> UnweightedAdjacencyListGraph;

template class MatrixGraph<double>;
typedef MatrixGraph<double> WeightedMatrixGraph;

template class MatrixGraph<int>;
typedef MatrixGraph<int> UnweightedMatrixGraph;

