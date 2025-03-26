#include <stdio.h>
#include <stdlib.h>
#include "model.h"

// This file tests the linear regression model on a fixed dataset.
// It calculates the weights using the normal equation and tests prediction accuracy.

int main() {
    int num_samples = 4;
    int num_features = 3;

    // Allocate and fill raw input and output data arrays using helper function
    long double **input_data = allocate_2d_array(num_samples, num_features);
    long double **output_data = allocate_2d_array(num_samples, 1);

    long double raw_inputs[4][3] = {
        {1, 2, 3},
        {1, 3, 5},
        {1, 1, 1},
        {1, 4, 6}
    };

    long double raw_outputs[4][1] = {
        {5}, {8}, {2}, {10}
    };

    for (int i = 0; i < num_samples; i++) {
        for (int j = 0; j < num_features; j++) {
            input_data[i][j] = raw_inputs[i][j];
        }
        output_data[i][0] = raw_outputs[i][0];
    }

    // Allocate and fill matrices
    matrix X = allocate_matrix(num_samples, num_features);
    matrix Y = allocate_matrix(num_samples, 1);
    fill_input_output(X, Y, input_data, output_data);

    // Train model: calculate weights using normal equation
    matrix W = weights(X, Y);
    LRmodel model = {W, num_features, true};

    // Define a test input to predict output
    long double input_predict[1][3] = {{1, 5, 9}};
    matrix input_matrix = allocate_matrix(1, num_features);
    for (int i = 0; i < num_features; i++) {
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
    for (int i = 0; i < num_samples; i++) {
        free(input_data[i]);
        free(output_data[i]);
    }
    free(input_data);
    free(output_data);

    return 0;
}
