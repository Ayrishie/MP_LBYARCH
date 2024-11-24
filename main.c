#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Function prototypes
extern void imgCvtGrayDoubleToInt(uint8_t* output, double* input, int width, int height);
extern double debug_temp; // Declare debug_temp as an external variable

int main() {
    int width, height;

    printf("Enter image dimensions (height width): ");
    if (scanf_s("%d %d", &height, &width) != 2 || height <= 0 || width <= 0) {
        printf("Invalid dimensions! Exiting...\n");
        return 1;
    }

    int size = width * height;
    double* input = (double*)malloc(size * sizeof(double));
    uint8_t* output = (uint8_t*)malloc(size * sizeof(uint8_t));
    if (!input || !output) {
        printf("Memory allocation failed! Exiting...\n");
        free(input);
        free(output);
        return 1;
    }

    printf("Enter pixel values (range 0.0 to 1.0, space-separated, row by row):\n");
    for (int i = 0; i < size; i++) {
        if (scanf_s("%lf", &input[i]) != 1 || input[i] < 0.0 || input[i] > 1.0) {
            printf("Invalid pixel value! Exiting...\n");
            free(input);
            free(output);
            return 1;
        }
    }

    imgCvtGrayDoubleToInt(output, input, width, height);

    printf("Debugging Scaled Values (f * 255):\n");
    for (int i = 0; i < size; i++) {
        imgCvtGrayDoubleToInt(&output[i], &input[i], 1, 1); // Process one pixel
        printf("Pixel %d: Scaled value = %.2f\n", i, debug_temp);
    }

    printf("Converted Integer Pixel Values:\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%3d ", output[i * width + j]); // Ensure correct indexing
        }
        printf("\n");
    }

    free(input);
    free(output);

    return 0;
}
