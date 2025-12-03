// MIT OCW 6.S096
// Assignment 1, Problem 4: Transposition Cipher (loop)
// default entries

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 1024

static const char *input = "p3-input.txt";
static const char *output = "p3-output.txt";

void encrypt(char *String, size_t length);
size_t getstr(char **Str, FILE *input_f);

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
    
    if (!input_f || !output_f) {
        fprintf(stderr, "Failed to open files.\n");
        return 1;
    }

    char *text = NULL;
    size_t length = getstr(&text, input_f);

    encrypt(text, length);

    fwrite(text, 1, length, output_f);

    free(text);
    fclose(input_f); fclose(output_f);
    return 0;
}

void encrypt(char *String, size_t length) {
    if (length <= 2) return;

    size_t k = length / 2;

    for (size_t i = 0; i < k / 2; i++) {
        char temp = String[i];
        String[i] = String[k - 1 - i];
        String[k - 1 - i] = temp;
    }

    for (size_t i = 0; i < (length - k) / 2; i++) {
        char temp = String[k + i];
        String[k + i] = String[length - 1 - i];
        String[length - 1 - i] = temp;
    }

    encrypt(String, k);
    encrypt(String + k, length - k);
}

size_t getstr(char **Str, FILE *input_f) {
    size_t chars_to_read = BLOCK_SIZE;
    size_t length = 0;
    size_t chars = 0;

    *Str = (char *)malloc(chars_to_read);
    if (*Str == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    while ((chars = fread(*Str + length, 1, chars_to_read, input_f)) > 0) {
        length += chars;

        if (length + BLOCK_SIZE > chars_to_read) {
            chars_to_read *= 2;  // double buffer size
            char *new_ptr = (char *)realloc(*Str, chars_to_read);
            if (new_ptr == NULL) {
                free(*Str);
                fprintf(stderr, "Memory reallocation failed\n");
                return 0;
            }
            *Str = new_ptr;
        }
    }

    return length;
}
