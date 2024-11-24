#include <stdio.h>
#include <stdlib.h>

// Declare the assembly function
extern void imgCvtGrayDoubleToInt(unsigned char* output, double* input, int width, int height);

int main() {
    int width, height;

    printf("Enter image dimensions (height width): ");
    if (scanf_s("%d %d", &height, &width) != 2 || height <= 0 || width <= 0) {
        printf("Invalid dimensions! Exiting...\n");
        return 1;
    }

    int size = width * height;
    double* input = (double*)malloc(size * sizeof(double));
    unsigned char* output = (unsigned char*)malloc(size * sizeof(unsigned char));

    if (!input || !output) {
        printf("Memory allocation failed! Exiting...\n");
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

    printf("\nCalling assembly function...\n");
    imgCvtGrayDoubleToInt(output, input, width, height);
    printf("Assembly function completed.\n");

    // Print the converted values
    printf("\nConverted Integer Pixel Values:\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%3d ", output[i * width + j]);
        }
        printf("\n");
    }

    free(input);
    free(output);

    return 0;
}
