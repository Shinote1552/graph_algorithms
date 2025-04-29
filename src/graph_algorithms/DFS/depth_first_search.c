#include "../data_structures/stack/stack.h"
#include "../s21_graph_algorithms.h"

/**
 * Depth first search algorithm
 * @brief depth first search
 * @param graph graph structure pointer
 * @param start_vertex start vertex
 * @param result result structure pointer
 * @return void
 */
void depth_first_search(graph_t* graph, int start_vertex,
                        graph_traversal_result_t* result) {
  if (!graph || !result || !graph->adjacency || !graph->adjacency->data ||
      graph->adjacency->size == 0 || start_vertex < 0 ||
      start_vertex >= graph->adjacency->size) {
    return;
  }
  stack* st = stack_create();
  if (!st) return;
  int* visited = (int*)calloc(graph->adjacency->size, sizeof(int));
  if (!visited) {
    stack_delete(st);
    return;
  }
  stack_push(st, start_vertex);
  visited[start_vertex] = 1;
  result->size = 0;
  while (!stack_is_empty(st)) {
    int current_vertex = stack_top(st);
    stack_pop(st);
    result->visited_vertices[result->size++] = current_vertex;
    for (int n = graph->adjacency->size - 1; n >= 0; n--) {
      if (graph->adjacency->data[current_vertex][n] && !visited[n]) {
        stack_push(st, n);
        visited[n] = 1;
      }
    }
  }
  stack_delete(st);
  free(visited);
}
