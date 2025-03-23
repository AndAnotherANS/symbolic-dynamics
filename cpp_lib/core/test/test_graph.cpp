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
    std::vector<std::vector<std::string>> expected_label_matrix = {{ "", "", ""}, { "", "", ""}, { "", "", ""}};
    ASSERT_EQ(graph2.get_adjacency_matrix(), expected_adjacency_matrix);
    ASSERT_EQ(graph2.get_label_matrix(), expected_label_matrix);
}

TEST(MatrixGraph, VertexEdgeAdding) 
{
    MatrixGraph<double> graph(2);
    int new_node = graph.add_node("Node2");
    ASSERT_EQ(new_node, 2);
    ASSERT_EQ(graph.get_node_label(2), "Node2");

    graph.add_edge(0, 1, 1.0, "a");
    graph.add_edge(1, 2, 2.0, "b");
    graph.add_edge(2, 0, 3.0, "c");

    ASSERT_TRUE(graph.edge_exists(0, 1));
    ASSERT_TRUE(graph.edge_exists(1, 2));
    ASSERT_TRUE(graph.edge_exists(2, 0));
    ASSERT_FALSE(graph.edge_exists(1, 0));

    ASSERT_EQ(graph.get_edge_weight(0, 1), 1.0);
    ASSERT_EQ(graph.get_edge_weight(1, 2), 2.0);
    ASSERT_EQ(graph.get_edge_weight(2, 0), 3.0);

    ASSERT_EQ(graph.get_edge_label(0, 1), "a");
    ASSERT_EQ(graph.get_edge_label(1, 2), "b");
    ASSERT_EQ(graph.get_edge_label(2, 0), "c");

    std::vector<std::vector<double>> expected_adjacency_matrix = {{0, 1, 0}, {0, 0, 2}, {3, 0, 0}};
    std::vector<std::vector<std::string>> expected_label_matrix = {{ "", "a", ""}, { "", "", "b"}, {"c", "", ""}};
    ASSERT_EQ(graph.get_adjacency_matrix(), expected_adjacency_matrix);
    ASSERT_EQ(graph.get_label_matrix(), expected_label_matrix);
}

TEST(MatrixGraph, EdgeModification) 
{
    MatrixGraph<double> graph(3);
    graph.add_edge(0, 1, 1.0, "a");
    graph.set_edge_weight(0, 1, 2.0);
    graph.set_edge_label(0, 1, "updated");

    ASSERT_EQ(graph.get_edge_weight(0, 1), 2.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), "updated");

    graph.remove_edge(0, 1);
    ASSERT_FALSE(graph.edge_exists(0, 1));
    ASSERT_EQ(graph.get_edge_weight(0, 1), 0.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), "");
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
    int new_node = graph.add_node("Node2");
    ASSERT_EQ(new_node, 2);
    ASSERT_EQ(graph.get_node_label(2), "Node2");

    graph.add_edge(0, 1, 1.0, "a");
    graph.add_edge(1, 2, 2.0, "b");
    graph.add_edge(2, 0, 3.0, "c");

    ASSERT_TRUE(graph.edge_exists(0, 1));
    ASSERT_TRUE(graph.edge_exists(1, 2));
    ASSERT_TRUE(graph.edge_exists(2, 0));
    ASSERT_FALSE(graph.edge_exists(1, 0));

    ASSERT_EQ(graph.get_edge_weight(0, 1), 1.0);
    ASSERT_EQ(graph.get_edge_weight(1, 2), 2.0);
    ASSERT_EQ(graph.get_edge_weight(2, 0), 3.0);

    ASSERT_EQ(graph.get_edge_label(0, 1), "a");
    ASSERT_EQ(graph.get_edge_label(1, 2), "b");
    ASSERT_EQ(graph.get_edge_label(2, 0), "c");

    auto edges = graph.edges();
    ASSERT_EQ(edges.size(), 3);
}

TEST(AdjacencyListGraph, EdgeModification) 
{
    AdjacencyListGraph<double> graph(3);
    graph.add_edge(0, 1, 1.0, "a");
    graph.set_edge_weight(0, 1, 2.0);
    graph.set_edge_label(0, 1, "updated");

    ASSERT_EQ(graph.get_edge_weight(0, 1), 2.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), "updated");

    graph.remove_edge(0, 1);
    ASSERT_FALSE(graph.edge_exists(0, 1));
    ASSERT_EQ(graph.get_edge_weight(0, 1), 0.0);
    ASSERT_EQ(graph.get_edge_label(0, 1), "");
}

TEST(Graph, AbstractClassBehavior) 
{
    // Mock implementation of Graph to test abstract class behavior
    class MockGraph : public Graph<double> 
    {
    public:
        int size() const override { return 0; }
        void add_edge(const int, const int, double, std::string) override {}
        void remove_edge(const int, const int) override {}
        int add_node(std::string) override { return 0; }
        std::vector<Edge<double>> edges() const override { return {}; }
        double get_edge_weight(int, int) const override { return 0.0; }
        std::string get_edge_label(int, int) const override { return ""; }
        void set_edge_label(int, int, std::string) override {}
        void set_edge_weight(int, int, double) override {}
        std::vector<int> neighbors(int) const override { return {}; }
    };

    MockGraph graph;
    ASSERT_TRUE(graph.empty());
    ASSERT_EQ(graph.size(), 0);
    ASSERT_FALSE(graph.edge_exists(0, 1));
}
