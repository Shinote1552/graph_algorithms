#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H

/**
 * **************************************************************************
 * by_edmurepi | ࿋꒚ꎧｴℕꑙￓﾼ|1552࿋ | Glowing in the dark | Shinote |
 * @TTGLShinote
 * **************************************************************************
 */

#include <limits.h>

#include "ACO/ant_colony_optimization_public.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief result structure for graph algorithms BFS and DFS.
 * @param visited_vertices array of visited vertices(path).
 * @param size size of array(and visited_vertices).
 */
typedef struct {
  int *visited_vertices;
  int size;
} graph_traversal_result_t;

graph_traversal_result_t *traversal_result_create(int size);
void traversal_result_delete(graph_traversal_result_t *result);
void depth_first_search(graph_t *graph, int start_vertex,
                        graph_traversal_result_t *result);
void breadth_first_search(graph_t *graph, int start_vertex,
                          graph_traversal_result_t *result);
int get_shortest_path_between_vertices(graph_t *graph, int vertex1,
                                       int vertex2);
int get_shortest_paths_between_all_vertices(graph_t *graph, int **dist);
int get_least_spanning_tree(graph_t *graph, int **mst);
void solve_traveling_salesman_problem(tsm_result_t *result,
                                      const graph_t *graph,
                                      const aco_params_t *params);
#ifdef __cplusplus
}
#endif

#endif  // S21_GRAPH_ALGORITHMS_H
