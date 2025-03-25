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


#endif
