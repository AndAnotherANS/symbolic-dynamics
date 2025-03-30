#include <gtest/gtest.h>
#include "Graph.hpp"

TEST(MatrixGraph, Constructor) 
{
    MatrixGraph<double> graph; 
    ASSERT_EQ(graph.size(), 0);
    ASSERT_TRUE(graph.empty());

    MatrixGraph<double> graph2(3);
    ASSERT_EQ(graph2.size(), 3);
    ASSERT_FALSE(graph2.empty());

    std::vector<std::vector<double>> expected_adjacency_matrix = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    std::vector<std::vector<Word> > expected_label_matrix = {{ Word(), Word(), Word()}, { Word(), Word(), Word()}, { Word(), Word(), Word()}};
    ASSERT_EQ(graph2.get_adjacency_matrix(), expected_adjacency_matrix);
    ASSERT_EQ(graph2.get_label_matrix(), expected_label_matrix);
}

TEST(MatrixGraph, VertexEdgeAdding) 
{
    MatrixGraph<double> graph(2);
    unsigned int new_node = graph.add_node(Word({0}));
    ASSERT_EQ(new_node, 2);
    ASSERT_EQ(graph.get_node_label(2), Word({0}));

    graph.add_edge(0, 1, 1.0, Word({0, 1}));
    graph.add_edge(1, 2, 2.0, Word({1, 1}));
    graph.add_edge(2, 0, 3.0, Word({1, 0}));

    ASSERT_TRUE(graph.edge_exists(0, 1));
    ASSERT_TRUE(graph.edge_exists(1, 2));
    ASSERT_TRUE(graph.edge_exists(2, 0));
    ASSERT_FALSE(graph.edge_exists(1, 0));

    ASSERT_EQ(graph.get_edge_weight(0, 1), 1.0);
    ASSERT_EQ(graph.get_edge_weight(1, 2), 2.0);
    ASSERT_EQ(graph.get_edge_weight(2, 0), 3.0);

    ASSERT_EQ(graph.get_edge_label(0, 1), Word({0, 1}));
    ASSERT_EQ(graph.get_edge_label(1, 2), Word({1, 1}));
    ASSERT_EQ(graph.get_edge_label(2, 0), Word({1, 0}));

    std::vector<std::vector<double>> expected_adjacency_matrix = {{0, 1, 0}, {0, 0, 2}, {3, 0, 0}};
    std::vector<std::vector<Word>> expected_label_matrix = {{ Word(), Word({0, 1}), Word()}, { Word(), Word(), Word({1, 1})}, {Word({1, 0}), Word(),Word()}};
    ASSERT_EQ(graph.get_adjacency_matrix(), expected_adjacency_matrix);
    ASSERT_EQ(graph.get_label_matrix(), expected_label_matrix);
}

TEST(MatrixGraph, EdgeModification) 
{
    MatrixGraph<double> graph(3);
    graph.add_edge(0, 1, 1.0, {0});
    graph.set_edge_weight(0, 1, 2.0);
    graph.set_edge_label(0, 1, {0, 1});

    ASSERT_EQ(graph.get_edge_weight(0, 1), 2.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), Word({0, 1}));

    graph.remove_edge(0, 1);
    ASSERT_FALSE(graph.edge_exists(0, 1));
    ASSERT_EQ(graph.get_edge_weight(0, 1), 0.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), Word());
}

TEST(AdjacencyListGraph, Constructor) 
{
    AdjacencyListGraph<double> graph;
    ASSERT_EQ(graph.size(), 0);
    ASSERT_TRUE(graph.empty());

    AdjacencyListGraph<double> graph2(3);
    ASSERT_EQ(graph2.size(), 3);
    ASSERT_FALSE(graph2.empty());
}

TEST(AdjacencyListGraph, VertexEdgeAdding) 
{
    AdjacencyListGraph<double> graph(2);
    unsigned int new_node = graph.add_node(Word({0}));
    ASSERT_EQ(new_node, 2);
    ASSERT_EQ(graph.get_node_label(2), Word({0}));

    graph.add_edge(0, 1, 1.0, Word({0, 1}));
    graph.add_edge(1, 2, 2.0, Word({1, 0}));
    graph.add_edge(2, 0, 3.0, Word({0, 0}));

    ASSERT_TRUE(graph.edge_exists(0, 1));
    ASSERT_TRUE(graph.edge_exists(1, 2));
    ASSERT_TRUE(graph.edge_exists(2, 0));
    ASSERT_FALSE(graph.edge_exists(1, 0));

    ASSERT_EQ(graph.get_edge_weight(0, 1), 1.0);
    ASSERT_EQ(graph.get_edge_weight(1, 2), 2.0);
    ASSERT_EQ(graph.get_edge_weight(2, 0), 3.0);

    ASSERT_EQ(graph.get_edge_label(0, 1), Word({0, 1}));
    ASSERT_EQ(graph.get_edge_label(1, 2), Word({1, 0}));
    ASSERT_EQ(graph.get_edge_label(2, 0), Word({0, 0}));

    auto edges = graph.edges();
    ASSERT_EQ(edges.size(), 3);
}

TEST(AdjacencyListGraph, EdgeModification) 
{
    AdjacencyListGraph<double> graph(3);
    graph.add_edge(0, 1, 1.0, Word({0}));
    graph.set_edge_weight(0, 1, 2.0);
    graph.set_edge_label(0, 1, Word({1}));

    ASSERT_EQ(graph.get_edge_weight(0, 1), 2.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), Word({1}));

    graph.remove_edge(0, 1);
    ASSERT_FALSE(graph.edge_exists(0, 1));
    ASSERT_EQ(graph.get_edge_weight(0, 1), 0.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), Word());
}

TEST(Graph, AbstractClassBehavior) 
{
    // Mock implementation of Graph to test abstract class behavior
    class MockGraph : public Graph<double> 
    {
    public:
        [[nodiscard]] unsigned int size() const override { return 0; }
        void add_edge(unsigned int, unsigned int, double, Word) override {}
        void remove_edge(unsigned int, unsigned int) override {}
        unsigned int add_node(Word) override { return 0; }
        [[nodiscard]] std::vector<Edge<double>> edges() const override { return {}; }
        [[nodiscard]] double get_edge_weight(unsigned int, unsigned int) const override { return 0.0; }
        [[nodiscard]] Word get_edge_label(unsigned int, unsigned int) const override { return {}; }
        void set_edge_label(unsigned int, unsigned int, Word) override {}
        void set_edge_weight(unsigned int, unsigned int, double) override {}
        [[nodiscard]] std::vector<unsigned int> neighbors(unsigned int) const override { return {}; }
    };

    MockGraph graph;
    ASSERT_TRUE(graph.empty());
    ASSERT_EQ(graph.size(), 0);
    ASSERT_FALSE(graph.edge_exists(0, 1));
}
