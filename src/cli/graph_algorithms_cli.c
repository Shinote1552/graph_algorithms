#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

// if linux #include <linux/limits.h>  // For PATH_MAX

#ifdef __linux__
#include <linux/limits.h>
#endif

#include "../graph/s21_graph.h"
#include "../graph_algorithms/s21_graph_algorithms.h"

#ifdef __cplusplus
extern "C" {
#endif

// aco_params_t define
#define ALPHA_K 1.0
#define BETA_K 2.0
#define PHEROMONE_K 1.0
#define Q_K 100.0
#define EVAPORATION_K 0.5
#define MIN_PHEROMONE_K 0.01
#define MAX_ITERATIONS_K 1000

/**
 * @brief Structure for measuring execution time
 * @details Contains start and end time
 */
typedef struct {
  clock_t start;
  clock_t end;
} my_timer_t;

void timer_start(my_timer_t *timer) { timer->start = clock(); }

double timer_stop(my_timer_t *timer) {
  timer->end = clock();
  return (double)(timer->end - timer->start) / CLOCKS_PER_SEC;
}

void print_execution_time(double time_spent) {
  printf(
      "________________________________________________\nExecution time: %.6f "
      "seconds\n________________________________________________\n",
      time_spent);
}

void print_matrix(int **matrix, int size) {
  printf("    ");
  for (int i = 0; i < size; i++) {
    printf("%4d", i + 1);
  }
  printf("\n");
  for (int i = 0; i < size; i++) {
    printf("%4d", i + 1);
    for (int j = 0; j < size; j++) {
      if (matrix[i][j] == INT_MAX) {
        printf("   ∞");
      } else {
        printf("%4d", matrix[i][j]);
      }
    }
    printf("\n");
  }
}

bool is_graphviz_available() { return system("dot -V") == 0; }

void handle_how_to_visualize_graph(graph_t *graph) {
  if (graph == NULL || graph->adjacency == NULL) {
    printf("\n):\tGraph is not loaded!\t:(\n");
    return;
  }
  printf("________________________________________________\n");
  printf("Adjacency matrix of the graph:\n");
  printf("________________________________________________\n");
  print_matrix(graph->adjacency->data, graph->adjacency->size);
  printf("________________________________________________\n");
  if (is_graphviz_available()) {
    printf("\nTo visualize this graph using Graphviz:\n");
    printf("1. First export the graph to DOT format (option 8)\n");
    printf("2. Then run: dot -Tpng yourfile.dot -o graph.png\n");
    printf("3. Open graph.png to view the visualization\n");
  } else {
    printf("\nNote: Graphviz is not installed on your system.\n");
    printf(
        "To visualize graphs, install Graphviz from https://graphviz.org/\n");
  }
  printf("________________________________________________\n");
}

void handle_bfs(graph_t *graph) {
  if (graph == NULL || graph->adjacency == NULL) {
    printf("Graph is not loaded!\n");
    return;
  }
  int start_vertex;
  printf("Enter start vertex (1-%d): ", get_order(graph));
  if (scanf("%d", &start_vertex) != 1) {
    printf("Invalid input!\n");
    while (getchar() != '\n');
    return;
  }
  if (start_vertex < 1 || start_vertex > get_order(graph)) {
    printf("Invalid vertex!\n");
    return;
  }
  my_timer_t timer;
  timer_start(&timer);
  graph_traversal_result_t *result = traversal_result_create(get_order(graph));
  breadth_first_search(graph, start_vertex, result);
  double time_spent = timer_stop(&timer);
  printf("________________________________________________\n");
  printf("\nBFS traversal: ");
  for (int i = 0; i < result->size; i++) {
    printf("%d ", result->visited_vertices[i] + 1);  // +1 for 1-based output
  }
  printf("\n");
  print_execution_time(time_spent);
  traversal_result_delete(result);
}

void handle_dfs(graph_t *graph) {
  if (graph == NULL || graph->adjacency == NULL) {
    printf("Graph is not loaded!\n");
    return;
  }
  int start_vertex;
  printf("Enter start vertex (1-%d): ", get_order(graph));
  if (scanf("%d", &start_vertex) != 1) {
    printf("Invalid input!\n");
    while (getchar() != '\n');  // Clear input buffer
    return;
  }
  if (start_vertex < 1 || start_vertex > get_order(graph)) {
    printf("Invalid vertex!\n");
    return;
  }
  my_timer_t timer;
  timer_start(&timer);
  graph_traversal_result_t *result = traversal_result_create(get_order(graph));
  depth_first_search(graph, start_vertex, result);
  double time_spent = timer_stop(&timer);
  printf("________________________________________________\n");
  printf("\nDFS traversal: ");
  for (int i = 0; i < result->size; i++) {
    printf("%d ", result->visited_vertices[i] + 1);  // +1 for 1-based output
  }
  printf("\n");
  print_execution_time(time_spent);
  traversal_result_delete(result);
}

void handle_shortest_path(graph_t *graph) {
  if (graph == NULL || graph->adjacency == NULL) {
    printf("Graph is not loaded!\n");
    return;
  }
  int vertex1, vertex2;
  printf("Enter first vertex (1-%d): ", get_order(graph));
  if (scanf("%d", &vertex1) != 1) {
    printf("Invalid input!\n");
    while (getchar() != '\n');
    return;
  }
  printf("Enter second vertex (1-%d): ", get_order(graph));
  if (scanf("%d", &vertex2) != 1) {
    printf("Invalid input!\n");
    while (getchar() != '\n');
    return;
  }
  if (vertex1 < 1 || vertex1 > get_order(graph) || vertex2 < 1 ||
      vertex2 > get_order(graph)) {
    printf("\n):\tInvalid vertices!\t:(\n");
    return;
  }
  my_timer_t timer;
  timer_start(&timer);
  int distance = get_shortest_path_between_vertices(
      graph, vertex1 - 1, vertex2 - 1);  // -1 for 0-based index
  double time_spent = timer_stop(&timer);
  if (distance == -1) {
    printf("No path exists between vertices %d and %d\n", vertex1, vertex2);
  } else {
    printf("________________________________________________\n");
    printf("Shortest path between %d and %d: %d\n", vertex1, vertex2, distance);
  }
  print_execution_time(time_spent);
}

void handle_all_shortest_paths(graph_t *graph) {
  if (graph == NULL || graph->adjacency == NULL) {
    printf("\n):\tGraph is not loaded!\t:(\n");
    return;
  }
  int size = get_order(graph);
  int **dist = (int **)malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) {
    dist[i] = (int *)malloc(size * sizeof(int));
  }
  my_timer_t timer;
  timer_start(&timer);
  int result_code = get_shortest_paths_between_all_vertices(graph, dist);
  double time_spent = timer_stop(&timer);
  if (result_code == 0) {
    printf("________________________________________________\n");
    printf("Shortest paths between all vertices:\n");
    printf("________________________________________________\n");
    print_matrix(dist, size);
  } else {
    printf("________________________________________________\n");
    printf("\n):\tError calculating shortest paths\t:(\n");
  }
  print_execution_time(time_spent);
  for (int i = 0; i < size; i++) {
    free(dist[i]);
  }
  free(dist);
}

