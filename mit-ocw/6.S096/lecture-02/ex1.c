#include <stdio.h>

int main(void) {
    // open file for writing
    FILE *output = fopen("prog.out", "w");
    // do stuff; then close and free resources
    fclose(output);
    return 0;
}
