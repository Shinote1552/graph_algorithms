#include "../../../test/main_test.h"
#include "../../wrapper_for_gtest/graph_algorithms_wrapper.h"

TEST(GraphAlgorithmsTestDijkstraTest, ShortestPathBetweenVertices_SimpleGraph) {
  GraphWrapper graph;
  graph.createGraph(3);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/weighted_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  int distance = 0;
  distance = algorithms.getShortestPathBetweenVertices(graph, 0, 2);

  ASSERT_EQ(distance, 3);
}

TEST(GraphAlgorithmsTest, ShortestPathBetweenVertices_NoPath) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/disconnected_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  int distance = 0;
  distance = algorithms.getShortestPathBetweenVertices(graph, 0, 3);

  ASSERT_EQ(distance, -1);
}

TEST(GraphAlgorithmsTest, ShortestPathBetweenVertices_SameVertex) {
  GraphWrapper graph;
  graph.createGraph(3);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/weighted_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  int distance = 9999999;
  distance = algorithms.getShortestPathBetweenVertices(graph, 1, 1);

  ASSERT_EQ(distance, 0);
}

TEST(GraphAlgorithmsTest, ShortestPathBetweenVertices_InvalidVertices) {
  GraphWrapper graph;
  graph.createGraph(3);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/weighted_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  int distance1 = 0;
  int distance2 = 0;
  distance1 = algorithms.getShortestPathBetweenVertices(graph, -1, 2);
  distance2 = algorithms.getShortestPathBetweenVertices(graph, 0, 5);

  ASSERT_EQ(distance1, -1);
  ASSERT_EQ(distance2, -1);
}
TEST(GraphAlgorithmsTest, ShortestPathBetweenVertices_WithNegativeVertices) {
  GraphWrapper graph;
  graph.createGraph(3);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/"
      "weighted_graph_with_negative_vertices.txt");

  GraphAlgorithmsWrapper algorithms;
  int distance1 = 0;
  int distance2 = 0;
  distance1 = algorithms.getShortestPathBetweenVertices(graph, 0, 1);
  distance2 = algorithms.getShortestPathBetweenVertices(graph, 0, 5);

  ASSERT_EQ(distance1, 1);
  ASSERT_EQ(distance2, -1);
}

TEST(GraphAlgorithmsTest, AboveDescribedGraphExamples) {
  GraphWrapper graph;
  graph.createGraph(11);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/graph_examples.txt");

  GraphAlgorithmsWrapper algorithms;
  int distance1 = 0;
  distance1 = algorithms.getShortestPathBetweenVertices(graph, 0, 10);

  ASSERT_EQ(distance1, 18);
}
