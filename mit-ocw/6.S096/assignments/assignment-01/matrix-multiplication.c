// MIT OCW 6.S096
// Assignment 1, Problem 2-3: Matrix Multiplication 1-2 (matrix1-2)
// I've used dynamic memory allocation in both approaches

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

// default entries
static const char *input = "p2-input.txt";
static const char *output = "p2-output.txt";

typedef struct {
    size_t M, N;
    int **data;
} Matrix;

Matrix *read_matrix(FILE  *input_f);
void write_matrix(FILE *output_f, Matrix *m);
void free_matrix(Matrix *matrix);
void print_matrix(Matrix *matrix);
Matrix *multiply_matrices(Matrix *m1, Matrix *m2);

int main(int argc, char **argv) {
    FILE *input_f = NULL, *output_f = NULL;
    if (argc == 3) {
        input_f = fopen(argv[1], "r"); output_f = fopen(argv[2], "w");
        if (!input_f) {
            fprintf(stderr, "Error opening file: %s\nUsing default path", argv[1]);
            input_f = fopen(input, "r");
        }
        if (!output_f) {
            fprintf(stderr, "Error opening file: %s\nUsing default path", argv[1]);
            output_f = fopen(output, "w");
        }
    } else {
        printf("Usage: <binary> <input-file> <output-file>\nUsing default paths: %s, %s.\n", input, output);
        input_f = fopen(input, "r"); output_f = fopen(output, "w");
    }

    Matrix *m1 = read_matrix(input_f), *m2 = read_matrix(input_f);
    Matrix *m = multiply_matrices(m1, m2);

#if DEBUG
    print_matrix(m1);
    printf("\n");
    print_matrix(m2);
    printf("\n");
    printf("%zu %zu\n", m->M, m->N);
    print_matrix(m);
#else
    write_matrix(output_f, m);
#endif

    free_matrix(m1); free_matrix(m2);
    fclose(input_f); fclose(output_f);
    return 0;
}

Matrix *multiply_matrices(Matrix *m1, Matrix *m2) {
    if (m1->N != m2->M) {
        fprintf(stderr, "Number of columns in the first matrix must be equal to the number of rows in the second matrix!\n");
        return NULL;
    }
    
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    if (!m) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    m->M = m1->M; m->N = m2->N;
    m->data = (int **)malloc(m->M * sizeof(int *));
    if (!m->data) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < m->M; ++i) {
        m->data[i] = (int *)calloc(m->N, sizeof(int));
        if (!m->data[i]) {
            perror("memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }

    for (size_t y = 0; y < m->M; ++y) {
        for (size_t x = 0; x < m->N; ++x) {
            for (size_t k = 0; k < m1->N; ++k) {
                m->data[y][x] += m1->data[y][k] * m2->data[k][x];
            }
        }
    }

    return m;
}

void write_matrix(FILE *output_f, Matrix *m) {
    if (!output_f) {
        fprintf(stderr, "Given file is not valid!\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(output_f, "%zu %zu\n", m->M, m->N);

    for (size_t y = 0; y < m->M; ++y) {
        for (size_t x = 0; x < m->N; ++x) {
            fprintf(output_f, "%d ", m->data[y][x]);
        }
        fprintf(output_f, "\n");
    }
}

Matrix *read_matrix(FILE  *input_f) {
    if (!input_f) {
        perror("File not valid");
        exit(EXIT_FAILURE);
    }

    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (!matrix) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    if (fscanf(input_f, "%zu %zu", &matrix->M, &matrix->N) != 2) {
        fprintf(stderr, "Failed to read M and N of the input matrix!\n");
        exit(EXIT_FAILURE);
    }
    matrix->data = (int **)malloc(sizeof(int *) * matrix->M);
    if (!matrix->data) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < matrix->M; ++i) {
        matrix->data[i] = (int *)malloc(sizeof(int) * matrix->N);
        if (!matrix->data[i]) {
            perror("memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }
    
    for (size_t y = 0; y < matrix->M; ++y) {
        for (size_t x = 0; x < matrix->N; ++x) {
            if (fscanf(input_f, "%d", &matrix->data[y][x]) != 1) {
                fprintf(stderr, "Failed to read the number!\n");
                exit(EXIT_FAILURE);
            }
        }
    } 

    return matrix;
}

void free_matrix(Matrix *matrix) {
    for (size_t i = 0; i < matrix->M; ++i) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

void print_matrix(Matrix *matrix) {
    for (size_t y = 0; y < matrix->M; ++y) {
        for (size_t x = 0; x < matrix->N; ++x) {
            printf(" %d", matrix->data[y][x]);
        }
        printf("\n");
    }
}

