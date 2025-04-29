#include "../data_structures/queue/queue.h"
#include "../s21_graph_algorithms.h"

/**
 * @brief breadth first search (BFS)
 * @param graph graph structure pointer
 * @param start_vertex start vertex
 * @param result result structure pointer
 * @return void
 */
void breadth_first_search(graph_t* graph, int start_vertex,
                          graph_traversal_result_t* result) {
  if (!graph || !result || !graph->adjacency || !graph->adjacency->data ||
      graph->adjacency->size == 0 || start_vertex < 0 ||
      start_vertex >= graph->adjacency->size) {
    return;
  }
  queue* q = queue_create();
  if (!q) return;
  int* visited = (int*)calloc(graph->adjacency->size, sizeof(int));
  if (!visited) {
    queue_delete(q);
    return;
  }
  queue_push(q, start_vertex);
  visited[start_vertex] = 1;
  result->size = 0;
  while (!queue_is_empty(q)) {
    int current_vertex = queue_front(q);
    queue_pop(q);
    result->visited_vertices[result->size++] = current_vertex;
    for (int n = 0; n < graph->adjacency->size; n++) {
      if (graph->adjacency->data[current_vertex][n] && !visited[n]) {
        queue_push(q, n);
        visited[n] = 1;
      }
    }
  }
  queue_delete(q);
  free(visited);
}
