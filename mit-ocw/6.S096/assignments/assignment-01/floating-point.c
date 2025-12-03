// MIT OCW 6.S096
// Assignment 1, Problem 1: Floating Point
// (-1)^sign × 1.mantissa × 2^(exponent − bias)

#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

#define MANTISSA 23
#define EXPONENT 8
#define BIAS 127
#define DEBUG 0

static const char *input = "p1-input.txt";
static const char *output = "p1-output.txt";

typedef union float_bits {
    float f;
    uint32_t bits;
} float_bits;

void print_hex(float f);
void float_to_bin(FILE *output_f, uint32_t num);

int main(void) {
    FILE *input_f = fopen(input, "r"), *output_f = fopen(output, "w");
    if (!input_f || !output_f) {
        perror("Error opening files!");
        return 1;
    }
    
    float f; unsigned int out;
    while (fscanf(input_f, "%f", &f) == 1) {
#if DEBUG
        print_hex(out);
#endif
        float_bits t;
        t.f = f;
        float_to_bin(output_f, t.bits);
    }

    fclose(input_f);
    fclose(output_f);
    return 0;
}

void float_to_bin(FILE *output_f, uint32_t num) {
    if (!output_f) {
        fprintf(stderr, "Error with file!\n");
        return;
    }

    uint32_t is_signed = num >> 31 & 1;
    uint32_t exponent = num >> (31 - EXPONENT) & 0xFF; 
    uint32_t mantissa = num & 0x7FFFFF;
#if DEBUG 
    printf("signed: %d\n", is_signed); 
    printf("exponent: %d\n", exponent); 
    printf("mantissa: %d\n", mantissa); 
#endif
    if (is_signed) {
        fprintf(output_f, "-");
    }
    if (exponent == 0xFF) {
        fprintf(output_f, "Inf\n");
        return;
    }

    if (exponent == 0){
        fprintf(output_f, "0.");
    } else {
        fprintf(output_f, "1.");
    }

    for (int i = 22; i >= 0; i--) {
        fprintf(output_f, "%u", (mantissa >> i) & 1);
    }

    if (exponent == 0) {
        if (mantissa != 0)
            fprintf(output_f, " * 2^(-126)\n");
        else
            fprintf(output_f, "\n");
    } else {
        fprintf(output_f, " * 2^(%d)\n", (int)exponent - 127);
    }
}

void print_hex(float f) {
    union float_bits t;
    t.f = f;
    printf("The float looks like 0x%x in hex.\n", t.bits);
}
