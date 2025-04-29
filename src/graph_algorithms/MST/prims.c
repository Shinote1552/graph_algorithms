#include "../s21_graph_algorithms.h"

static int validate_mst_input(graph_t* graph, int** mst) {
  if (!graph || !graph->adjacency || !graph->adjacency->data || !mst) {
    return 1;
  }
  return graph->adjacency->size <= 0 ? 1 : 0;
}

static void init_mst_matrix(int** mst, int vertex_count) {
  for (int i = 0; i < vertex_count; i++) {
    for (int j = 0; j < vertex_count; j++) {
      mst[i][j] = 0;
    }
  }
}

static void find_min_edge(graph_t* graph, const int* visited, int vertex_count,
                          int* min_weight, int* src, int* dest) {
  *min_weight = INT_MAX;
  *src = -1;
  *dest = -1;
  for (int i = 0; i < vertex_count; i++) {
    if (visited[i]) {
      for (int j = 0; j < vertex_count; j++) {
        int weight = graph->adjacency->data[i][j];
        if (!visited[j] && weight != 0 && weight < *min_weight) {
          *min_weight = weight;
          *src = i;
          *dest = j;
        }
      }
    }
  }
}

/**
 * Minimum Spanning Tree (Prim's algorithm)
 * @brief finds the minimum spanning tree of a graph
 * @param graph structure of the graph pointer
 * @param mst result matrix of mst
 * @return 0 = success 1 = error
 */
int get_least_spanning_tree(graph_t* graph, int** mst) {
  if (validate_mst_input(graph, mst)) {
    return 1;
  }
  const int vertex_count = graph->adjacency->size;
  int* visited = (int*)calloc(vertex_count, sizeof(int));
  if (!visited) return 1;
  init_mst_matrix(mst, vertex_count);
  visited[0] = 1;
  for (int e = 0; e < vertex_count - 1; e++) {
    int min_weight, src, dest;
    find_min_edge(graph, visited, vertex_count, &min_weight, &src, &dest);

    if (src == -1 || dest == -1) {
      free(visited);
      return 1;
    }
    mst[src][dest] = min_weight;
    mst[dest][src] = min_weight;
    visited[dest] = 1;
  }
  free(visited);
  return 0;
}