void handle_mst(graph_t *graph) {
  if (graph == NULL || graph->adjacency == NULL) {
    printf("\n):\tGraph is not loaded!\t:(\n");
    return;
  }
  int size = get_order(graph);
  int **mst = (int **)malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) {
    mst[i] = (int *)malloc(size * sizeof(int));
  }
  my_timer_t timer;
  timer_start(&timer);
  int result_code = get_least_spanning_tree(graph, mst);
  double time_spent = timer_stop(&timer);
  if (result_code == 0) {
    printf("________________________________________________\n");
    printf("Minimum spanning tree adjacency matrix:\n");
    printf("________________________________________________\n");
    print_matrix(mst, size);
  } else {
    printf("________________________________________________\n");
    printf("\n):\tError calculating MST\t:(\n");
  }
  print_execution_time(time_spent);
  for (int i = 0; i < size; i++) {
    free(mst[i]);
  }
  free(mst);
}

void handle_tsp(graph_t *graph) {
  if (graph == NULL || graph->adjacency == NULL) {
    printf("\n):\tGraph is not loaded!\t:(\n");
    return;
  }
  const aco_params_t params = {.alpha_k = ALPHA_K,
                               .beta_k = BETA_K,
                               .initial_pheromone_k = PHEROMONE_K,
                               .q_k = Q_K,
                               .evaporation_k = EVAPORATION_K,
                               .min_pheromone_k = MIN_PHEROMONE_K,
                               .max_iterations = MAX_ITERATIONS_K};

  tsm_result_t *result = tsm_result_create();
  my_timer_t timer;
  timer_start(&timer);
  solve_traveling_salesman_problem(result, graph, &params);
  double time_spent = timer_stop(&timer);
  printf("\nTSP solution:\n");
  printf("________________________________________________\n");
  printf("Path: ");
  for (int i = 0; i < result->size; i++) {
    printf("%d ", result->vertices[i] + 1);  // +1 for 1-based output
  }
  printf("\nDistance: %lf\n", result->distance);
  print_execution_time(time_spent);
  tsm_result_delete(result);
}

