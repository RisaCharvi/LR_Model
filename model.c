#include <stdlib.h>
#include <stdio.h>
#include "model.h"

matrix transpose(matrix data) {
    matrix result;
    result.rows = data.cols;
    result.cols = data.rows;

    result.array = (long double **)malloc(result.rows * sizeof(long double *));
    for (int i = 0; i < result.rows; i++) {
        result.array[i] = (long double *)malloc(result.cols * sizeof(long double));
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
    result.array = (long double **)malloc(result.rows * sizeof(long double *));

    for (int i = 0; i < result.rows; i++) {
        result.array[i] = (long double *)malloc(result.cols * sizeof(long double));
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
    result.array = (long double **)malloc(n * sizeof(long double *));
    for (int i = 0; i < n; i++) {
        result.array[i] = (long double *)calloc(n, sizeof(long double));
    }

    long double **aug = (long double **)malloc(n * sizeof(long double *));
    for (int i = 0; i < n; i++) {
        aug[i] = (long double *)malloc(2 * n * sizeof(long double));
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
    m.array = NULL;
    m.rows = 0;
    m.cols = 0;
}

