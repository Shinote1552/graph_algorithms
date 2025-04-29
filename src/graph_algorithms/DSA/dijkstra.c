#include "../s21_graph_algorithms.h"

static int validate_input(graph_t* graph, int vertex1, int vertex2) {
  if (!graph || !graph->adjacency || !graph->adjacency->data || vertex1 < 0 ||
      vertex1 >= graph->adjacency->size || vertex2 < 0 ||
      vertex2 >= graph->adjacency->size) {
    return -1;
  }
  if (vertex1 == vertex2) return 0;
  return 1;
}

static void initialize_arrays(int vertex_count, int** dist, int** visited) {
  *dist = (int*)malloc(vertex_count * sizeof(int));
  *visited = (int*)calloc(vertex_count, sizeof(int));
  for (int i = 0; i < vertex_count; i++) {
    (*dist)[i] = INT_MAX;
  }
}

static int find_min_distance_vertex(int vertex_count, const int* dist,
                                    const int* visited) {
  int min_dist = INT_MAX;
  int min_index = -1;
  for (int v = 0; v < vertex_count; v++) {
    if (!visited[v] && dist[v] < min_dist) {
      min_dist = dist[v];
      min_index = v;
    }
  }
  return min_index;
}

static void update_neighbor_distances(graph_t* graph, int u, int* dist,
                                      int* visited) {
  for (int v = 0; v < graph->adjacency->size; v++) {
    const int edge_weight = graph->adjacency->data[u][v];
    if (!visited[v] && edge_weight > 0 && dist[u] != INT_MAX) {
      const int new_dist = dist[u] + edge_weight;
      if (new_dist < dist[v]) {
        dist[v] = new_dist;
      }
    }
  }
}

/**
 * Dijkstra’s algorith, only with positive edges of the graph
 * @brief finds the shortest path between two vertices(from first to all others)
 * @param graph graph structure pointer
 * @return shortest path length (v1 x v2) or -1 if error
 */
int get_shortest_path_between_vertices(graph_t* graph, int vertex1,
                                       int vertex2) {
  int validation = validate_input(graph, vertex1, vertex2);
  if (validation != 1) return validation;
  const int vertex_count = graph->adjacency->size;
  int *dist, *visited;
  initialize_arrays(vertex_count, &dist, &visited);
  dist[vertex1] = 0;
  for (int i = 0; i < vertex_count - 1; i++) {
    int u = find_min_distance_vertex(vertex_count, dist, visited);
    if (u == -1 || dist[u] == INT_MAX || u == vertex2) break;

    visited[u] = 1;
    update_neighbor_distances(graph, u, dist, visited);
  }
  const int result = (dist[vertex2] == INT_MAX) ? -1 : dist[vertex2];
  free(dist);
  free(visited);
  return result;
}
