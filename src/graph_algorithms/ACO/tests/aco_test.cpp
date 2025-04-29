#include <cmath>

#include "../../../test/main_test.h"
#include "../../wrapper_for_gtest/graph_algorithms_wrapper.h"

TEST(TravelingSalesmanProblemTest, SingleVertexGraph) {
  GraphWrapper graph;
  graph.createGraph(1);
  graph.getGraph()->adjacency->data[0][0] = 0;

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph);

  ASSERT_EQ((double)result.distance, 0.0);
  ASSERT_EQ((int)result.vertices.size(), 2);
  ASSERT_EQ((int)result.vertices[0], 0);
  ASSERT_EQ((int)result.vertices[1], 0);
}

TEST(TravelingSalesmanProblemTest, TwoByTwoGraph) {
  GraphWrapper graph;
  graph.createGraph(2);
  graph.getGraph()->adjacency->data[0][1] = 5;
  graph.getGraph()->adjacency->data[1][0] = 5;
  graph.getGraph()->adjacency->data[0][0] = 0;
  graph.getGraph()->adjacency->data[1][1] = 0;

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph);

  ASSERT_NEAR((double)result.distance, 10.0, 1e-5);
}

TEST(TravelingSalesmanProblemTest, BasicGraph) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/tsp_basic.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph);

  ASSERT_NEAR((double)result.distance, 10.0, 1e-5);
  ASSERT_EQ((int)result.vertices.size(), 5);
  ASSERT_EQ((int)result.vertices[0], (int)result.vertices.back());
}

TEST(TravelingSalesmanProblemTest, DisconnectedGraph) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/tsp_disconnected_graph.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph);

  ASSERT_EQ(result.distance, std::numeric_limits<double>::infinity());
  ASSERT_TRUE(result.vertices.empty());
}

TEST(TravelingSalesmanProblemTest, ThreeVerticesCompleteGraph) {
  GraphWrapper graph;
  graph.createGraph(3);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/tsp_three_vertices.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph);

  ASSERT_NEAR((double)result.distance, 6.0, 1e-5);
  ASSERT_EQ((int)result.vertices.size(), 4);
  ASSERT_EQ(result.vertices[0], result.vertices.back());
}

TEST(TravelingSalesmanProblemTest, AsymmetricGraph) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/tsp_asymmetric.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph);

  ASSERT_GT((double)result.distance, 0.0);
  ASSERT_EQ((int)result.vertices.size(), 5);
  ASSERT_EQ(result.vertices[0], result.vertices.back());
}

TEST(TravelingSalesmanProblemTest, EmptyGraph) {
  GraphWrapper graph;
  graph.createGraph(0);

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph);

  ASSERT_EQ(result.distance, std::numeric_limits<double>::infinity());
  ASSERT_TRUE(result.vertices.empty());
}

TEST(TravelingSalesmanProblemTest, WithCustomACOParameters) {
  GraphWrapper graph;
  graph.createGraph(5);
  graph.loadGraphFromFile("../datasets/incidence_matrix_src/tsp_complex.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph, 1.0, 2.0, 1.0,
                                                         100.0, 0.5, 0.01, 100);

  ASSERT_GT(result.distance, 0.0);
  ASSERT_EQ((int)result.vertices.size(), 6);
  ASSERT_EQ(result.vertices[0], result.vertices.back());
}

TEST(TravelingSalesmanProblemTest, SmallKnownCase) {
  GraphWrapper graph;
  graph.createGraph(3);
  graph.getGraph()->adjacency->data[0][0] = 0;
  graph.getGraph()->adjacency->data[0][1] = 1;
  graph.getGraph()->adjacency->data[0][2] = 10;
  graph.getGraph()->adjacency->data[1][0] = 10;
  graph.getGraph()->adjacency->data[1][1] = 0;
  graph.getGraph()->adjacency->data[1][2] = 2;
  graph.getGraph()->adjacency->data[2][0] = 3;
  graph.getGraph()->adjacency->data[2][1] = 10;
  graph.getGraph()->adjacency->data[2][2] = 0;

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph);

  ASSERT_EQ(result.distance, 6.0);
  ASSERT_EQ((int)result.vertices.size(), 4);
  ASSERT_EQ(result.vertices[0], result.vertices[3]);

  std::set<int> visited(result.vertices.begin(), result.vertices.end());
  ASSERT_EQ((int)visited.size(), 3);

  double calculated_distance = 0.0;
  for (size_t i = 0; i < result.vertices.size() - 1; ++i) {
    int from = result.vertices[i];
    int to = result.vertices[i + 1];
    calculated_distance += graph.getGraph()->adjacency->data[from][to];
  }

  ASSERT_EQ(calculated_distance, result.distance);
}

TEST(TravelingSalesmanProblemTest, CompareWithKnownOptimal) {
  GraphWrapper graph;
  graph.createGraph(4);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/tsp_known_optimal.txt");

  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph);

  ASSERT_NEAR(result.distance, 38.0, 5.0);
  ASSERT_EQ((int)result.vertices.size(), 5);
  ASSERT_EQ(result.vertices[0], result.vertices.back());
}

TEST(GraphAlgorithmsTest, solveTravelingSalesmanProblemgraph_examples) {
  GraphWrapper graph;
  graph.createGraph(11);
  graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/graph_examples.txt");
  GraphAlgorithmsWrapper algorithms;
  auto result = algorithms.solveTravelingSalesmanProblem(graph);
  ASSERT_NEAR(result.distance, 253.0, 10.0);
}
