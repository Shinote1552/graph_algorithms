#include <math.h>

#include "../s21_graph_algorithms.h"

/**
 * @brief Creates a new graph traversal result structure.
 * @param size The size of the result structure.
 * @return A pointer to the created structure, or NULL if memory allocation
 * failed.
 */
graph_traversal_result_t* traversal_result_create(int size) {
  graph_traversal_result_t* result = NULL;
  result = (graph_traversal_result_t*)malloc(sizeof(graph_traversal_result_t));
  if (result != NULL) {
    result->visited_vertices = (int*)malloc(size * sizeof(int));
    if (result->visited_vertices != NULL) {
      result->size = 0;
    } else {
      free(result);
      result = NULL;
    }
  }
  return result;
}

/**
 * @brief Deletes a graph traversal result.
 *
 * Frees the memory allocated for the visited vertices and the result structure
 * itself.
 *
 * @param result Pointer to the graph_traversal_result_t structure to be
 * deleted.
 */
void traversal_result_delete(graph_traversal_result_t* result) {
  if (result != NULL) {
    if (result->visited_vertices != NULL) {
      free(result->visited_vertices);
    }
    free(result);
  }
}

/**
 * @brief Creates a new TSM result structure.
 * @return A pointer to the created structure, or NULL if memory allocation
 * failed.
 */
tsm_result_t* tsm_result_create(void) {
  tsm_result_t* result = (tsm_result_t*)malloc(sizeof(tsm_result_t));
  if (!result) return NULL;

  result->vertices = NULL;
  result->size = 0;
  result->distance = INFINITY;
  return result;
}

/**
 * @brief Deletes a TSM result.
 */
void tsm_result_delete(tsm_result_t* tsm_result) {
  if (!tsm_result) return;

  free(tsm_result->vertices);
  free(tsm_result);
}