int input_adjacency_matrix(graph_t **graph) {
  int size;
  printf("Enter the number of vertices (or 'q' to cancel): ");
  char input[10];
  if (scanf("%9s", input) != 1 || tolower(input[0]) == 'q') {
    return 0;
  }
  size = atoi(input);
  if (size <= 0) {
    printf("\n):\tInvalid size! Size must be positive integer.\t:(\n");
    return 0;
  }
  *graph = graph_create(size);
  if (*graph == NULL) {
    printf("\n):\tError creating graph structure!\t:(\n");
    return 0;
  }
  printf("Enter adjacency matrix (%dx%d, row by row):\n", size, size);
  printf("(Enter %d values for each row separated by spaces)\n", size);
  for (int i = 0; i < size; i++) {
    printf(" Row %d: ", i + 1);
    for (int j = 0; j < size; j++) {
      if (scanf("%d", &(*graph)->adjacency->data[i][j]) != 1) {
        printf("\n):\tInvalid input! Please enter integers only.\t:(\n");
        graph_delete(*graph);
        *graph = NULL;
        return 0;
      }
    }
  }
  for (int i = 0; i < size; i++) {
    if ((*graph)->adjacency->data[i][i] != 0) {
      printf("\n):\tWarning: Diagonal element [%d][%d] is not zero.\t:(\n", i,
             i);
    }
  }
  printf("Graph created successfully with %d vertices.\n", size);
  return 1;
}
char *get_current_directory() {
  static char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd))) {
    return cwd;
  } else {
    perror("getcwd() error");
    return NULL;
  }
}

