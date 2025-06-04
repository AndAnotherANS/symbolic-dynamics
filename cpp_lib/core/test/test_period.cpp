#include <gtest/gtest.h>

#include "GraphAlgorithms.hpp"

TEST(Period, EmptyGraph) {
    MatrixGraph<int> graph;
    EXPECT_EQ(period<int>(graph), 0);
}

TEST(Period, SingleNode) {
    AdjacencyListGraph<int> graph;
    graph.add_node({});
    EXPECT_EQ(period(graph), 0);
    EXPECT_FALSE(is_aperiodic(graph));
    EXPECT_FALSE(is_primitive(graph));
}

TEST(Period, TwoNodes) {
    AdjacencyListGraph<int> graph;
    graph.add_node({});
    graph.add_node({});
    EXPECT_EQ(period(graph), 0);
    EXPECT_FALSE(is_aperiodic(graph));
    EXPECT_FALSE(is_primitive(graph));
}

TEST(Period, SimpleLoop) {
    AdjacencyListGraph<int> graph;
    graph.add_node({});
    graph.add_edge(0, 0, 1, {});
    EXPECT_EQ(period(graph), 1);
}

TEST(Period, TwoNodesOneEdge) {
    MatrixGraph<int> graph;
    graph.add_node({});
    graph.add_node({});
    graph.add_edge(0, 1, 1, {});
    EXPECT_EQ(period(graph), 0);
}

TEST(Period, TwoNodesTwoEdges) {
    MatrixGraph<int> graph;
    graph.add_node({});
    graph.add_node({});
    graph.add_edge(0, 1, 1, {});
    graph.add_edge(1, 0, 1, {});
    EXPECT_EQ(period(graph), 2);
}

TEST(Period, Triangle) {
    MatrixGraph<int> graph;
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_edge(0, 1, 1, {});
    graph.add_edge(1, 2, 1, {});
    graph.add_edge(2, 0, 1, {});
    EXPECT_EQ(period(graph), 3);
}

TEST(Period, TriangleSquare) {
    AdjacencyListGraph<int> graph;
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_edge(0, 1, 1, {});
    graph.add_edge(1, 2, 1, {});
    graph.add_edge(2, 0, 1, {});
    graph.add_edge(1, 3, 1, {});
    graph.add_edge(3, 4, 1, {});
    graph.add_edge(4, 2, 1, {});
    EXPECT_EQ(period(graph), 1);
}

TEST(Period, TriangleBridgeSquare) {
    AdjacencyListGraph<int> graph;
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_edge(0, 1, 1, {});
    graph.add_edge(1, 2, 1, {});
    graph.add_edge(2, 0, 1, {});
    graph.add_edge(0, 3, 1, {});
    graph.add_edge(3, 4, 1, {});
    graph.add_edge(4, 5, 1, {});
    graph.add_edge(5, 6, 1, {});
    graph.add_edge(6, 3, 1, {});
    EXPECT_EQ(period(graph), 1);
    EXPECT_TRUE(is_aperiodic(graph));
    EXPECT_FALSE(is_primitive(graph));
}

TEST(Period, SquareHexagon) {
    AdjacencyListGraph<int> graph;
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_node({});
    graph.add_edge(0, 1, 1, {});
    graph.add_edge(1, 2, 1, {});
    graph.add_edge(2, 3, 1, {});
    graph.add_edge(3, 0, 1, {});
    graph.add_edge(3, 4, 1, {});
    graph.add_edge(4, 5, 1, {});
    graph.add_edge(5, 6, 1, {});
    graph.add_edge(6, 7, 1, {});
    graph.add_edge(7, 2, 1, {});
    EXPECT_EQ(period(graph), 2);
}
