#include "mandelbrot.h"
#include <stdio.h>

int main(int argc, char **argv) {
    const char *path = (argc == 2) ? argv[1] : "mandelbrot.ppm";

    FILE *image = fopen(path, "w");
    if (!image) {
        fprintf(stderr, "Failed while opening %s file\n", path);
        return 1;
    }

    mandelbrot(image);
    
    fclose(image);
    printf("Open %s to see the fractal\n", path);
    return 0;
}

void mandelbrot(FILE *image) {
    if (!image) return;
    fprintf(image, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double real = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double imag = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
            double complex c = real + imag * I;
            double complex z = 0 + 0 * I;

            int i = 0;
            while (cabs(z) <= 2.0 && i < MAX_ITER) {
                z = z * z + c;
                ++i;
            }

            if (i == MAX_ITER) {
                fprintf(image, "0 0 0 ");
            } else {
                int color = (i * 255) / MAX_ITER;
                fprintf(image, "%d 0 %d ", color, color);
            }
        }
        fprintf(image, "\n");
    }
}
