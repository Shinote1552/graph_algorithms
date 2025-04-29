#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

int **allocate_matrix(int size);
void free_matrix(int **matrix, int size);
double **allocate_matrix_double(int size);
double **allocate_matrix_double_with_value(int size, double value);
void free_matrix_double(double **matrix, int size);

#ifdef __cplusplus
}
#endif

#endif  // S21_MATRIX_H