int load_graph_from_file_improved(graph_t **graph) {
  char filename[PATH_MAX];
  char *cwd = get_current_directory();

  if (!cwd) {
    return 0;
  }

  printf("\nCurrent directory: %s\n", cwd);
  printf("Available files in current directory:\n");
  system("ls -p | grep -v /");  // Show only files (not directories)

  printf("\nEnter filename (or full path): ");
  if (scanf("%255s", filename) != 1) {
    printf("Invalid input!\n");
    return 0;
  }

  // Check if file exists
  if (access(filename, F_OK) == -1) {
    printf("File '%s' does not exist or is not accessible!\n", filename);
    return 0;
  }

  if (*graph != NULL) {
    graph_delete(*graph);
  }

  *graph = graph_create(0);
  if (!*graph) {
    printf("Error creating graph structure!\n");
    return 0;
  }

  if (load_graph_from_file(*graph, filename)) {
    printf("\nGraph loaded successfully from: %s\n", filename);
    printf("Graph order: %d\n", get_order(*graph));
    return 1;
  } else {
    printf("Error loading graph from file '%s'\n", filename);
    graph_delete(*graph);
    *graph = NULL;
    return 0;
  }
}
int load_graph(graph_t **graph) {
  char choice[10];
  printf("\nChoose input method:\n");
  printf("1. Load from file (improved)\n");
  printf("2. Enter adjacency matrix manually\n");
  printf("3. Return to main menu\n");
  printf("Your choice: ");

  if (scanf("%9s", choice) != 1) return 0;
  if (tolower(choice[0]) == 'q') return 0;

  switch (atoi(choice)) {
    case 1:
      return load_graph_from_file_improved(graph);
    case 2:
      if (*graph != NULL) graph_delete(*graph);
      return input_adjacency_matrix(graph);
    case 3:
      return 0;
    default:
      printf("Invalid choice!\n");
      return 0;
  }
}
void handle_export_to_dot(graph_t *graph) {
  if (graph == NULL || graph->adjacency == NULL) {
    printf("\n):\tGraph is not loaded!\t:(\n");
    return;
  }
  char filename[256];
  printf("Enter filename to save DOT file (e.g., graph.dot): ");
  if (scanf("%255s", filename) != 1) {
    printf("\n):\tInvalid filename!\t:(\n");
    return;
  }
  export_graph_to_dot(graph, filename);
  printf("Graph successfully exported to %s\n", filename);
}

bool handle_load_new_graph(graph_t **graph) {
  if (load_graph(graph)) {
    return true;
  }
  return false;
}

void display_algorithms_menu(void) {
  printf("\nGraph Algorithms Menu\n");
  printf("1. Breadth First Search (BFS)\n");
  printf("2. Depth First Search (DFS)\n");
  printf("3. Shortest path between two vertices\n");
  printf("4. Shortest paths between all vertices\n");
  printf("5. Minimum spanning tree\n");
  printf("6. Traveling Salesman Problem (TSP)\n");
  printf("7. How to visualie my graph?\n");
  printf("8. Export graph to DOT file\n");
  printf("9. Load different graph\n");
  printf("Choose an option (or 'q' to exit): ");
}

void process_user_choice(int choice, graph_t **graph) {
  switch (choice) {
    case 1:
      handle_bfs(*graph);
      break;
    case 2:
      handle_dfs(*graph);
      break;
    case 3:
      handle_shortest_path(*graph);
      break;
    case 4:
      handle_all_shortest_paths(*graph);
      break;
    case 5:
      handle_mst(*graph);
      break;
    case 6:
      handle_tsp(*graph);
      break;
    case 7:
      handle_how_to_visualize_graph(*graph);
      break;
    case 8:
      handle_export_to_dot(*graph);
      break;
    case 9:
      if (!handle_load_new_graph(graph)) {
        return;
      }
      break;
    default:
      printf("\nInvalid choice. Try again.\n");
  }
}

void show_algorithms_menu(graph_t *graph) {
  char input[10];
  graph_t *current_graph = graph;
  while (1) {
    display_algorithms_menu();
    if (scanf("%9s", input) != 1) continue;
    if (tolower(input[0]) == 'q') {
      if (current_graph) graph_delete(current_graph);
      exit(0);
    }
    process_user_choice(atoi(input), &current_graph);
  }
}

int main(void) {
  graph_t *graph = NULL;
  char input[10];
  printf("Graph Algorithms Application\n");
  while (1) {
    printf("\nMain Menu\n");
    printf("1. Load/input graph\n");
    printf("2. Exit\n");
    printf("Choose an option: ");
    if (scanf("%9s", input) != 1) continue;
    if (tolower(input[0]) == 'q' || atoi(input) == 2) {
      if (graph) graph_delete(graph);
      printf("Exiting...\n");
      break;
    }
    if (atoi(input) == 1) {
      if (load_graph(&graph)) {
        show_algorithms_menu(graph);
      }
    } else {
      printf("\n):\tInvalid choice. Try again.\t:(\n");
    }
  }
  return 0;
}

#ifdef __cplusplus
}
#endif
