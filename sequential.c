#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WIDTH 1200
#define HEIGHT 1200

int main() {
    double start = clock() / (double)CLOCKS_PER_SEC;

    double real_min = -1.0;
    double real_max = 1.0;
    double imag_min = -1.0;
    double imag_max = 1.0;
    int max_counter = 1000;

    int* data = (int*)malloc(sizeof(int) * WIDTH * HEIGHT);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double c_real = real_min + (real_max - real_min) * x / WIDTH;
            double c_imag = imag_min + (imag_max - imag_min) * y / HEIGHT;
            double z_real = 0.0;
            double z_imag = 0.0;

            int counter = 0;
            while (z_real * z_real + z_imag * z_imag < 4.0 && counter < max_counter) {
                double next_z_real = z_real * z_real - z_imag * z_imag + c_real;
                double next_z_imag = 2.0 * z_real * z_imag + c_imag;
                z_real = next_z_real;
                z_imag = next_z_imag;
                counter++;
            }

            if (counter == max_counter) {
                data[y * WIDTH + x] = 0;
            } else {
                data[y * WIDTH + x] = counter % 256;
            }
        }
    }

    FILE* fp = fopen("mandelbrot_sequential.pgm", "wb");
    fprintf(fp, "P5\n%d %d\n255\n", WIDTH, HEIGHT);
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        fputc(data[i], fp);
    }
    fclose(fp);
    free(data);

    double end = clock() / (double)CLOCKS_PER_SEC;
    printf("Total execution time: %f seconds\n", end - start);

    return 0;
}
