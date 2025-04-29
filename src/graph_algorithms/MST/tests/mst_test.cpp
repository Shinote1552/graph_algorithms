#include "../../../test/main_test.h"
#include "../../wrapper_for_gtest/graph_algorithms_wrapper.h"

TEST(PrimAlgorithmTest, BasicGraph) {
  GraphWrapper graph;
  graph.createGraph(5);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/prim_basic.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.getLeastSpanningTree(graph);

  ASSERT_EQ((int)result[0][1], 2);
  ASSERT_EQ((int)result[1][0], 2);
  ASSERT_EQ((int)result[0][3], 6);
  ASSERT_EQ((int)result[3][0], 6);
  ASSERT_EQ((int)result[1][2], 3);
  ASSERT_EQ((int)result[2][1], 3);
  ASSERT_EQ((int)result[1][4], 5);
  ASSERT_EQ((int)result[4][1], 5);
  ASSERT_EQ((int)result[0][2], 0);
  ASSERT_EQ((int)result[0][4], 0);
  ASSERT_EQ((int)result[2][3], 0);
  ASSERT_EQ((int)result[2][4], 0);
  ASSERT_EQ((int)result[3][4], 0);
}

TEST(PrimAlgorithmTest, SingleVertexGraph) {
  GraphWrapper graph;
  graph.createGraph(1);

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.getLeastSpanningTree(graph);

  ASSERT_EQ((int)result.size(), 1);
  ASSERT_EQ((int)result[0][0], 0);
}

TEST(PrimAlgorithmTest, DisconnectedGraph) {
  GraphWrapper graph;
  graph.createGraph(6);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/disconnected_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.getLeastSpanningTree(graph);

  ASSERT_TRUE(result.empty());
}

TEST(PrimAlgorithmTest, AllEdgesEqualWeight) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/prim_equal_weights.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.getLeastSpanningTree(graph);

  int edge_count = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      if (result[i][j] == 1) edge_count++;
    }
  }

  ASSERT_EQ((int)edge_count, 3);
}

TEST(PrimAlgorithmTest, ComplexGraph) {
  GraphWrapper graph;
  graph.createGraph(6);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/prim_complex.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.getLeastSpanningTree(graph);

  int edge_count = 0;
  int total_weight = 0;
  for (int i = 0; i < 6; ++i) {
    for (int j = i + 1; j < 6; ++j) {
      if (result[i][j] > 0) {
        edge_count++;
        total_weight += result[i][j];
      }
    }
  }

  ASSERT_EQ((int)edge_count, 5);
  ASSERT_EQ((int)total_weight, 16);
  ASSERT_EQ((int)result[0][1], 3);
  ASSERT_EQ((int)result[1][2], 4);
  ASSERT_EQ((int)result[2][3], 2);
  ASSERT_EQ((int)result[3][4], 2);
  ASSERT_EQ((int)result[4][5], 5);
}

TEST(PrimAlgorithmTest, EmptyGraph) {
  GraphWrapper graph;
  graph.createGraph(0);

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.getLeastSpanningTree(graph);

  ASSERT_TRUE(result.empty());
}

TEST(PrimAlgorithmTest, NegativeWeights) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/prim_negative_weights.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.getLeastSpanningTree(graph);

  ASSERT_EQ((int)result[0][1], -5);
  ASSERT_EQ((int)result[1][2], -3);
  ASSERT_EQ((int)result[1][3], 2);
  ASSERT_EQ((int)result[0][2], 0);
  ASSERT_EQ((int)result[0][3], 0);
  ASSERT_EQ((int)result[2][3], 0);
  ASSERT_EQ(0, 0);
}
