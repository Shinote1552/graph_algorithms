# Ant Colony Optimization PUBLIC (ACO) Module Specification

## Overview
This module implements the Ant Colony Optimization metaheuristic for solving the Traveling Salesman Problem (TSP) based on Marco Dorigo's method. It simulates ant behavior to find optimal/near-optimal paths through graphs.

## Data Structures

### `tsm_result_t`
Stores the TSP solution found by ACO.

**Fields:**
- `int* vertices`: Array representing the optimal path (vertex sequence)
- `int size`: Number of vertices in the path
- `double distance`: Total distance of the optimal path

### `aco_params_t`
Configuration parameters for ACO algorithm tuning.

**Parameters:**
| Parameter            | Type     | Description                                                                 | Typical Range     |
|----------------------|----------|-----------------------------------------------------------------------------|-------------------|
| `alpha_k`            | double   | Pheromone influence (α) - Higher values increase trail importance           | 0.5 - 2.0         |
| `beta_k`             | double   | Heuristic influence (β) - Prioritizes shorter edges when higher             | 1.0 - 5.0         |
| `initial_pheromone_k`| double   | Starting pheromone concentration on edges                                   | 0.1 - 1.0         |
| `q_k`                | double   | Pheromone deposit constant (Q) - Scales pheromone added per iteration       | 10 - 100          |
| `evaporation_k`      | double   | Evaporation rate (ρ) - How quickly old trails fade                          | 0.1 - 0.5         |
| `min_pheromone_k`    | double   | Minimum pheromone threshold - Prevents algorithm stagnation                | 0.001 - 0.01      |
| `max_iterations`     | int      | Maximum iterations before termination                                      | 50 - 500          |

## Core Functions

### `tsm_result_t* tsm_result_create(void)`
Creates and initializes a TSM result structure.

**Returns:**
- Pointer to allocated structure
- NULL on memory allocation failure

### `void tsm_result_delete(tsm_result_t* tsm_result)`
Frees all memory associated with a TSM result.

**Parameters:**
- `tsm_result`: Structure to deallocate

## Algorithm Characteristics

### Pheromone Update
- **Global Update**: Reinforces pheromones on edges belonging to the best tour
- **Evaporation**: Gradually reduces pheromone levels to avoid local optima

### Transition Rule
Uses probabilistic selection based on:
Where:
- τ = pheromone level
- η = heuristic information (1/distance)
- α,β = control parameters

## Dependencies
- Graph module (`s21_graph.h`) for graph representation
- Standard C library for memory allocation

## Usage Example
```c
// Initialize parameters
aco_params_t params = {
    .alpha_k = 1.0,
    .beta_k = 2.0,
    .initial_pheromone_k = 0.5,
    .q_k = 50.0,
    .evaporation_k = 0.3,
    .min_pheromone_k = 0.01,
    .max_iterations = 100
};

// Solve TSP
tsm_result_t* result = tsm_result_create();
solve_traveling_salesman_problem(result, graph, &params);

// Use results
printf("Optimal path distance: %f\n", result->distance);

// Cleanup
tsm_result_delete(result);
```
# Ant Colony Optimization PRIVATE (ACO)(Private Module Implementation)
## Internal Data Structures

### `ant_t`
Represents an individual ant in the colony.

**Fields:**
| Field               | Type      | Description                                                                 |
|---------------------|-----------|-----------------------------------------------------------------------------|
| `path`              | `int*`    | Array of visited vertices in traversal order                               |
| `path_size`         | `int`     | Current number of vertices in path                                         |
| `visited_vertices`  | `double*` | Marks visited vertices and pheromone values                                |
| `vertex_size`       | `int`     | Current vertex position                                                   |
| `path_distance`     | `double`  | Total distance traveled by ant                                            |
| `can_continue`      | `bool`    | Flag indicating if ant can continue moving                                |

### `ant_colony_result_t`
Stores colony-wide optimization results.

**Fields:**
| Field           | Type            | Description                                     |
|-----------------|-----------------|-------------------------------------------------|
| `best_path`     | `tsm_result_t`  | Best solution found across all iterations       |
| `iterations`    | `int`           | Total iterations performed                      |

## Core Algorithm Functions

### Colony Management
| Function                          | Description                                                                 |
|-----------------------------------|-----------------------------------------------------------------------------|
| `ant_colony_optimization()`       | Main ACO algorithm controller                                               |
| `run_ant_colony_iteration()`      | Executes single iteration of ant movements and pheromone updates            |
| `update_best_path()`              | Updates global best solution if better path found                           |

### Ant Operations
| Function                          | Description                                                                 |
|-----------------------------------|-----------------------------------------------------------------------------|
| `select_next_vertex()`            | Probabilistically selects next vertex based on pheromone and heuristic      |
| `calculate_probabilities()`       | Computes transition probabilities to neighboring vertices                   |
| `is_complete_path()`              | Checks if ant has completed a full cycle                                    |
| `try_return_to_start()`           | Attempts to complete cycle by returning to start vertex                     |

### Pheromone Handling
| Function                          | Description                                                                 |
|-----------------------------------|-----------------------------------------------------------------------------|
| `update_local_pheromone()`        | Updates pheromone levels based on individual ant paths                      |
| `update_global_pheromone()`       | Applies evaporation and updates global pheromone matrix                     |

### Result Handling
| Function                          | Description                                                                 |
|-----------------------------------|-----------------------------------------------------------------------------|
| `aco_result_create()`             | Allocates and initializes result structure                                  |
| `aco_result_delete()`             | Deallocates result resources                                                |
| `copy_result()`                   | Copies optimized path to output structure                                   |
| `set_invalid_result()`            | Marks result as invalid for error cases                                     |

### Edge Cases
| Function                          | Description                                                                 |
|-----------------------------------|-----------------------------------------------------------------------------|
| `handle_no_neighbors()`           | Handles ants with no available moves                                       |
| `handle_single_vertex_case()`     | Special case for single-vertex graphs                                      |
| `handle_empty_graph_case()`       | Special case for empty graphs                                              |
| `is_valid_path()`                 | Validates solution integrity                                               |

## Algorithm Workflow

1. **Initialization**
   - Create ant colony with random starting positions
   - Initialize pheromone matrix with `initial_pheromone_k`

2. **Iteration Loop**
   ```plaintext
   For each iteration up to max_iterations:
       For each ant:
           While can_continue:
               Calculate move probabilities
               Select next vertex probabilistically
               Update path and distance
           Try complete cycle
           Update local pheromone
       Apply global pheromone update
       Check for new best path

3. **Termination**
    - Return best path found
    - Handle special cases (no solution found)

## Probability Calculation
```P(i,j) = [τ(i,j)^α * η(i,j)^β] / Σ[τ(i,k)^α * η(i,k)^β]```

**Where:**

    τ(i,j) = pheromone on edge (i,j)
    η(i,j) = 1/distance(i,j) (heuristic)
    α,β = control parameters

### Error handles ###
Special cases handled:

    - Graphs with 0 or 1 vertices
    - Disconnected graphs
    - Stagnation detection (via min_pheromone)
### Dependencies ###
    - Standard C libraries (math, stdlib, string, time)
    - Graph module (s21_graph.h)
    - Public ACO header (ant_colony_optimization_public.h)

### Performance Considerations ###
    - Memory: O(ants*N + N²) for N vertices
    - Time: O(iterations * ants * N²)
    - Parallelization opportunities in ant movement phase
    - you can use SIMD to force operations with matrix