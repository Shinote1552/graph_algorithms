#include "ant_colony_optimization_private.h"

/**
 * @brief Creates ant colony optimization result structure.
 * @param size The size of the result structure.
 * @return A pointer to the created structure, or NULL if memory allocation
 * failed.
 */
ant_colony_result_t* aco_result_create(const int size) {
  ant_colony_result_t* result =
      (ant_colony_result_t*)malloc(sizeof(ant_colony_result_t));
  if (!result) return NULL;

  result->best_path.vertices = (int*)malloc((size + 1) * sizeof(int));
  if (!result->best_path.vertices) {
    free(result);
    return NULL;
  }
  result->best_path.size = 0;
  result->best_path.distance = INFINITY;
  result->iterations = 0;
  return result;
}

/**
 * @brief Deletes ant colony optimization result structure.
 * @param result Pointer to the ant_colony_result_t structure to be deleted.
 * @return void
 */
void aco_result_delete(ant_colony_result_t* result) {
  if (!result) return;
  free(result->best_path.vertices);
  free(result);
}

double ant_get_random_choice(void) { return (double)rand() / (double)RAND_MAX; }

int* get_unvisited_neighbors(const ant_t* ant, const graph_t* graph) {
  int* neighbors = (int*)malloc(graph->adjacency->size * sizeof(int));
  if (!neighbors) return NULL;
  int count = 0;
  for (int to = 0; to < graph->adjacency->size; ++to) {
    bool is_connected = graph->adjacency->data[ant->vertex_size][to] > 0;
    bool is_unvisited = ant->visited_vertices[to] == 0.0;
    if (is_connected && is_unvisited) {
      neighbors[count++] = to;
    }
  }
  neighbors[count] = -1;  // ends marker
  return neighbors;
}

void initialize_pheromone(double*** pheromone, double** local_pheromone,
                          int size, double initial_value) {
  *pheromone = (double**)malloc(size * sizeof(double*));
  *local_pheromone = (double*)calloc(size, sizeof(double));
  for (int i = 0; i < size; ++i) {
    (*pheromone)[i] = (double*)malloc(size * sizeof(double));
    for (int j = 0; j < size; ++j) {
      (*pheromone)[i][j] = (i == j) ? 0.0 : initial_value;
    }
  }
}

void free_pheromone(double*** pheromone, double* local_pheromone, int size) {
  for (int i = 0; i < size; ++i) {
    free((*pheromone)[i]);
  }
  free(*pheromone);
  free(local_pheromone);
}

void initialize_ant(ant_t* ant, int start_vertex, int vertex_count) {
  ant->path = (int*)malloc((vertex_count + 1) * sizeof(int));
  ant->path[0] = start_vertex;
  ant->path_size = 1;
  ant->visited_vertices = (double*)calloc(vertex_count, sizeof(double));
  ant->visited_vertices[start_vertex] = 1.0;
  ant->vertex_size = start_vertex;
  ant->path_distance = 0.0;
  ant->can_continue = true;
}
void free_ant(ant_t* ant) {
  free(ant->path);
  free(ant->visited_vertices);
}

void update_ant_path(ant_t* ant, int next_vertex, const graph_t* graph) {
  ant->path[ant->path_size++] = next_vertex;
  ant->visited_vertices[next_vertex] = 1.0;
  ant->path_distance += graph->adjacency->data[ant->vertex_size][next_vertex];
  ant->vertex_size = next_vertex;
}

/**
 * @brief calculates probabilities for ant to choose next vertex
 * @param ant pointer to ant structure
 * @param graph pointer to graph structure
 * @param pheromone pheromone levels matrix
 * @param alpha constant
 * @param beta constant
 * @param probabilities array to store calculated probabilities
 * @param neighbor_count number of neighbors
 * @param neighbors array of neighbors
 */
