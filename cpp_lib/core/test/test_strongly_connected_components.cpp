#include <gtest/gtest.h>
#include "Graph.hpp"
#include "StronglyConnectedComponents.hpp"

TEST(StrongConnectedComponents, EmptyGraph) {
    MatrixGraph<int> graph;
    auto [scc, n] = strongly_connected_components(graph);
    ASSERT_EQ(n, 0);
    ASSERT_TRUE(scc.empty());
}

TEST(StrongConnectedComponents, SimpleLoop) {
    MatrixGraph<int> graph;
    graph.add_node();
    graph.add_edge(0, 0, 1, "");
    auto [scc, n] = strongly_connected_components(graph);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(scc[0], scc[1]);
}

TEST(StrongConnectedComponents, SingleEdge) {
    MatrixGraph<int> graph1;
    graph1.add_node();
    graph1.add_node();
    graph1.add_edge(0, 1, 1, "");
    auto [scc1, n1] = strongly_connected_components(graph1);
    ASSERT_EQ(n1, 2);
    ASSERT_NE(scc1[0], scc1[1]);

    MatrixGraph<int> graph2;
    graph2.add_node();
    graph2.add_node();
    graph2.add_edge(1, 0, 1, "");
    auto [scc2, n2] = strongly_connected_components(graph2);
    ASSERT_EQ(n2, 2);
    ASSERT_NE(scc2[0], scc2[1]);

    MatrixGraph<int> graph3;
    graph3.add_node();
    graph3.add_node();
    graph3.add_edge(0, 1, 1, "");
    graph3.add_edge(1, 0, 1, "");
    auto [scc3, n3] = strongly_connected_components(graph3);
    ASSERT_EQ(n3, 1);
    ASSERT_EQ(scc3[0], scc3[1]);
}

TEST(StrongConnectedComponents, Triangle) {
    MatrixGraph<int> graph;
    graph.add_node();
    graph.add_node();
    graph.add_node();
    graph.add_edge(0, 1, 1, "");
    graph.add_edge(1, 2, 1, "");
    graph.add_edge(2, 0, 1, "");
    auto [scc, n] = strongly_connected_components(graph);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(scc[0], scc[1]);
    ASSERT_EQ(scc[0], scc[2]);
}

TEST(StrongConnectedComponents, TwoTriangles) {
    MatrixGraph<int> graph;
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
    ASSERT_EQ(n, 2);
    ASSERT_EQ(scc[0], scc[1]);
    ASSERT_EQ(scc[0], scc[2]);
    ASSERT_EQ(scc[3], scc[4]);
    ASSERT_EQ(scc[3], scc[5]);
    ASSERT_NE(scc[0], scc[3]);
}


