#ifndef ANT_COLONY_OPTIMIZATION_PUBLIC_H
#define ANT_COLONY_OPTIMIZATION_PUBLIC_H

#include "../../graph/s21_graph.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief result structure for solve_traveling_salesman_problem.
 * @param vertices array of vertices(path)
 * @param distance length of path(sum of edges)
 */
typedef struct {
  int* vertices;
  int size;
  double distance;
} tsm_result_t;

/**
 * @brief Parameter structure for Ant Colony Optimization (ACO) algorithm in TSP
 * solutions.
 *
 * @param alpha_k             Pheromone influence exponent (α). Higher values
 * increase pheromone trail importance.
 * @param beta_k              Heuristic influence exponent (β). Higher values
 * prioritize shorter edges.
 * @param initial_pheromone_k Starting pheromone concentration on all edges.
 * @param q_k                 Pheromone deposit constant (Q). Scales total
 * pheromone added per iteration.
 * @param evaporation_k       Pheromone evaporation rate (ρ). Determines how
 * quickly old trails fade (0.1-0.5 typical).
 * @param min_pheromone_k     Minimum pheromone threshold. Prevents algorithm
 * stagnation (0.001-0.01 recommended).
 * @param max_iterations      Termination condition. Maximum iterations before
 * stopping (50-500 typical).
 */
typedef struct {
  double alpha_k;
  double beta_k;
  double initial_pheromone_k;
  double q_k;
  double evaporation_k;
  double min_pheromone_k;
  int max_iterations;
} aco_params_t;

tsm_result_t* tsm_result_create(void);
void tsm_result_delete(tsm_result_t* tsm_result);

#ifdef __cplusplus
}
#endif

#endif  // ANT_COLONY_OPTIMIZATION_PUBLIC_H

/**
 * aco realization by Marco Dorigo method
 */
