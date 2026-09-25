#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_random_matrix(int rows, int cols, int *matrix) {
     for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // this stores the random value in the matrix at the correct position as flattened 1D array.
            matrix[i * cols + j] = rand();
        }
    }
}

void multiply_matrices(int rows1, int cols1, int *matrix1,
                       int rows2, int cols2, int *matrix2,
                       int *result) {
    // Check if the matrices can be multiplied based on their dimensions. 
    // number of columns in the first matrix must equal the number of rows in the second matrix.
    if (cols1 != rows2) {
        printf("Cannot multiply matrices: cols1 must equal rows2.\n");
        return;
    }

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            // Initialize the result matrix element to 0 before summing the products.
            result[i * cols2 + j] = 0;
            for (int k = 0; k < cols1; k++) {
                // Multiply the corresponding elements and add to the result matrix element.
                result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }   
}

void display_matrix(int rows, int cols, int *matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }   
}

float do_job(int rows1, int cols1, int cols2, int forever) {

    // Determine the number of rows in the second matrix based on the number of columns in the first matrix.
    int rows2 = cols1;

    int *matrix1 = malloc(rows1 * cols1 * sizeof(int));
    int *matrix2 = malloc(rows2 * cols2 * sizeof(int));
    int *result = malloc(rows1 * cols2 * sizeof(int));

    if (matrix1 == NULL || matrix2 == NULL || result == NULL) {
        free(matrix1);
        free(matrix2);
        free(result);
        // Memory allocation failed, return early.
        return -1.0;
    }

    printf("Generating Matrices...\n");
    generate_random_matrix(rows1, cols1, matrix1);
    printf("Matrix 1 done.\n");

    generate_random_matrix(rows2, cols2, matrix2);
    printf("Matrix 2 done.\n");

    struct timespec t0, t1;

    timespec_get(&t0, TIME_UTC);  // C11 feature

    if (forever) {
        while (1) {
            multiply_matrices(rows1, cols1, matrix1, rows2, cols2, matrix2, result);
        }
    } else {
        multiply_matrices(rows1, cols1, matrix1, rows2, cols2, matrix2, result);
    }

    timespec_get(&t1, TIME_UTC);  // C11 feature

    // nano seconds elapsed converted to fractional seconds
    float dns = (float)(t1.tv_nsec - t0.tv_nsec) / 1000000000;
    // seconds elapsed
    float ds = (float)(t1.tv_sec - t0.tv_sec);

    float total_time = dns+ds;

    free(matrix1);
    free(matrix2);
    free(result);

    return total_time;
   
}

