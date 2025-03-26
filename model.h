#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>

typedef struct {
    long double **array;
    int rows;
    int cols;
} matrix;

typedef struct {
    matrix weights;
    int features;
    bool yintercept;
} LRmodel;

matrix transpose(matrix);
matrix multiply(matrix, matrix);
matrix inverse(matrix);
matrix weights(matrix, matrix);
long double runModel(matrix, LRmodel, matrix);
void free_matrix(matrix);
matrix allocate_matrix(int rows, int cols);
long double **allocate_2d_array(int rows, int cols);
void fill_input_output(matrix X, matrix Y, long double **input_data, long double **output_data);

#endif
