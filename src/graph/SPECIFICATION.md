# Graph Module Specification

## Overview
The Graph module provides functionality to create, manipulate, and visualize graph data structures. It includes operations for graph creation/deletion, file I/O, and DOT format export for visualization.

## Data Structures

### `matrix_t`
Represents an adjacency matrix for graph storage.

**Fields:**
- `int **data`: 2D array storing matrix values
- `int size`: Dimension of the square matrix

### `graph_t`
Main graph structure containing adjacency matrix.

**Fields:**
- `matrix_t *adjacency`: Pointer to adjacency matrix

## Functions

### Graph Creation/Deletion

#### `graph_t* graph_create(int size)`
Creates a new graph with specified size.

**Parameters:**
- `size`: Number of vertices in graph

**Returns:**
- Pointer to new graph on success
- NULL on memory allocation failure

#### `void graph_delete(graph_t* graph)`
Frees all memory associated with a graph.

**Parameters:**
- `graph`: Graph to delete

### Graph Properties

#### `int get_order(graph_t* graph)`
Gets the number of vertices in the graph.

**Parameters:**
- `graph`: Target graph

**Returns:**
- Number of vertices (order) on success
- -1 if graph is NULL or invalid

### File Operations

#### `bool load_graph_from_file(graph_t* graph, const char* filename)`
Loads graph data from a text file.

**File Format:**
1. First line: integer N (number of vertices)
2. Next N lines: N space-separated integers representing adjacency matrix

**Parameters:**
- `graph`: Graph structure to populate
- `filename`: Path to input file

**Returns:**
- true on successful load
- false on any error (file access, invalid format, memory allocation)

### Visualization

#### `void export_graph_to_dot(const graph_t* graph, const char* filename)`
Exports graph to DOT format for visualization with Graphviz.

**Output Features:**
- Directed graph (digraph) representation
- Edge weights as labels
- Custom styling for readability
- Bidirectional edges shown as separate arrows

**Parameters:**
- `graph`: Graph to export
- `filename`: Output file path

## Error Handling
- Functions return NULL or false on failure
- Memory allocation failures are handled gracefully
- File operations include validation checks

## Dependencies
- Standard C library (stdlib.h, stdio.h)
- Matrix module for underlying storage

## Usage Example
```c
graph_t *g = graph_create(5);
if (load_graph_from_file(g, "graph.txt")) {
    export_graph_to_dot(g, "graph.dot");
    printf("Graph order: %d\n", get_order(g));
}
graph_delete(g);
```