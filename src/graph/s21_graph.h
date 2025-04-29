#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <stdbool.h>

#include "matrix/matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief matrix structure
 * @param data pointer to matrix
 * @param size matrix size
 */
typedef struct {
  int **data;
  int size;
} matrix_t;

/**
 * @brief graph structure
 * @param adjacency pointer to adjacency matrix
 */
typedef struct {
  matrix_t *adjacency;
} graph_t;

graph_t *graph_create(int size);
void graph_delete(graph_t *graph);
int get_order(graph_t *graph);
bool load_graph_from_file(graph_t *graph, const char *filename);
void export_graph_to_dot(const graph_t *graph, const char *filename);

#ifdef __cplusplus
}
#endif

#endif  // S21_GRAPH_H
