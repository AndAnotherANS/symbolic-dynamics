#include "Graph.hpp"
#include <gtest/gtest.h>

unsigned int int_max = std::numeric_limits<unsigned int>::max();

TEST(MatrixGraph, Constructor)
{
    MatrixGraph<> graph;
    ASSERT_EQ(graph.size(), 0);
    ASSERT_TRUE(graph.empty());

    MatrixGraph<> graph2(3);
    ASSERT_EQ(graph2.size(), 3);
    ASSERT_FALSE(graph2.empty());

    Eigen::MatrixXd expected_adjacency_matrix = Eigen::MatrixXd::Zero(3, 3);
    std::vector<std::vector<unsigned int>> expected_label_matrix = {
        {int_max, int_max, int_max}, {int_max, int_max, int_max}, {int_max, int_max, int_max}};
    ASSERT_EQ(graph2.get_adjacency_matrix(), expected_adjacency_matrix);
    ASSERT_EQ(graph2.get_label_matrix(), expected_label_matrix);
}

TEST(MatrixGraph, VertexEdgeAdding)
{
    MatrixGraph<> graph(2);
    unsigned int new_node = graph.add_node(Word({0}));
    ASSERT_EQ(new_node, 2);
    ASSERT_EQ(graph.get_node_label(2), Word({0}));

    graph.add_edge(0, 1, 1.0, 0);
    graph.add_edge(1, 2, 2.0, 0);
    graph.add_edge(2, 0, 3.0, 0);

    ASSERT_TRUE(graph.edge_exists(0, 1));
    ASSERT_TRUE(graph.edge_exists(1, 2));
    ASSERT_TRUE(graph.edge_exists(2, 0));
    ASSERT_FALSE(graph.edge_exists(1, 0));

    ASSERT_EQ(graph.get_edge_weight(0, 1), 1.0);
    ASSERT_EQ(graph.get_edge_weight(1, 2), 2.0);
    ASSERT_EQ(graph.get_edge_weight(2, 0), 3.0);

    ASSERT_EQ(graph.get_edge_label(0, 1), 0);
    ASSERT_EQ(graph.get_edge_label(1, 2), 0);
    ASSERT_EQ(graph.get_edge_label(2, 0), 0);

    Eigen::MatrixXd expected_adjacency_matrix = Eigen::MatrixXd::Zero(3, 3);
    expected_adjacency_matrix(0, 1) = 1;
    expected_adjacency_matrix(1, 2) = 2;
    expected_adjacency_matrix(2, 0) = 3;
    std::vector<std::vector<unsigned int>> expected_label_matrix = {
        {int_max, 0, int_max}, {int_max, int_max, 0}, {0, int_max, int_max}};
    ASSERT_EQ(graph.get_adjacency_matrix(), expected_adjacency_matrix);
    ASSERT_EQ(graph.get_label_matrix(), expected_label_matrix);
}

TEST(MatrixGraph, EdgeModification)
{
    MatrixGraph<> graph(3);
    graph.add_edge(0, 1, 1.0, 0);
    graph.set_edge_weight(0, 1, 2.0);
    graph.set_edge_label(0, 1, 2);

    ASSERT_EQ(graph.get_edge_weight(0, 1), 2.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), 2);

    graph.remove_edge(0, 1);
    ASSERT_FALSE(graph.edge_exists(0, 1));
    ASSERT_EQ(graph.get_edge_weight(0, 1), 0.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), int_max);
}

TEST(AdjacencyListGraph, Constructor)
{
    AdjacencyListGraph<> graph;
    ASSERT_EQ(graph.size(), 0);
    ASSERT_TRUE(graph.empty());

    AdjacencyListGraph<> graph2(3);
    ASSERT_EQ(graph2.size(), 3);
    ASSERT_FALSE(graph2.empty());
}

TEST(AdjacencyListGraph, VertexEdgeAdding)
{
    AdjacencyListGraph<> graph(2);
    unsigned int new_node = graph.add_node(Word({0}));
    ASSERT_EQ(new_node, 2);
    ASSERT_EQ(graph.get_node_label(2), Word({0}));

    graph.add_edge(0, 1, 1.0, 0);
    graph.add_edge(1, 2, 2.0, 0);
    graph.add_edge(2, 0, 3.0, 1);

    ASSERT_TRUE(graph.edge_exists(0, 1));
    ASSERT_TRUE(graph.edge_exists(1, 2));
    ASSERT_TRUE(graph.edge_exists(2, 0));
    ASSERT_FALSE(graph.edge_exists(1, 0));

    ASSERT_EQ(graph.get_edge_weight(0, 1), 1.0);
    ASSERT_EQ(graph.get_edge_weight(1, 2), 2.0);
    ASSERT_EQ(graph.get_edge_weight(2, 0), 3.0);

    ASSERT_EQ(graph.get_edge_label(0, 1), 0);
    ASSERT_EQ(graph.get_edge_label(1, 2), 0);
    ASSERT_EQ(graph.get_edge_label(2, 0), 1);

    auto edges = graph.edges();
    ASSERT_EQ(edges.size(), 3);
}

TEST(AdjacencyListGraph, EdgeModification)
{
    AdjacencyListGraph<> graph(3);
    graph.add_edge(0, 1, 1.0, 2);
    graph.set_edge_weight(0, 1, 2.0);
    graph.set_edge_label(0, 1, 1);

    ASSERT_EQ(graph.get_edge_weight(0, 1), 2.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), 1);

    graph.remove_edge(0, 1);
    ASSERT_FALSE(graph.edge_exists(0, 1));
    ASSERT_EQ(graph.get_edge_weight(0, 1), 0.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), int_max);
}

TEST(Graph, AbstractClassBehavior)
{
    // Mock implementation of Graph to test abstract class behavior
    class MockGraph : public Graph<>
    {
      public:
        [[nodiscard]] unsigned int size() const override
        {
            return 0;
        }
        void add_edge(unsigned int, unsigned int, double, unsigned int) override
        {
        }
        void remove_edge(unsigned int, unsigned int) override
        {
        }
        unsigned int add_node(Word) override
        {
            return 0;
        }
        [[nodiscard]] std::vector<Edge<>> edges() const override
        {
            return {};
        }
        [[nodiscard]] double get_edge_weight(unsigned int, unsigned int) const override
        {
            return 0.0;
        }
        [[nodiscard]] unsigned int get_edge_label(unsigned int, unsigned int) const override
        {
            return {};
        }
        void set_edge_label(unsigned int, unsigned int, unsigned int) override
        {
        }
        void set_edge_weight(unsigned int, unsigned int, double) override
        {
        }
        [[nodiscard]] std::vector<unsigned int> neighbors(unsigned int) const override
        {
            return {};
        }
    };

    MockGraph graph;
    ASSERT_TRUE(graph.empty());
    ASSERT_EQ(graph.size(), 0);
    ASSERT_FALSE(graph.edge_exists(0, 1));
}
