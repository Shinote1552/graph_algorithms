#include "../../../test/main_test.h"
#include "../../wrapper_for_gtest/graph_algorithms_wrapper.h"

TEST(GraphAlgorithmsTest, DepthFirstSearch) {
  GraphWrapper graph;
  graph.createGraph(5);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/test_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.depthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 3, 2, 4};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, DepthFirstSearch_DisconnectedGraph) {
  GraphWrapper graph;
  graph.createGraph(6);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/disconnected_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.depthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2};

  ASSERT_EQ(result, expected);
}
TEST(GraphAlgorithmsTest, DepthFirstSearch_DisconnectedGraph2) {
  GraphWrapper graph;
  graph.createGraph(6);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/disconnected_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.depthFirstSearch(graph, 3);
  std::vector<int> expected = {3, 4, 5};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, DepthFirstSearch_CyclicGraph) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/cyclic_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.depthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2, 3};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, DepthFirstSearch_EmptyGraph) {
  GraphWrapper graph;
  graph.createGraph(0);

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.depthFirstSearch(graph, 0);
  std::vector<int> expected = {};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, DepthFirstSearch_InvalidStartVertex) {
  GraphWrapper graph;
  graph.createGraph(5);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/test_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.depthFirstSearch(graph, 10);
  std::vector<int> expected = {};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, DepthFirstSearch_SingleVertexGraph) {
  GraphWrapper graph;
  graph.createGraph(1);

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.depthFirstSearch(graph, 0);
  std::vector<int> expected = {0};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, DepthFirstSearch_LinearGraph) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/linear_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.depthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2, 3};

  ASSERT_EQ(result, expected);
}
