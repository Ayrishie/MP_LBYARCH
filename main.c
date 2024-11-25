#include <windows.h>  // For high-resolution timer on Windows
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Declare the assembly function
extern void imgCvtGrayDoubleToInt(unsigned char* output, double* input, int width, int height);

// Reference implementation in C for correctness validation
void referenceCvtGrayDoubleToInt(unsigned char* output, double* input, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        int value = (int)(input[i] * 255.0);
        if (value < 0) value = 0;
        if (value > 255) value = 255;
        output[i] = (unsigned char)value;
    }
}

// Function to compare two outputs and validate correctness
bool compareOutputs(unsigned char* output1, unsigned char* output2, int size) {
    bool is_valid = true;
    printf("\nValidation Debugging:\n");
    printf("Index | Assembly Output | Reference Output\n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%5d | %15d | %16d\n", i, output1[i], output2[i]);
        if (output1[i] != output2[i]) {
            printf("  -> Mismatch at index %d: Assembly=%d, Reference=%d\n", i, output1[i], output2[i]);
            is_valid = false;
        }
    }
    return is_valid;
}


double measureExecutionTimeWithDebug(unsigned char* output, double* input, int width, int height) {
    LARGE_INTEGER frequency, start_time, end_time;
    double total_time = 0.0;

    
    QueryPerformanceFrequency(&frequency);

    for (int i = 0; i < 30; i++) { // Run 30 iterations
        printf("\n--- Run %d ---\n", i + 1);

        // Print input values
        printf("Input Double Pixel Values:\n");
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                printf("%.6f ", input[row * width + col]);
            }
            printf("\n");
        }

        QueryPerformanceCounter(&start_time); // Start timer
        imgCvtGrayDoubleToInt(output, input, width, height); // Call the assembly function
        QueryPerformanceCounter(&end_time);   // End timer

        // Calculate elapsed time for this iteration
        double elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
        total_time += elapsed_time;

        // Print output values
        printf("\nConverted Integer Pixel Values (Assembly):\n");
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                printf("%3d ", output[row * width + col]);
            }
            printf("\n");
        }

        // Print execution time for this run
        printf("Execution Time for Run %d: %.9f seconds\n", i + 1, elapsed_time);
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
    unsigned char* output_assembly = (unsigned char*)malloc(size * sizeof(unsigned char));
    unsigned char* output_reference = (unsigned char*)malloc(size * sizeof(unsigned char));

    if (!input || !output_assembly || !output_reference) {
        printf("Memory allocation failed! Exiting...\n");
        free(input);
        free(output_assembly);
        free(output_reference);
        return 1;
    }

    // Seed the random number generator for varied outputs each run
    srand((unsigned int)time(NULL));

    // Initialize input with random values
    printf("Generating random pixel values...\n");
    for (int i = 0; i < size; i++) {
        int raw_rand = rand(); // Generate a random integer
        input[i] = (double)raw_rand / RAND_MAX; // Scale to [0.0, 1.0]
        printf("rand() = %d, Scaled = %.6f\n", raw_rand, input[i]); // Debugging information
    }

    // Measure execution time with debugging
    printf("\nMeasuring execution time for assembly function...\n");
    double avg_time = measureExecutionTimeWithDebug(output_assembly, input, width, height);
    printf("\nAverage Execution Time for %dx%d: %.9f seconds\n", height, width, avg_time);
    printf("\n--------------------------------------------------------------");
    // Validate correctness using reference function
    referenceCvtGrayDoubleToInt(output_reference, input, width, height);
    if (compareOutputs(output_assembly, output_reference, size)) {
        printf("Validation successful: Assembly output matches the reference implementation.\n");
    }
    else {
        printf("Validation failed: Assembly output does not match the reference implementation.\n");
    }

    free(input);
    free(output_assembly);
    free(output_reference);

    return 0;
}

