# MP_LBYARCH

## Group Members
- Irish Jane Ramos 
- Gabrielle Mae Arco
  
## Introduction

In this README file, we will be anlyzing our program's performance. Our program converts grayscale image representations from double-precision floating-point values (float) to 8-bit unsigned integer values (int) using both C and x86 assembly. This conversion is essential for compatibility between libraries that use different data types for image processing.

The conversion is performed by multiplying the float value by 255 (the maximum value for an 8-bit unsigned integer) and truncating it to the nearest integer value. The equation is as follows:

$$
\text{f} \times 255 = \text{i}
$$

Where:
- **𝑓** is the floating-point value in the range [0, 1].
- **𝑖** is the integer value in the range [0, 255].

In this case, we analyze the performance by measuring the execution time of the assembly implementation. The execution time is averaged over 30 runs for each of the input image sizes:   

10 × 10 
100 × 100   
1000 × 1000

Additionally, we will be showing a sample of the output result with the correctness check. 


## Execution Time and Short Analysis of the Performance

### Performance Analysis

| Input Size    | Total Pixels | Average Execution Time (seconds) | Time per Pixel (seconds/pixel) |
|---------------|--------------|----------------------------------|---------------------------------|
| 10 × 10       | 100          | 0.000001087                      | (0.000001240 / 100) = 1.09 × 10⁻⁸ |
| 100 × 100     | 10,000       | 0.000046957                      | (0.000046957 / 10,000) = 4.70 × 10⁻⁹ |
| 1000 × 1000   | 1,000,000    | 0.004206260                      | (0.004206260 / 1,000,000) = 4.21 × 10⁻⁹ |

Execution Time Scales in Relation to Input Size
* The execution time increases as the input size increases.
* We can expect this because the number of operations depends on the total number of pixels.
  
Efficiency per Pixel (Seconds/Pixel)
* The time per pixel decreases slightly as the input size grows.
* Due to the use of assembly code, it has improved CPU utilization and reduced overhead for larger datasets.
* These can be accounted to the reduced relative impact of fixed setup time in loop initialization and function calls, and better utilization of cache memory for larger, continuous data.

### Scaling Analysis

From 10 x 10 to 100 x 100
* Pixels increase by a factor of 100.
* Execution time increases by a factor of approximately:


$$
\frac{0.000046957}{0.000001087} \approx 43 
$$

From 100 x 100 to 1000 x 1000
* Pixels increase by a factor of 100.
* Execution time increases by a factor of approximately:

$$
\frac{0.004206260}{0.000046957} \approx 89
$$

Since the pixels increase by 100 in each scenario, we can expect that the execution time should also increase by 100-fold if we assume that the relationship between the execution time to be linear or: 

$$
\text{Execution Time} \propto \text{Total Pixels} (\text{Width} \times \text{Height})
$$

However, the algorithm remains efficient and exhibits good performance even as the input size grows, with execution time increasing by approximately 43 times for a 100-fold increase in pixels and 89 times for another 100-fold increase. Both have their execution times increase less than the expected 100-fold increase. It suggests that by using assembly to optimize memory management and data access, we can handle larger images more efficiently, resulting in slightly better performance than a normal linear increase.

## Screenshots of the program output with the correctness check
### 10 × 10
![image](https://github.com/user-attachments/assets/4495d5f4-9dd2-4ac1-a58b-42b2dc239bf6)
![image](https://github.com/user-attachments/assets/cd312922-8073-445b-9a8a-d696ab453f5a)
![image](https://github.com/user-attachments/assets/2cf3d11f-519b-40e9-9396-0dd4ba64a931)

### 100 × 100 (End only)
![image](https://github.com/user-attachments/assets/08170d8b-2a09-4624-9f84-30874147e747)
![image](https://github.com/user-attachments/assets/8b505fc5-0259-429b-a238-4a09fc4dce11)

### 1000 × 1000 (End only)
![image](https://github.com/user-attachments/assets/4145e9ba-6bc1-42ab-9390-8323e462f06e)
![image](https://github.com/user-attachments/assets/9ef60d16-6394-483e-9839-34a172ee424b)

## Video thats shows the source code, compilation, and execution of the C and x86-64 program.
https://drive.google.com/file/d/1dHOgSDuFoO6FYIa5Nc5TKzm31kZ1izrJ/view?usp=sharing


## Conclusion
The code demonstrates good scaling behavior with linear growth in execution time relative to the number of pixels. Additionally, as the input size grows, the system becomes more efficient at managing the larger data, leading to execution time increasing to less than the expected 100-fold. This a good outcome because the system is able to handle the increased load with relatively less overhead.





