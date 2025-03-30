#include <gtest/gtest.h>

#include "Graph.hpp"
#include "StronglyConnectedComponents.hpp"

TEST(StronglyConnectedComponents, EmptyGraph) {
    MatrixGraph<int> graph;
    auto [scc, n] = strongly_connected_components(graph);
    EXPECT_EQ(n, 0);
    EXPECT_TRUE(scc.empty());
}

TEST(StronglyConnectedComponents, SimpleLoop) {
    AdjacencyListGraph<int> graph;
    graph.add_node();
    graph.add_edge(0, 0, 1, "");
    auto [scc, n] = strongly_connected_components(graph);
    EXPECT_EQ(n, 1);
}

TEST(StronglyConnectedComponents, SingleEdge) {
    MatrixGraph<int> graph1;
    graph1.add_node();
    graph1.add_node();
    graph1.add_edge(0, 1, 1, "");
    auto [scc1, n1] = strongly_connected_components(graph1);
    EXPECT_EQ(n1, 2);
    EXPECT_NE(scc1.at(0), scc1.at(1));

    MatrixGraph<int> graph2;
    graph2.add_node();
    graph2.add_node();
    graph2.add_edge(1, 0, 1, "");
    auto [scc2, n2] = strongly_connected_components(graph2);
    EXPECT_EQ(n2, 2);
    EXPECT_NE(scc2.at(0), scc2.at(1));

    AdjacencyListGraph<int> graph3;
    graph3.add_node();
    graph3.add_node();
    graph3.add_edge(0, 1, 1, "");
    graph3.add_edge(1, 0, 1, "");
    auto [scc3, n3] = strongly_connected_components(graph3);
    EXPECT_EQ(n3, 1);
    EXPECT_EQ(scc3.at(0), scc3.at(1));
}

TEST(StronglyConnectedComponents, Triangle) {
    MatrixGraph<int> graph;
    graph.add_node();
    graph.add_node();
    graph.add_node();
    graph.add_edge(0, 1, 1, "");
    graph.add_edge(1, 2, 1, "");
    graph.add_edge(2, 0, 1, "");
    auto [scc, n] = strongly_connected_components(graph);
    EXPECT_EQ(n, 1);
    EXPECT_EQ(scc.at(0), scc.at(1));
    EXPECT_EQ(scc.at(0), scc.at(2));
}

TEST(StronglyConnectedComponents, TwoTriangles) {
    AdjacencyListGraph<int> graph;
    graph.add_node();
    graph.add_node();
    graph.add_node();
    graph.add_node();
    graph.add_node();
    graph.add_node();
    graph.add_edge(0, 1, 1, "");
    graph.add_edge(1, 2, 1, "");
    graph.add_edge(2, 0, 1, "");
    graph.add_edge(3, 4, 1, "");
    graph.add_edge(4, 5, 1, "");
    graph.add_edge(5, 3, 1, "");
    graph.add_edge(0, 3, 1, "");
    graph.add_edge(1, 4, 1, "");
    auto [scc, n] = strongly_connected_components(graph);
    EXPECT_EQ(n, 2);
    EXPECT_EQ(scc.at(0), scc.at(1));
    EXPECT_EQ(scc.at(0), scc.at(2));
    EXPECT_EQ(scc.at(3), scc.at(4));
    EXPECT_EQ(scc.at(3), scc.at(5));
    EXPECT_NE(scc.at(0), scc.at(3));
}
