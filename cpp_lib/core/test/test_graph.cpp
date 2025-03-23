#include <gtest/gtest.h>
#include "Graph.hpp"

TEST(MatrixGraph, Constructor) 
{
    MatrixGraph<float> graph; 
    ASSERT_EQ(graph.get_adjacency_matrix().size(), 0);
    ASSERT_EQ(graph.get_label_matrix().size(), 0);   
    
    MatrixGraph<float> graph2(3);
    std::vector<std::vector<float>> expected_adjacency_matrix = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    std::vector<std::vector<std::string>> expected_label_matrix = {{ "", "", ""}, { "", "", ""}, { "", "", ""}};
    ASSERT_EQ(graph2.get_adjacency_matrix(), expected_adjacency_matrix);
    ASSERT_EQ(graph2.get_label_matrix(), expected_label_matrix);

    MatrixGraph<float> graph3(expected_adjacency_matrix, expected_label_matrix);
    ASSERT_EQ(graph3.get_adjacency_matrix(), expected_adjacency_matrix);
    ASSERT_EQ(graph3.get_label_matrix(), expected_label_matrix);

}

TEST(MatrixGraph, VertexEdgeAdding) 
{
    MatrixGraph<float> graph(2);
    graph.add_node();
    graph.add_edge(0, 1, 1.0, "a");
    graph.add_edge(1, 2, 2.0, "b");
    graph.add_edge(2, 0, 3.0, "c");
    std::vector<std::vector<float>> expected_adjacency_matrix = {{0, 1, 0}, {0, 0, 2}, {3, 0, 0}};
    std::vector<std::vector<std::string>> expected_label_matrix = {{ "", "a", ""}, { "", "", "b"}, {"c", "", ""}};
    ASSERT_EQ(graph.get_adjacency_matrix(), expected_adjacency_matrix);
    ASSERT_EQ(graph.get_label_matrix(), expected_label_matrix);
}
