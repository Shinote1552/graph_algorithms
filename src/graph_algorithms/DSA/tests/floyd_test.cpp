#include "../../../test/main_test.h"
#include "../../wrapper_for_gtest/graph_algorithms_wrapper.h"

TEST(FloydWarshallTest, FloydLargeGraph) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/floyd_basic.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.getShortestPathsBetweenAllVertices(graph);

  ASSERT_EQ(result[0][0], 0);
  ASSERT_EQ(result[1][1], 0);
  ASSERT_EQ(result[2][2], 0);
  ASSERT_EQ(result[3][3], 0);
  ASSERT_EQ(result[0][3], 8);
  ASSERT_EQ(result[0][2], 3);
  ASSERT_EQ(result[3][0], -8);
  ASSERT_EQ(result[2][0], -3);
}

TEST(FloydWarshallTest, FloydNegativeWeights) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/floyd_negative_weights.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.getShortestPathsBetweenAllVertices(graph);

  ASSERT_EQ(result[0][1], -4);
}

TEST(FloydWarshallTest, FloydComplexCase) {
  GraphWrapper graph;
  graph.createGraph(5);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/floyd_complex_case.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.getShortestPathsBetweenAllVertices(graph);

  ASSERT_EQ(result[0][1], 3);
  ASSERT_EQ(result[0][3], 2);
  ASSERT_EQ(result[0][4], 6);
  ASSERT_EQ(result[4][0], 2);
  ASSERT_EQ(result[2][4], 2);
}
