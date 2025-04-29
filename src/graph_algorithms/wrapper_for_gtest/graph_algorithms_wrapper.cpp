#include "graph_algorithms_wrapper.h"

GraphAlgorithmsWrapper::~GraphAlgorithmsWrapper() {}

std::vector<int> GraphAlgorithmsWrapper::depthFirstSearch(GraphWrapper& graph,
                                                          int startVertex) {
  graph_t* c_graph = graph.getGraph();
  graph_traversal_result_t* result =
      traversal_result_create(c_graph->adjacency->size);
  depth_first_search(c_graph, startVertex, result);
  std::vector<int> traversalResult = traversalResultToVector(result);
  traversal_result_delete(result);
  return traversalResult;
}

std::vector<int> GraphAlgorithmsWrapper::breadthFirstSearch(GraphWrapper& graph,
                                                            int startVertex) {
  graph_t* raw_graph = graph.getGraph();
  graph_traversal_result_t* result =
      traversal_result_create(raw_graph->adjacency->size);

  breadth_first_search(raw_graph, startVertex, result);
  std::vector<int> bfs_result = traversalResultToVector(result);

  traversal_result_delete(result);
  return bfs_result;
}

std::vector<int> GraphAlgorithmsWrapper::traversalResultToVector(
    graph_traversal_result_t* result) {
  std::vector<int> traversalResult;
  if (result && result->visited_vertices) {
    for (int i = 0; i < result->size; ++i) {
      traversalResult.push_back(result->visited_vertices[i]);
    }
  }
  return traversalResult;
}

int GraphAlgorithmsWrapper::getShortestPathBetweenVertices(GraphWrapper& graph,
                                                           int vertex1,
                                                           int vertex2) {
  return get_shortest_path_between_vertices(graph.getGraph(), vertex1, vertex2);
}

std::vector<std::vector<int>>
GraphAlgorithmsWrapper::getShortestPathsBetweenAllVertices(
    GraphWrapper& graph) {
  graph_t* g = graph.getGraph();
  const int size = g->adjacency->size;
  int** dist = allocate_matrix(size);
  if (!dist) {
    return {};
  }
  std::vector<std::vector<int>> result;
  if (get_shortest_paths_between_all_vertices(g, dist) == 0) {
    for (int i = 0; i < size; ++i) {
      result.emplace_back(dist[i], dist[i] + size);
    }
  }
  free_matrix(dist, size);
  return result;
}

std::vector<std::vector<int>> GraphAlgorithmsWrapper::getLeastSpanningTree(
    GraphWrapper& graph) {
  graph_t* g = graph.getGraph();
  if (!g || !g->adjacency || g->adjacency->size == 0) {
    return {};
  }
  const int size = g->adjacency->size;
  int** mst = allocate_matrix(size);
  if (!mst) {
    return {};
  }
  std::vector<std::vector<int>> result;
  if (get_least_spanning_tree(g, mst) == 0) {  // 0 = success
    for (int i = 0; i < size; ++i) {
      result.emplace_back(mst[i], mst[i] + size);
    }
  }
  free_matrix(mst, size);
  return result;
}

GraphAlgorithmsWrapper::TsmResult
GraphAlgorithmsWrapper::solveTravelingSalesmanProblem(
    const GraphWrapper& graph) {
  graph_t* g = graph.getGraph();
  const aco_params_t params = {
      alpha_k_,       beta_k_,          initial_pheromone_k_, q_k_,
      evaporation_k_, min_pheromone_k_, max_iterations_k_};
  tsm_result_t* result = tsm_result_create();
  solve_traveling_salesman_problem(result, g, &params);
  TsmResult tsmResult;
  tsmResult.distance = result->distance;
  for (int i = 0; i < result->size; ++i) {
    tsmResult.vertices.push_back(result->vertices[i]);
  }
  tsm_result_delete(result);
  return tsmResult;
}

GraphAlgorithmsWrapper::TsmResult
GraphAlgorithmsWrapper::solveTravelingSalesmanProblem(const GraphWrapper& graph,
                                                      aco_params_t* params) {
  graph_t* g = graph.getGraph();
  tsm_result_t* result = tsm_result_create();
  solve_traveling_salesman_problem(result, g, params);
  TsmResult tsmResult;
  tsmResult.distance = result->distance;
  for (int i = 0; i < result->size; ++i) {
    tsmResult.vertices.push_back(result->vertices[i]);
  }
  tsm_result_delete(result);
  return tsmResult;
}

GraphAlgorithmsWrapper::TsmResult
GraphAlgorithmsWrapper::solveTravelingSalesmanProblem(
    const GraphWrapper& graph, double alpha_k, double beta_k,
    double initial_pheromone_k, double q_k, double evaporation_k,
    double min_pheromone_k, int max_iterations_k) {
  graph_t* g = graph.getGraph();
  aco_params_t params = {
      alpha_k,       beta_k,          initial_pheromone_k, q_k,
      evaporation_k, min_pheromone_k, max_iterations_k};
  tsm_result_t* result = tsm_result_create();
  solve_traveling_salesman_problem(result, g, &params);
  TsmResult tsmResult;
  tsmResult.distance = result->distance;
  for (int i = 0; i < result->size; ++i) {
    tsmResult.vertices.push_back(result->vertices[i]);
  }
  tsm_result_delete(result);
  return tsmResult;
}
