#include <stdio.h>
#include <stdlib.h>
#include "model.h"

// This file tests the linear regression model on a fixed dataset.
// It calculates the weights using the normal equation and tests prediction accuracy.

int main() {
    // Define input features (X) with 4 examples and 3 features (including bias term 1)
    long double input_data[4][3] = {
        {1, 2, 3},
        {1, 3, 5},
        {1, 1, 1},
        {1, 4, 6}
    };

    // Define output values (Y) for each input example
    long double output_data[4][1] = {
        {5}, {8}, {2}, {10}
    };

    // Allocate and fill matrix X (4 rows, 3 columns)
    matrix X = {malloc(4 * sizeof(long double *)), 4, 3};
    // Allocate and fill matrix Y (4 rows, 1 column)
    matrix Y = {malloc(4 * sizeof(long double *)), 4, 1};

    for (int i = 0; i < 4; i++) {
        X.array[i] = malloc(3 * sizeof(long double));
        Y.array[i] = malloc(sizeof(long double));
        for (int j = 0; j < 3; j++) {
            X.array[i][j] = input_data[i][j];
        }
        Y.array[i][0] = output_data[i][0];
    }

    // Train model: calculate weights using normal equation
    matrix W = weights(X, Y);
    LRmodel model = {W, 3, true};

    // Define a test input to predict output
    long double input_predict[1][3] = {{1, 5, 9}};
    matrix input_matrix = {malloc(sizeof(long double *)), 1, 3};
    input_matrix.array[0] = malloc(3 * sizeof(long double));
    for (int i = 0; i < 3; i++) {
        input_matrix.array[0][i] = input_predict[0][i];
    }

    // Predict output for the test input using the trained model
    long double prediction = runModel(W, model, input_matrix);
    printf("Prediction for [1, 5, 9]: %Lf\n", prediction);

    // Display the learned weights
    printf("Learned Weights:\n");
    for (int i = 0; i < W.rows; i++) {
        for (int j = 0; j < W.cols; j++) {
            printf("%Lf ", W.array[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    free_matrix(X);
    free_matrix(Y);
    free_matrix(W);
    free_matrix(input_matrix);

    return 0;
}
