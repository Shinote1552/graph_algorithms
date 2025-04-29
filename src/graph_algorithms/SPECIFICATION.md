# Graph Algorithms Module Specification

## Overview
This module provides implementations of fundamental graph algorithms including traversal, shortest path, minimum spanning tree, and the Traveling Salesman Problem (TSP).

## Data Structures

### `graph_traversal_result_t`
Stores results of graph traversal algorithms (BFS/DFS).

**Fields:**
- `int *visited_vertices`: Array storing the traversal path
- `int size`: Number of vertices in the traversal path

### `tsm_result_t` (from ACO submodule)
Stores results for Traveling Salesman Problem solutions.

**Fields:**
- `int *vertices`: Array storing the optimal path
- `int size`: Number of vertices in the path
- `double distance`: Total distance of the path

## Core Algorithms

### Graph Traversal

#### `graph_traversal_result_t* traversal_result_create(int size)`
Creates a new traversal result structure.

**Parameters:**
- `size`: Maximum number of vertices to store

**Returns:**
- Pointer to new structure on success
- NULL on memory allocation failure

#### `void traversal_result_delete(graph_traversal_result_t* result)`
Frees memory allocated for traversal results.

**Parameters:**
- `result`: Structure to deallocate

#### `void depth_first_search(graph_t *graph, int start_vertex, graph_traversal_result_t *result)`
Performs DFS traversal starting from specified vertex.

**Parameters:**
- `graph`: Input graph
- `start_vertex`: Starting vertex (1-based index)
- `result`: Pre-allocated structure to store results

#### `void breadth_first_search(graph_t *graph, int start_vertex, graph_traversal_result_t *result)`
Performs BFS traversal starting from specified vertex.

**Parameters:**
- Same as DFS

### Shortest Path Algorithms

#### `int get_shortest_path_between_vertices(graph_t *graph, int vertex1, int vertex2)`
Finds shortest path between two vertices using Dijkstra's algorithm.

**Parameters:**
- `graph`: Input graph
- `vertex1`, `vertex2`: Start and end vertices (1-based)

**Returns:**
- Shortest path distance on success
- -1 on error (invalid vertices or disconnected graph)

#### `int get_shortest_paths_between_all_vertices(graph_t *graph, int **dist)`
Computes all-pairs shortest paths using Floyd-Warshall algorithm.

**Parameters:**
- `graph`: Input graph
- `dist`: Pointer to distance matrix (allocated by caller)

**Returns:**
- 0 on success
- -1 on error

### Minimum Spanning Tree

#### `int get_least_spanning_tree(graph_t *graph, int **mst)`
Finds MST using Prim's algorithm.

**Parameters:**
- `graph`: Input graph
- `mst`: Pointer to MST adjacency matrix (allocated by caller)

**Returns:**
- 0 on success
- -1 on error

### Traveling Salesman Problem

#### `void solve_traveling_salesman_problem(tsm_result_t *result, const graph_t *graph, const aco_params_t *params)`
Solves TSP using Ant Colony Optimization.

**Parameters:**
- `result`: Pre-allocated structure to store solution
- `graph`: Input graph
- `params`: ACO algorithm parameters (pheromone, evaporation rate, etc.)

## Utility Functions

#### `tsm_result_t* tsm_result_create(void)`
Creates new TSM result structure.

**Returns:**
- Pointer to new structure
- NULL on allocation failure

#### `void tsm_result_delete(tsm_result_t* tsm_result)`
Frees TSM result structure.

## Error Handling
- Functions return error codes (-1) or NULL for critical failures
- Memory allocation failures are handled gracefully
- Input parameters are validated

## Dependencies
- Standard C library (stdlib.h, math.h)
- Graph module (s21_graph.h)
- ACO submodule (ant_colony_optimization_public.h)

## Usage Example
```c
// Graph traversal example
graph_traversal_result_t* dfs_result = traversal_result_create(graph_size);
depth_first_search(graph, 1, dfs_result);
traversal_result_delete(dfs_result);

// Shortest path example
int distance = get_shortest_path_between_vertices(graph, 1, 5);

// TSP example
tsm_result_t* tsp_result = tsm_result_create();
aco_params_t params = {
    .alpha_k = 1.0,
    .beta_k = 2.0,
    .initial_pheromone_k = 0.5,
    .q_k = 50.0,
    .evaporation_k = 0.3,
    .min_pheromone_k = 0.01,
    .max_iterations = 100
};
solve_traveling_salesman_problem(tsp_result, graph, &params);
tsm_result_delete(tsp_result);
```