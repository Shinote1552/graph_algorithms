#include "s21_graph.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief create graph
 * @param size Size of graph
 * @return Pointer to graph or NULL if error
 */
graph_t* graph_create(int size) {
  graph_t* graph = NULL;
  bool success = true;
  graph = (graph_t*)calloc(1, sizeof(graph_t));
  if (!graph) {
    success = false;
  }
  if (success) {
    graph->adjacency = (matrix_t*)calloc(1, sizeof(matrix_t));
    if (!graph->adjacency) {
      success = false;
    }
  }
  if (success) {
    graph->adjacency->size = size;
    graph->adjacency->data = allocate_matrix(size);
    if (!graph->adjacency->data) {
      success = false;
    } else {
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          graph->adjacency->data[i][j] = 0;
        }
      }
    }
  }
  if (!success) {
    if (graph) {
      if (graph->adjacency) {
        if (graph->adjacency->data) {
          free_matrix(graph->adjacency->data, graph->adjacency->size);
        }
        free(graph->adjacency);
      }
      free(graph);
    }
    graph = NULL;
  }
  return graph;
}

/**
 * @brief delete graph
 * @param graph Pointer to graph
 * @return void
 */
void graph_delete(graph_t* graph) {
  if (graph) {
    if (graph->adjacency) {
      free_matrix(graph->adjacency->data, graph->adjacency->size);
      free(graph->adjacency);
    }
    free(graph);
  }
}

/**
 * @brief get order of graph
 * @param graph Pointer to graph
 * @return int order or error = -1
 */
int get_order(graph_t* graph) {
  if (!graph || !graph->adjacency) {
    return -1;
  }
  return graph->adjacency->size;
}

static bool prepare_graph_structure(graph_t* graph, int size) {
  // Clean up existing matrix if size doesn't match
  if (graph->adjacency && graph->adjacency->size != size) {
    free_matrix(graph->adjacency->data, graph->adjacency->size);
    free(graph->adjacency);
    graph->adjacency = NULL;
  }

  // Allocate new matrix if needed
  if (!graph->adjacency) {
    graph->adjacency = (matrix_t*)malloc(sizeof(matrix_t));
    if (!graph->adjacency) {
      return false;
    }

    graph->adjacency->size = size;
    graph->adjacency->data = allocate_matrix(size);
    if (!graph->adjacency->data) {
      free(graph->adjacency);
      graph->adjacency = NULL;
      return false;
    }
  }
  return true;
}

static void cleanup_on_failure(graph_t* graph) {
  if (graph->adjacency) {
    free_matrix(graph->adjacency->data, graph->adjacency->size);
    free(graph->adjacency);
    graph->adjacency = NULL;
  }
}

/**
 * @brief load graph from file, can allocate memory for new graph
 * if graph matrix is NULL pointer is null
 * @param graph Pointer to graph
 * @param filename Name of file
 * @return true if success false if error
 */
bool load_graph_from_file(graph_t* graph, const char* filename) {
  if (!graph || !filename) {
    fprintf(stderr, "Invalid input parameters\n");
    return false;
  }
  FILE* file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Failed to open file: %s\n", filename);
    return false;
  }
  int size = 0;
  if (fscanf(file, "%d", &size) != 1 || size <= 0) {
    fclose(file);
    fprintf(stderr, "Invalid graph size in file\n");
    return false;
  }
  if (!prepare_graph_structure(graph, size)) {
    fclose(file);
    fprintf(stderr, "Failed to prepare graph structure\n");
    return false;
  }
  bool success = true;
  for (int i = 0; i < size && success; i++) {
    for (int j = 0; j < size && success; j++) {
      if (fscanf(file, "%d", &graph->adjacency->data[i][j]) != 1) {
        success = false;
      }
    }
  }
  fclose(file);
  if (!success) {
    cleanup_on_failure(graph);
    fprintf(stderr, "Error reading matrix data from file\n");
  }
  return success;
}

static void initialize_dot_file(FILE* file) {
  fprintf(file, "digraph {\n");
  fprintf(file, "    bgcolor=\"lightgray\";\n");
  fprintf(file, "    rankdir=LR;\n");
  fprintf(file, "    size=\"8,5\";\n");
  fprintf(file, "    node [shape=circle];\n");
  fprintf(file, "    overlap=false;\n");
  fprintf(file, "    splines=true;\n");
  fprintf(file, "    nodesep=4.0;\n");
  fprintf(file, "    ranksep=3.0;\n");
  fprintf(file, "    edge [fontsize=24, fontname=\"Arial\"];\n");
  fprintf(file, "    node [fontsize=24, fontname=\"Arial\"];\n");
}

static void write_edge(FILE* file, int i, int j, int weight_ij, int weight_ji) {
  if (weight_ij != 0 && weight_ji != 0) {
    fprintf(file, "    %d -> %d [label=\"%d\"];\n", i, j, weight_ij);
    fprintf(file, "    %d -> %d [label=\"%d\"];\n", j, i, weight_ji);
  } else if (weight_ij != 0) {
    fprintf(file, "    %d -> %d [label=\"%d\"];\n", i, j, weight_ij);
  } else if (weight_ji != 0) {
    fprintf(file, "    %d -> %d [label=\"%d\"];\n", j, i, weight_ji);
  }
}

/**
 * @brief Export graph to DOT file
 * @param graph Pointer to graph
 * @param filename Path to file
 */
void export_graph_to_dot(const graph_t* graph, const char* filename) {
  bool success = true;
  if (!graph || !filename) {
    success = false;
  }
  FILE* file = NULL;
  if (success) {
    file = fopen(filename, "w");
    if (!file) {
      success = false;
    }
  }
  if (success) {
    initialize_dot_file(file);
    for (int i = 0; i < graph->adjacency->size; i++) {
      for (int j = i + 1; j < graph->adjacency->size; j++) {
        if (graph->adjacency->data[i][j] != 0 ||
            graph->adjacency->data[j][i] != 0) {
          write_edge(file, i, j, graph->adjacency->data[i][j],
                     graph->adjacency->data[j][i]);
        }
      }
    }
    fprintf(file, "}\n");
  }
  if (file) {
    fclose(file);
  }
}
