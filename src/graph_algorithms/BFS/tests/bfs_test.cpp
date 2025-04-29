#include "../../../test/main_test.h"
#include "../../wrapper_for_gtest/graph_algorithms_wrapper.h"

TEST(GraphAlgorithmsTest, BreadthFirstSearch) {
  GraphWrapper graph;
  graph.createGraph(5);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/test_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.breadthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2, 3, 4};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, BreadthFirstSearch_DisconnectedGraph) {
  GraphWrapper graph;
  graph.createGraph(6);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/disconnected_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.breadthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, BreadthFirstSearch_DisconnectedGraph2) {
  GraphWrapper graph;
  graph.createGraph(6);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/disconnected_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.breadthFirstSearch(graph, 3);
  std::vector<int> expected = {3, 4, 5};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, BreadthFirstSearch_CyclicGraph) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/cyclic_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.breadthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2, 3};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, BreadthFirstSearch_EmptyGraph) {
  GraphWrapper graph;
  graph.createGraph(0);

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.breadthFirstSearch(graph, 0);
  std::vector<int> expected = {};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, BreadthFirstSearch_InvalidStartVertex) {
  GraphWrapper graph;
  graph.createGraph(5);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/test_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.breadthFirstSearch(graph, 10);
  std::vector<int> expected = {};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, BreadthFirstSearch_SingleVertexGraph) {
  GraphWrapper graph;
  graph.createGraph(1);

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.breadthFirstSearch(graph, 0);
  std::vector<int> expected = {0};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, BreadthFirstSearch_LinearGraph) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/linear_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.breadthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2, 3};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, BreadthFirstSearch_TreeGraph) {
  GraphWrapper graph;
  graph.createGraph(7);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/tree_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.breadthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6};

  ASSERT_EQ(result, expected);
}

TEST(GraphAlgorithmsTest, BreadthFirstSearch_ComplexGraph) {
  GraphWrapper graph;
  graph.createGraph(6);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/complex_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  std::vector<int> result = algorithms.breadthFirstSearch(graph, 0);

  ASSERT_EQ((int)result.size(), 6);
  ASSERT_EQ((int)result[0], 0);
  std::set<int> unique_vertices(result.begin(), result.end());

  ASSERT_EQ((int)unique_vertices.size(), 6);
}
