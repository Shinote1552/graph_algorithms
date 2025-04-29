#include <fstream>

#include "../../test/main_test.h"
#include "wrapper_for_gtest/graph_wrapper.h"

TEST(GraphTest, CreateGraphTest1) {
  GraphWrapper graph;
  EXPECT_NO_THROW(graph.createGraph(5));
  EXPECT_EQ(graph.getOrder(), 5);
}

TEST(GraphTest, LoadGraphFromFileTest1) {
  GraphWrapper graph;
  EXPECT_TRUE(graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/graph_examples.txt"));
}

TEST(GraphTest, LoadGraphFromFileTest2) {
  GraphWrapper graph;
  EXPECT_TRUE(graph.loadGraphFromFile(
      "../datasets/incidence_matrix_src/simple_graph.txt"));
}
TEST(LoadGraphTxtTest, LoadAndCheckGraphFromFile1) {
  const int kExpectedSize = 4;
  const int kExpectedValueAtPosition = 20;
  const std::string kInputFile =
      "../datasets/incidence_matrix_src/simple_graph.txt";

  GraphWrapper graph;
  EXPECT_TRUE(graph.loadGraphFromFile(kInputFile))
      << "Failed to load graph from file: " << kInputFile;

  EXPECT_EQ(graph.getOrder(), kExpectedSize) << "Graph size mismatch.";
  EXPECT_EQ(graph.getMatrixValue(3, 1), kExpectedValueAtPosition)
      << "Value at position [3][1] mismatch.";
}

TEST(LoadGraphTxtTest, LoadAndCheckGraphFromFile2) {
  const int kExpectedSize = 11;
  const int kExpectedValueAtPosition = 31;
  const std::string kInputFile =
      "../datasets/incidence_matrix_src/graph_examples.txt";

  GraphWrapper graph;
  EXPECT_TRUE(graph.loadGraphFromFile(kInputFile))
      << "Failed to load graph from file: " << kInputFile;

  EXPECT_EQ(graph.getOrder(), kExpectedSize) << "Graph size mismatch.";
  EXPECT_EQ(graph.getMatrixValue(0, 5), kExpectedValueAtPosition)
      << "Value at position [0][5] mismatch.";
}

TEST(LoadGraphTxtTest, LoadAndCheckGraphFromFile3) {
  const std::string kNonExistentFile =
      "../datasets/incidence_matrix_src/non_existing_file.txt";

  GraphWrapper graph;

  bool result = graph.loadGraphFromFile(kNonExistentFile);

  EXPECT_FALSE(result)
      << "Expected load_graph_from_file to fail for non-existent file: "
      << kNonExistentFile;
}

TEST(ExportGraphToDotTest, ExportSimpleGraph1) {
  const std::string kInputFile =
      "../datasets/incidence_matrix_src/graph_examples.txt";
  const std::string kOutputFile =
      "../data-samples/dot_structs/graph_examples.dot";

  GraphWrapper graph;
  EXPECT_TRUE(graph.loadGraphFromFile(kInputFile))
      << "Failed to load graph from file: " << kInputFile;

  graph.exportGraphToDot(kOutputFile);

  std::ifstream file(kOutputFile);
  ASSERT_TRUE(file.is_open())
      << "Failed to open exported DOT file: " << kOutputFile;
}

TEST(ExportGraphToDotTest, ExportSimpleGraph2) {
  const std::string kInputFile =
      "../datasets/incidence_matrix_src/simple_graph.txt";
  const std::string kOutputFile =
      "../data-samples/dot_structs/test_output1.dot";

  GraphWrapper graph;
  EXPECT_TRUE(graph.loadGraphFromFile(kInputFile))
      << "Failed to load graph from file: " << kInputFile;

  graph.exportGraphToDot(kOutputFile);

  std::ifstream file(kOutputFile);
  ASSERT_TRUE(file.is_open())
      << "Failed to open exported DOT file: " << kOutputFile;
}
TEST(ExportGraphToDotTest, ExportSimpleGraph3) {
  const std::string kInputFile =
      "../datasets/incidence_matrix_src/test_graph.txt";
  const std::string kOutputFile =
      "../data-samples/dot_structs/test_output2.dot";

  GraphWrapper graph;
  EXPECT_TRUE(graph.loadGraphFromFile(kInputFile))
      << "Failed to load graph from file: " << kInputFile;

  graph.exportGraphToDot(kOutputFile);

  std::ifstream file(kOutputFile);
  ASSERT_TRUE(file.is_open())
      << "Failed to open exported DOT file: " << kOutputFile;
}
