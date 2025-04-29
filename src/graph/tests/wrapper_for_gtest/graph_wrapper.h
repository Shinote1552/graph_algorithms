#ifndef GRAPH_WRAPPER_H
#define GRAPH_WRAPPER_H

#include <iostream>
#include <string>

#include "../../s21_graph.h"

/**
 * @brief Class for testing/using graph in c++ with c realization
 */
class GraphWrapper {
 public:
  GraphWrapper();
  ~GraphWrapper();

  int size();
  void createGraph(int size);
  int getOrder() const;
  int getMatrixValue(int i, int j) const;
  bool loadGraphFromFile(const std::string& filename);
  void exportGraphToDot(const std::string& filename) const;
  void PrintGraphIncidenceMatrix();
  graph_t* getGraph() const;

 private:
  graph_t* graph_;
};

#endif  // GRAPH_WRAPPER_H
