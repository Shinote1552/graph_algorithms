#include "graph_wrapper.h"

#include <stdexcept>

GraphWrapper::GraphWrapper() : graph_(nullptr) {}

bool GraphWrapper::loadGraphFromFile(const std::string& filename) {
  if (!graph_) {
    graph_ = graph_create(0);
  }
  return load_graph_from_file(graph_, filename.c_str());
}

GraphWrapper::~GraphWrapper() {
  if (graph_) {
    graph_delete(graph_);
  }
}

void GraphWrapper::createGraph(int size) {
  if (graph_) {
    graph_delete(graph_);
  }
  graph_ = graph_create(size);
  if (!graph_) {
    throw std::runtime_error("Failed to create graph");
  }
}
int GraphWrapper::getOrder() const {
  if (!graph_) {
    throw std::runtime_error("Graph is not initialized");
  }
  return get_order(graph_);
}

int GraphWrapper::getMatrixValue(int i, int j) const {
  if (!graph_ || !graph_->adjacency || !graph_->adjacency->data) {
    throw std::runtime_error("Graph is not initialized");
  }
  if (i < 0 || i >= graph_->adjacency->size || j < 0 ||
      j >= graph_->adjacency->size) {
    throw std::out_of_range("Invalid matrix indices");
  }
  return graph_->adjacency->data[i][j];
}

void GraphWrapper::exportGraphToDot(const std::string& filename) const {
  if (!graph_) {
    throw std::runtime_error("Graph is not initialized");
  }
  export_graph_to_dot(graph_, filename.c_str());
}

void GraphWrapper::PrintGraphIncidenceMatrix() {
  for (int i = 0; i < graph_->adjacency->size; i++) {
    for (int n = 0; n < graph_->adjacency->size; n++) {
      std::cout << graph_->adjacency->data[i][n] << " ";
    }
    std::cout << std::endl;
  }
}
int GraphWrapper::size() { return graph_->adjacency->size; }

graph_t* GraphWrapper::getGraph() const {
  if (!graph_) {
    throw std::runtime_error("Graph is not initialized");
  }
  return graph_;
}
