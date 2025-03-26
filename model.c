#include <stdlib.h>
#include <stdio.h>
#include "model.h"

matrix transpose(matrix data) {
    matrix result;
    result.rows = data.cols;
    result.cols = data.rows;

    result.array = allocate_2d_array(result.rows, result.cols);
    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            result.array[i][j] = data.array[j][i];
        }
    }

    return result;
}

matrix multiply(matrix A, matrix B) {
    if (A.cols != B.rows) {
        fprintf(stderr, "Matrix multiplication error: incompatible dimensions\n");
        exit(1);
    }

    matrix result;
    result.rows = A.rows;
    result.cols = B.cols;
    result.array = allocate_2d_array(result.rows, result.cols);

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            result.array[i][j] = 0.0;
            for (int k = 0; k < A.cols; k++) {
                result.array[i][j] += A.array[i][k] * B.array[k][j];
            }
        }
    }

    return result;
}

matrix inverse(matrix data) {
    int n = data.rows;
    if (n != data.cols) {
        matrix empty = {NULL, 0, 0};
        return empty;
    }

    matrix result;
    result.rows = result.cols = n;
    result.array = allocate_2d_array(n, n);

    long double **aug = allocate_2d_array(n, 2 * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug[i][j] = data.array[i][j];
        }
        for (int j = n; j < 2 * n; j++) {
            aug[i][j] = (i == j - n) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < n; i++) {
        long double pivot = aug[i][i];
        if (pivot == 0.0) {
            fprintf(stderr, "Matrix is singular and cannot be inverted.\n");
            exit(1);
        }

        for (int j = 0; j < 2 * n; j++) {
            aug[i][j] /= pivot;
        }

        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            long double factor = aug[k][i];
            for (int j = 0; j < 2 * n; j++) {
                aug[k][j] -= factor * aug[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result.array[i][j] = aug[i][j + n];
        }
        free(aug[i]);
    }
    free(aug);

    return result;
}

matrix weights(matrix inputs, matrix outputs) {
    matrix Xt = transpose(inputs);
    matrix XtX = multiply(Xt, inputs);
    matrix XtX_inv = inverse(XtX);
    matrix XtY = multiply(Xt, outputs);
    return multiply(XtX_inv, XtY);
}

long double runModel(matrix weight, LRmodel model, matrix input) {
    long double prediction = 0.0;
    for (int i = 0; i < model.features; i++) {
        prediction += weight.array[i][0] * input.array[0][i];
    }
    return prediction;
}

void free_matrix(matrix m) {
    if (m.array == NULL) return;
    for (int i = 0; i < m.rows; i++) {
        free(m.array[i]);
    }
    free(m.array);
}

matrix allocate_matrix(int rows, int cols) {
    matrix m;
    m.rows = rows;
    m.cols = cols;
    m.array = allocate_2d_array(rows, cols);
    return m;
}

long double **allocate_2d_array(int rows, int cols) {
    long double **array = (long double **)malloc(rows * sizeof(long double *));
    for (int i = 0; i < rows; i++) {
        array[i] = (long double *)malloc(cols * sizeof(long double));
    }
    return array;
}

void fill_input_output(matrix X, matrix Y, long double **input_data, long double **output_data) {
    for (int i = 0; i < X.rows; i++) {
        for (int j = 0; j < X.cols; j++) {
            X.array[i][j] = input_data[i][j];
        }
        Y.array[i][0] = output_data[i][0];
    }
}
