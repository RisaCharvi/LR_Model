#include <stdio.h>
#include <stdlib.h>
#include "model.h"

int main() {
    // Training data: 3 samples, 3 features (e.g. [1, x1, x2])
    long double input_data[4][3] = {
        {1, 2, 3},
        {1, 3, 5},
        {1, 1, 1},
        {1, 4, 6}
    };
    long double output_data[4][1] = {
        {5}, {8}, {2}, {10}
    };

    // Allocate memory for input/output matrices
    matrix X = {malloc(3 * sizeof(long double *)), 4, 3};
    matrix Y = {malloc(3 * sizeof(long double *)), 4, 1};

    for (int i = 0; i < 4; i++) {
        X.array[i] = malloc(3 * sizeof(long double));
        Y.array[i] = malloc(sizeof(long double));
        for (int j = 0; j < 3; j++) {
            X.array[i][j] = input_data[i][j];
        }
        Y.array[i][0] = output_data[i][0];
    }

    // Train
    matrix W = weights(X, Y);
    LRmodel model = {W, 3, true};

    // Predict for new input: [1, 5, 9]
    long double input_predict[1][3] = {{1, 5, 9}};
    matrix input_matrix = {malloc(sizeof(long double *)), 1, 3};
    input_matrix.array[0] = malloc(3 * sizeof(long double));
    for (int i = 0; i < 3; i++) {
        input_matrix.array[0][i] = input_predict[0][i];
    }

    long double prediction = runModel(W, model, input_matrix);
    printf("Prediction for [1, 5, 9]: %Lf\n", prediction);

    free_matrix(X);
    free_matrix(Y);
    free_matrix(W);
    free_matrix(input_matrix);

    return 0;

    
}
