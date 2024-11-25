#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// Declare the assembly function
extern void imgCvtGrayDoubleToInt(unsigned char* output, double* input, int width, int height);

// Function to measure execution time using QueryPerformanceCounter
double measureExecutionTime(unsigned char* output, double* input, int width, int height) {
    LARGE_INTEGER frequency, start_time, end_time;
    double total_time = 0.0;

    // Get the frequency of the performance counter
    QueryPerformanceFrequency(&frequency);

    for (int i = 0; i < 30; i++) { // Run 30 times for averaging
        QueryPerformanceCounter(&start_time); // Start timer
        imgCvtGrayDoubleToInt(output, input, width, height); // Call the assembly function
        QueryPerformanceCounter(&end_time);   // End timer

        total_time += (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
    }

    return total_time / 30.0; // Return the average execution time
}

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
 

    // Print the converted values
    printf("\nConverted Integer Pixel Values:\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%3d ", output[i * width + j]);
        }
        printf("\n");
    }

    // Measure and display execution time
    double avg_time = measureExecutionTime(output, input, width, height);
    printf("Average Execution Time for %dx%d: %.9f seconds\n", height, width, avg_time);

    free(input);
    free(output);

    return 0;
}