void calculate_probabilities(const ant_t* ant, const graph_t* graph,
                             double** pheromone, double alpha, double beta,
                             double* probabilities, int neighbor_count,
                             const int* neighbors) {
  double total = 0.0;
  // calculate probabilities
  for (int i = 0; i < neighbor_count; ++i) {
    int to = neighbors[i];
    double pheromone_level = pheromone[ant->vertex_size][to];
    double weight = graph->adjacency->data[ant->vertex_size][to];
    double heuristic = 1.0 / weight;
    probabilities[i] = pow(pheromone_level, alpha) * pow(heuristic, beta);
    total += probabilities[i];
  }
  // normalize probabilities
  for (int i = 0; i < neighbor_count; ++i) {
    probabilities[i] /= total;
    // make probabilities cumulative to be able to select next vertex
    if (i > 0) probabilities[i] += probabilities[i - 1];
  }
}

int select_next_vertex(const double* probabilities, const int* neighbors,
                       int neighbor_count, double choice) {
  for (int i = 0; i < neighbor_count; ++i) {
    if (choice <= probabilities[i]) {
      return neighbors[i];
    }
  }
  return neighbors[neighbor_count - 1];
}

void ant_make_choice(ant_t* ant, const graph_t* graph, double** pheromone,
                     double alpha, double beta) {
  if (ant->path_size == graph->adjacency->size) {
    try_return_to_start(ant, graph);
    return;
  }
  int* neighbors = get_unvisited_neighbors(ant, graph);
  if (!neighbors) return;
  int neighbor_count = 0;
  while (neighbors[neighbor_count] != -1) neighbor_count++;
  if (neighbor_count == 0) {
    handle_no_neighbors(ant, graph);
    free(neighbors);
    return;
  }
  double* probabilities = (double*)malloc(neighbor_count * sizeof(double));
  calculate_probabilities(ant, graph, pheromone, alpha, beta, probabilities,
                          neighbor_count, neighbors);
  double choice = ant_get_random_choice();
  int next_vertex =
      select_next_vertex(probabilities, neighbors, neighbor_count, choice);
  update_ant_path(ant, next_vertex, graph);
  free(probabilities);
  free(neighbors);
}

void try_return_to_start(ant_t* ant, const graph_t* graph) {
  int start = ant->path[0];
  if (graph->adjacency->data[ant->vertex_size][start] > 0) {
    update_ant_path(ant, start, graph);
  }
  ant->can_continue = false;
}
void handle_no_neighbors(ant_t* ant, const graph_t* graph) {
  ant->can_continue = false;
  int start = ant->path[0];
  bool can_return = graph->adjacency->data[ant->vertex_size][start] > 0;
  if (can_return) {
    update_ant_path(ant, start, graph);
  }
}
void update_local_pheromone(double* local_pheromone, const ant_t* ant,
                            const double q_k) {
  for (int i = 0; i < ant->path_size - 1; i++) {
    int from = ant->path[i];
    local_pheromone[from] += q_k / ant->path_distance;
  }
}

void update_global_pheromone(double** pheromone, const double* local_pheromone,
                             const int size, const double evaporation_rate,
                             const double min_pheromone) {
  for (int from = 0; from < size; ++from) {
    for (int to = 0; to < size; ++to) {
      if (from != to) {
        // Apply evaporation and add new pheromone
        pheromone[from][to] = (1.0 - evaporation_rate) * pheromone[from][to] +
                              local_pheromone[from];

        // Enforce minimum pheromone level
        pheromone[from][to] = fmax(pheromone[from][to], min_pheromone);
      }
    }
  }
}

void run_ant_colony_iteration(ant_t** ants, int vertex_count,
                              const graph_t* graph, double** pheromone,
                              double* local_pheromone,
                              const aco_params_t* params,
                              ant_colony_result_t* result) {
  for (int i = 0; i < vertex_count; ++i) {
    while (ants[i]->can_continue) {
      ant_make_choice(ants[i], graph, pheromone, params->alpha_k,
                      params->beta_k);
    }
    if (is_complete_path(ants[i], vertex_count)) {
      update_best_path(result, ants[i]);
      update_local_pheromone(local_pheromone, ants[i], params->q_k);
    }
  }
}

