#include <windows.h>  // For high-resolution timer on Windows
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h> 

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


double measureExecutionTimeWithDebug(unsigned char* output, double* input, int width, int height, double looptime[]) {
    LARGE_INTEGER frequency, start_time, end_time;
    double total_time = 0.0;

    QueryPerformanceFrequency(&frequency);

    for (int i = 0; i < 30; i++) { // Run 30 iterations
        printf("\n--- Run %d ---\n", i + 1);


        QueryPerformanceCounter(&start_time); // Start timer
        imgCvtGrayDoubleToInt(output, input, width, height); // Call the assembly function
        QueryPerformanceCounter(&end_time);   // End timer

        // Calculate elapsed time for this iteration
        double elapsed_time = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
        total_time += elapsed_time;
        looptime[i] = elapsed_time;


        // Print execution time for this run
        printf("Execution Time for Run %d: %.9f seconds\n", i + 1, elapsed_time);
    }

    return total_time / 30.0; // Return the average execution time
}

int main() {
    int width, height, choice1, choice2;
    int timeruns = 0;

    printf("Enter image dimensions (height width): ");
    if (scanf_s("%d %d", &height, &width) != 2 || height <= 0 || width <= 0) {
        printf("Invalid dimensions! Exiting...\n");
        return 1;
    }

    if ((width == 10 && height == 10) || (width == 100 && height == 100) || (width == 1000 && height == 1000)) {
        printf("Continue with generating random values, recording execution time for 30 runs,and getting the average time [Input: 0] or Exit [Input: 1]: ");
        if (scanf_s("%d", &choice1) != 1 || choice1 <= -1 || choice1 >= 2) {
            printf("Invalid input! Exiting...\n");
            return 1;
        }
        choice2 = 0;
        timeruns = 1;
    }

    int size = width * height;
    double looptime[30];    
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

    if (timeruns == 0) {
        printf("Random pixel values [Input: 0] or Input pixel values [Input: 1]:");
        if (scanf_s("%d", &choice2) != 1 || choice2 >= 2 || choice2 <= -1) {
            printf("Invalid choice input! Exiting...\n");
            free(input);
            free(output_assembly);
            free(output_reference);
            return 1;
        }
    }

    if (choice2 == 1) {
        printf("Enter pixel values (range 0.0 to 1.0, space-separated, row by row):\n");
        for (int i = 0; i < size; i++) {
            if (scanf_s("%lf", &input[i]) != 1 || input[i] < 0.0 || input[i] > 1.0) {
                printf("Invalid pixel value! Exiting...\n");
                free(input);
                free(output_assembly);
                free(output_reference);
                return 1;
            }
        }
    }

    // Initialize input with random values
    if (choice2 == 0) {
        // Seed the random number generator for varied outputs each run
        srand((unsigned int)time(NULL) + clock());

        printf("Generating random pixel values...\n");
        for (int i = 0; i < size; i++) {
            int raw_rand = rand(); // Generate a random integer
            input[i] = (double)raw_rand / RAND_MAX; // Scale to [0.0, 1.0]
            printf("rand() = %d, Scaled = %.6f\n", raw_rand, input[i]); // Debugging information
        }
    }

    if (timeruns == 0) {
        printf("Show output only [Input: 0] or Time Execution up to 30 runs [Input: 1]:");
        if (scanf_s("%d", &timeruns) != 1 || timeruns >= 2 || timeruns <= -1) {
            printf("Invalid choice input! Exiting...\n");
            free(input);
            free(output_assembly);
            free(output_reference);
            return 1;
        }
    }

    if (timeruns == 1) {

        // Measure execution time with debugging
        printf("\nMeasuring execution time for assembly function...\n");
        double avg_time = measureExecutionTimeWithDebug(output_assembly, input, width, height, looptime);
        printf("\n--------------------------------------------------------------");

        printf("\n Converted Integer Pixel Values:\n");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                printf("%3d ", output_assembly[i * width + j]); // Ensure correct indexing
            }
            printf("\n");
        }

        // Validate correctness using reference function
        referenceCvtGrayDoubleToInt(output_reference, input, width, height);
        if (compareOutputs(output_assembly, output_reference, size)) {
            printf("Validation successful: Assembly output matches the reference implementation.\n");
        }
        else {
            printf("Validation failed: Assembly output does not match the reference implementation.\n");
        }

        printf("\n Summary of Runtimes: \n");
        printf(" Run # | Time (seconds) \n");
        printf("-----------------------------------------\n");
        for (int i = 0; i < 30; i++) {
            printf(" %6d | %4.9f \n", i+1, looptime[i]);
        }

        printf("\nAverage Execution Time for %dx%d: %.9f seconds\n", height, width, avg_time);

    }


    if (timeruns == 0) {

        // COmpute for the output
        imgCvtGrayDoubleToInt(output_assembly, input, width, height); // Call the assembly function

        printf("\n");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                printf("%3d ", output_assembly[i * width + j]); // Ensure correct indexing
            }
            printf("\n");
        }

        referenceCvtGrayDoubleToInt(output_reference, input, width, height);

        //Validate correctness
        if (compareOutputs(output_assembly, output_reference, size)) {
            printf("Validation successful: Assembly output matches the reference implementation.\n");
        }
        else {
            printf("Validation failed: Assembly output does not match the reference implementation.\n");
        }

    }

    free(input);
    free(output_assembly);
    free(output_reference);

    return 0;
}
