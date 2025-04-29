#include "matrix.h"

int **allocate_matrix(int size) {
  int **matrix = NULL;
  bool success = true;

  matrix = (int **)malloc(size * sizeof(int *));
  if (!matrix) {
    success = false;
  }

  for (int i = 0; i < size && success; i++) {
    matrix[i] = (int *)calloc(size, sizeof(int));
    if (!matrix[i]) {
      success = false;
      for (int j = 0; j < i; j++) {
        free(matrix[j]);
      }
    }
  }

  if (!success) {
    if (matrix) {
      free(matrix);
    }
    matrix = NULL;
  }

  return matrix;
}

double **allocate_matrix_double(int size) {
  double **matrix = NULL;
  bool success = true;

  matrix = (double **)malloc(size * sizeof(double *));
  if (!matrix) {
    success = false;
  }

  for (int i = 0; i < size && success; i++) {
    matrix[i] = (double *)calloc(size, sizeof(double));
    if (!matrix[i]) {
      success = false;
      for (int j = 0; j < i; j++) {
        free(matrix[j]);
      }
    }
  }

  if (!success) {
    if (matrix) {
      free(matrix);
    }
    matrix = NULL;
  }

  return matrix;
}

double **allocate_matrix_double_with_value(int size, double value) {
  double **matrix = allocate_matrix_double(size);
  if (matrix) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        matrix[i][j] = value;
      }
    }
  }
  return matrix;
}

void free_matrix_double(double **matrix, int size) {
  if (matrix) {
    for (int i = 0; i < size; i++) {
      if (matrix[i]) {
        free(matrix[i]);
      }
    }
    free(matrix);
  }
}

void free_matrix(int **matrix, int size) {
  if (matrix) {
    for (int i = 0; i < size; i++) {
      if (matrix[i]) {
        free(matrix[i]);
      }
    }
    free(matrix);
  }
}
