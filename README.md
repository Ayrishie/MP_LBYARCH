# MP_LBYARCH

i.) execution time and short analysis of the performance

## Performance Analysis


| Input Size    | Total Pixels | Execution Time (seconds) | Time per Pixel (seconds/pixel) |
|---------------|--------------|--------------------------|---------------------------------|
| 10 × 10       | 100          | 0.000001240              | 0.000001240 / 100 = 1.24 × 10⁻⁸ |
| 100 × 100     | 10,000       | 0.000064717              | 0.000064717 / 10,000 = 6.47 × 10⁻⁹ |
| 1000 × 1000   | 1,000,000    | 0.004341680              | 0.004341680 / 1,000,000 = 4.34 × 10⁻⁹ |

Execution Time Scales with Input Size:
* The execution time increases as the input size increases. This is expected because the number of operations depends linearly on the total number of pixels.
  
Efficiency per Pixel
* The time per pixel decreases slightly as the input size grows. This suggests that the code benefits from improved CPU utilization or reduced overhead for larger datasets.
* Possible reasons include:
  * Reduced relative impact of fixed setup time (e.g., loop initialization, function calls).
  * Better utilization of cache memory for larger, continuous data.

Order of Growth
* The relationship between execution time and input size is approximately linear:
* This indicates the algorithm has an **O(n)** complexity, where `n` is the total number of pixels.

## Scaling Analysis

Doubling Pixels (from 10 × 10 to 100 × 100):
* Pixels increase by a factor of 100
* Execution time increases by a factor of approximately \( \frac{0.000064717}{0.000001240} \approx 52 \).

From 100 × 100 to 1000 × 1000:
* Pixels increase by a factor of 100
* Execution time increases by a factor of approximately \( \frac{0.004341680}{0.000064717} \approx 67 \).

While scaling isn’t perfectly linear, it remains close, possibly due to variations in system-level factors like cache misses or memory access patterns.

## Conclusion
The code demonstrates good scaling behavior with linear growth in execution time relative to the number of pixels.

ii.) Take a screenshot of the program output with the correctness check.

![image](https://github.com/user-attachments/assets/9918d413-0f22-4603-aa9e-790be050d933)


