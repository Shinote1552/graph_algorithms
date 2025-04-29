#ifndef ANT_COLONY_OPTIMIZATION_PRIVATE_H
#define ANT_COLONY_OPTIMIZATION_PRIVATE_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../graph/s21_graph.h"
#include "ant_colony_optimization_public.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ant structure
 * @param path array of visited vertices
 * @param path_size current size of path
 * @param visited_vertices array of visited vertices and pheromone values
 * @param vertex_size current vertex
 * @param path_distance length of path
 * @param can_continue can ant continue
 */
typedef struct {
  int* path;
  int path_size;
  double* visited_vertices;
  int vertex_size;
  double path_distance;
  bool can_continue;
} ant_t;

typedef struct {
  tsm_result_t best_path;
  int iterations;
} ant_colony_result_t;

void ant_colony_optimization(ant_colony_result_t* result, const graph_t* graph,
                             const aco_params_t* params);
ant_colony_result_t* aco_result_create(int size);
void aco_result_delete(ant_colony_result_t* result);
double ant_get_random_choice(void);
int select_next_vertex(const double* probabilities, const int* neighbors,
                       int neighbor_count, double choice);
void update_local_pheromone(double* local_pheromone, const ant_t* ant,
                            const double q_k);
void update_global_pheromone(double** pheromone, const double* local_pheromone,
                             const int size, const double evaporation_rate,
                             const double min_pheromone);
void handle_no_neighbors(ant_t* ant, const graph_t* graph);
void run_ant_colony_iteration(ant_t** ants, int vertex_count,
                              const graph_t* graph, double** pheromone,
                              double* local_pheromone,
                              const aco_params_t* params,
                              ant_colony_result_t* result);
void update_best_path(ant_colony_result_t* result, const ant_t* ant);
void calculate_probabilities(const ant_t* ant, const graph_t* graph,
                             double** pheromone, double alpha, double beta,
                             double* probabilities, int neighbor_count,
                             const int* neighbors);
bool is_complete_path(const ant_t* ant, int vertex_count);
void try_return_to_start(ant_t* ant, const graph_t* graph);
void handle_single_vertex_case(tsm_result_t* result);
void handle_empty_graph_case(tsm_result_t* result);
bool is_valid_path(const ant_colony_result_t* result, int vertex_count);
void copy_result(tsm_result_t* dest, const ant_colony_result_t* src);
void set_invalid_result(tsm_result_t* result);

#ifdef __cplusplus
}
#endif

#endif  // ANT_COLONY_OPTIMIZATION_PRIVATE_H