bool is_complete_path(const ant_t* ant, int vertex_count) {
  return (ant->path_size == vertex_count + 1) &&
         (ant->path[0] == ant->path[vertex_count]);
}

void update_best_path(ant_colony_result_t* result, const ant_t* ant) {
  if (ant->path_distance < result->best_path.distance) {
    memcpy(result->best_path.vertices, ant->path, ant->path_size * sizeof(int));
    result->best_path.size = ant->path_size;
    result->best_path.distance = ant->path_distance;
  }
}

void handle_single_vertex_case(tsm_result_t* result) {
  result->vertices = (int*)malloc(2 * sizeof(int));
  result->vertices[0] = 0;
  result->vertices[1] = 0;
  result->size = 2;
  result->distance = 0;
}

void handle_empty_graph_case(tsm_result_t* result) {
  result->vertices = NULL;
  result->size = 0;
  result->distance = INFINITY;
}

bool is_valid_path(const ant_colony_result_t* result, int vertex_count) {
  bool has_full_path = result->best_path.size == vertex_count + 1;
  bool is_cycle =
      result->best_path.vertices[0] == result->best_path.vertices[vertex_count];
  return has_full_path && is_cycle;
}

void copy_result(tsm_result_t* dest, const ant_colony_result_t* src) {
  dest->vertices = (int*)malloc(src->best_path.size * sizeof(int));
  memcpy(dest->vertices, src->best_path.vertices,
         src->best_path.size * sizeof(int));
  dest->size = src->best_path.size;
  dest->distance = src->best_path.distance;
}

void set_invalid_result(tsm_result_t* result) {
  result->vertices = NULL;
  result->size = 0;
  result->distance = INFINITY;
}

void ant_colony_optimization(ant_colony_result_t* result, const graph_t* graph,
                             const aco_params_t* params) {
  if (graph->adjacency->size == 0) return;

  srand((unsigned int)time(NULL));
  const int vertex_count = graph->adjacency->size;
  double** pheromone = NULL;
  double* local_pheromone = NULL;
  initialize_pheromone(&pheromone, &local_pheromone, vertex_count,
                       params->initial_pheromone_k);
  for (int iteration = 0; iteration < params->max_iterations; ++iteration) {
    ant_t** ants = (ant_t**)malloc(vertex_count * sizeof(ant_t*));
    for (int i = 0; i < vertex_count; ++i) {
      ants[i] = (ant_t*)malloc(sizeof(ant_t));
      initialize_ant(ants[i], i, vertex_count);
    }
    run_ant_colony_iteration(ants, vertex_count, graph, pheromone,
                             local_pheromone, params, result);
    update_global_pheromone(pheromone, local_pheromone, vertex_count,
                            params->evaporation_k, params->min_pheromone_k);
    memset(local_pheromone, 0, vertex_count * sizeof(double));
    for (int i = 0; i < vertex_count; ++i) {
      free_ant(ants[i]);
      free(ants[i]);
    }
    free(ants);
  }
  free_pheromone(&pheromone, local_pheromone, vertex_count);
  result->iterations = params->max_iterations;
}

/**
 * @brief Solves the traveling salesman problem using the ant colony
 * optimization algorithm.
 * @param result The result structure to store the solution.
 * @param graph The graph to be solved.
 * @param params The parameters for the ant colony optimization algorithm.
 * @return void
 */
void solve_traveling_salesman_problem(tsm_result_t* result,
                                      const graph_t* graph,
                                      const aco_params_t* params) {
  if (!result) {
    return;
  } else if (graph->adjacency->size == 1) {
    handle_single_vertex_case(result);
    return;
  } else if (graph->adjacency->size == 0) {
    handle_empty_graph_case(result);
    return;
  }
  ant_colony_result_t* ant_colony_result =
      aco_result_create(graph->adjacency->size);
  ant_colony_optimization(ant_colony_result, graph, params);
  if (is_valid_path(ant_colony_result, graph->adjacency->size)) {
    copy_result(result, ant_colony_result);
  } else {
    set_invalid_result(result);
  }
  aco_result_delete(ant_colony_result);
}
