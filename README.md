# MP_LBYARCH

## Execution Time and Short Analysis of the Performance

### Performance Analysis


| Input Size    | Total Pixels | Execution Time (seconds) | Time per Pixel (seconds/pixel) |
|---------------|--------------|--------------------------|---------------------------------|
| 10 × 10       | 100          | 0.000001240              | 0.000001240 / 100 = 1.24 × 10⁻⁸ |
| 100 × 100     | 10,000       | 0.000064717              | 0.000064717 / 10,000 = 6.47 × 10⁻⁹ |
| 1000 × 1000   | 1,000,000    | 0.004341680              | 0.004341680 / 1,000,000 = 4.34 × 10⁻⁹ |

Execution Time Scales in Relation to Input Size
* The execution time increases as the input size increases.
* We can expect this because of the number of operations depends on the total number of pixels.
  
Efficiency per Pixel (Seconds/Pixel)
* The time per pixel decreases slightly as the input size grows.
* Due to the use of assembly code, it has improved CPU utilization and reduced overhead for larger datasets.
* These can be accounted to the reduced relative impact of fixed setup time in loop initialization and function calls, and better utilization of cache memory for larger, continuous data.

### Scaling Analysis

From 10 × 10 to 100 × 100
* Pixels increase by a factor of 100.
* Execution time increases by a factor of approximately \( \frac{0.000064717}{0.000001240} \approx 52 \).

From 100 × 100 to 1000 × 1000
* Pixels increase by a factor of 100.
* Execution time increases by a factor of approximately \( \frac{0.004341680}{0.000064717} \approx 67 \).

Since, in each scenario, the pixels increase by 100 we can expect that the execution time should also increase by 100-fold if we assume that the relationship between the execution time to be linear or: 

$$
\text{Execution Time} \propto \text{Total Pixels} (\text{Width} \times \text{Height})
$$

However, the algorithm remains efficient and exhibits good performance even as the input size grows, with execution time increasing by approximately 52 times for a 100-fold increase in pixels and 67 times for another 100-fold increase. Both have their execution times increase less than the expected 100-fold increase. It suggests that system-level optimizations or memory management techniques are helping to handle larger images more efficiently, resulting in slightly better performance than a normal linear increase would suggest.

## Conclusion
The code demonstrates good scaling behavior with linear growth in execution time relative to the number of pixels. Additionally, as the input size grows, the system becomes more efficient at managing the larger data, leading to execution time increasing to less than the expected 100-fold. This can be seen as a positive outcome because the system is able to handle the increased load with relatively less overhead.


## Screenshot of the program output with the correctness check

![image](https://github.com/user-attachments/assets/9918d413-0f22-4603-aa9e-790be050d933)


