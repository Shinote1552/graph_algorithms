#ifndef GRAPH_ALGORITHMS_WRAPPER_H
#define GRAPH_ALGORITHMS_WRAPPER_H

#include <climits>
#include <string>
#include <vector>

#include "../../graph/tests/wrapper_for_gtest/graph_wrapper.h"
#include "../s21_graph_algorithms.h"

/**
 * @brief Class for testing/using graph algorithms in c++ with c realization
 */
class GraphAlgorithmsWrapper {
 public:
  /**
   * @brief result of traveling salesman problem
   * @param vertices array of vertices
   * @param distance distance of path
   */
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
    bool operator==(const TsmResult& other) const {
      return distance == other.distance && vertices == other.vertices;
    }
  };

 public:
  GraphAlgorithmsWrapper() = default;
  ~GraphAlgorithmsWrapper();

  std::vector<int> depthFirstSearch(GraphWrapper& graph, int startVertex);
  std::vector<int> breadthFirstSearch(GraphWrapper& graph, int startVertex);
  int getShortestPathBetweenVertices(GraphWrapper& graph, int vertex1,
                                     int vertex2);
  std::vector<std::vector<int>> getShortestPathsBetweenAllVertices(
      GraphWrapper& graph);
  std::vector<std::vector<int>> getLeastSpanningTree(GraphWrapper& graph);
  TsmResult solveTravelingSalesmanProblem(const GraphWrapper& graph);
  TsmResult solveTravelingSalesmanProblem(const GraphWrapper& graph,
                                          aco_params_t* params);
  TsmResult solveTravelingSalesmanProblem(const GraphWrapper& graph,
                                          double alpha_k, double beta_k,
                                          double initial_pheromone_k,
                                          double q_k, double evaporation_k,
                                          double min_pheromone_k,
                                          int max_iterations);

 private:
  std::vector<int> traversalResultToVector(graph_traversal_result_t* result);
  static constexpr double alpha_k_ = 1.0;
  static constexpr double beta_k_ = 2.0;
  static constexpr double initial_pheromone_k_ = 1.0;
  static constexpr double q_k_ = 100.0;
  static constexpr double evaporation_k_ = 0.5;
  static constexpr double min_pheromone_k_ = 0.01;
  static constexpr int max_iterations_k_ = 1000;
};

#endif  // GRAPH_ALGORITHMS_WRAPPER_H
