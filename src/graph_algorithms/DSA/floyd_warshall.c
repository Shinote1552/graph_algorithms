#include "../s21_graph_algorithms.h"

static int validate_input(graph_t* graph, int*** dist) {
  if (!graph || !graph->adjacency || !graph->adjacency->data || !(*dist)) {
    return 1;
  }
  return 0;
}

static void initialize_distance_matrix(graph_t* graph, int** dist) {
  const int vertex_count = graph->adjacency->size;
  for (int i = 0; i < vertex_count; i++) {
    for (int j = 0; j < vertex_count; j++) {
      if (i == j) {
        dist[i][j] = 0;
      } else if (graph->adjacency->data[i][j] != 0) {
        dist[i][j] = graph->adjacency->data[i][j];
      } else {
        dist[i][j] = INT_MAX;
      }
    }
  }
}

static void try_update_distance(int** dist, int i, int j, int k) {
  if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
    int new_dist = dist[i][k] + dist[k][j];
    if (dist[i][j] > new_dist) {
      dist[i][j] = new_dist;
    }
  }
}

static void floyd_warshall_algorithm(int vertex_count, int** dist) {
  for (int k = 0; k < vertex_count; k++) {
    for (int i = 0; i < vertex_count; i++) {
      for (int j = 0; j < vertex_count; j++) {
        try_update_distance(dist, i, j, k);
      }
    }
  }
}

/**
 * @brief finds the shortest paths between all pairs of vertices in the graph
 * @param graph graph structure pointer
 * @param dist matrix of shortest paths, dist = NULL if error
 * @return 0 = success or 1 = error
 */
int get_shortest_paths_between_all_vertices(graph_t* graph, int** dist) {
  if (validate_input(graph, &dist) != 0) {
    return 1;
  }
  const int vertex_count = graph->adjacency->size;
  initialize_distance_matrix(graph, dist);
  floyd_warshall_algorithm(vertex_count, dist);
  return 0;
}
