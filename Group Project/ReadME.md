# Smart Change Calculator
### CSCE 4110 — Algorithms

**Student:** Bryson Brown  
**Project Type:** Semester Project
**Programming Language:** C++17

## Project Overview

The Smart Change Calculator is a C++ application that compares two algorithms for solving the Coin Change Problem: the Greedy Algorithm and Dynamic Programming.

The objective is to determine the minimum number of coins required to make a specified amount of change and evaluate the performance and accuracy of each algorithm.

## Algorithms Implemented

### 1. Greedy Algorithm

The Greedy Algorithm selects the largest available coin denomination first and continues selecting coins until the target amount is reached or no further progress can be made.

**Advantages:**
- Fast execution
- Simple implementation
- Low memory usage

**Limitation:** Does not always produce the minimum number of coins for custom denominations.

### 2. Dynamic Programming

Dynamic Programming calculates the minimum number of coins required for each amount up to the target. It uses previously calculated solutions to determine the optimal combination.

**Advantages:**
- Finds the minimum number of coins when a solution exists
- Supports custom coin denominations
- Can identify impossible combinations

**Limitation:** Requires additional processing time and memory as the target amount increases.

## Project Structure

```text
Group Project/
├── src/
│   └── main.cpp
├── benchmarks/
│   ├── benchmark.cpp
│   └── benchmarks.csv
├── report/
│   └── CSCE4110_Final_Report_Bryson_Brown.pdf
└── README.md
```

## Requirements

- C++17-compatible compiler (Clang++ or g++)
- macOS, Windows, or Linux
- Terminal or Visual Studio Code
- No external libraries required

## Compilation and Execution

Open a terminal inside the `Group Project` directory.

**Compile the main application:**

```bash
clang++ -std=c++17 -O2 src/main.cpp -o smart_change
```

**Run the application:**

```bash
./smart_change
```

**Run the automated demonstration:**

```bash
./smart_change --demo
```

**Compile the benchmark:**

```bash
clang++ -std=c++17 -O2 benchmarks/benchmark.cpp -o benchmark
```

**Run the benchmark:**

```bash
./benchmark
```

The benchmark generates `benchmarks.csv` in the current working directory.

## Example Algorithm Comparison

For an amount of 30 cents using denominations of 1, 10, and 25 cents:

| Algorithm | Coin Selection | Total Coins |
|---|---|---|
| Greedy | 25 + 1 + 1 + 1 + 1 + 1 | 6 |
| Dynamic Programming | 10 + 10 + 10 | 3 |

This demonstrates that the Greedy Algorithm does not always find the optimal solution.

## Performance Benchmark Results

Both algorithms were tested using 30 trials per amount on a MacBook.

| Amount (cents) | Greedy (µs) | Dynamic Programming (µs) |
|---|---:|---:|
| 100 | 0.110 | 0.610 |
| 500 | 0.281 | 1.893 |
| 1,000 | 0.264 | 3.439 |
| 2,500 | 0.333 | 8.126 |
| 5,000 | 0.377 | 15.414 |
| 10,000 | 0.518 | 30.254 |

Greedy consistently executed faster during these benchmark tests, while Dynamic Programming provides an optimal solution for arbitrary valid coin denominations.

## Time Complexity

| Algorithm | Time Complexity | Auxiliary Space |
|---|---|---|
| Greedy | O(k log k) including denomination sorting | Depends on stored output |
| Dynamic Programming | O(A × k) | O(A) |

Where:
- A = target amount
- k = number of coin denominations

## Testing

The project includes tests involving:

- Standard coin denominations
- Custom coin denominations
- Cases where Greedy is not optimal
- Cases where change cannot be made
- Increasing target amounts
- Execution time and operation comparisons

## Project Contributions

**Bryson Brown — Sole Project Contributor**

Responsible for the project implementation, algorithm integration, correctness testing, performance benchmarking, documentation, report preparation, GitHub organization, and final demonstration.

The instructor approved individual completion of the project.

## Final Report

The project report is available in the `report` directory.

## Demonstration Video

Video link: To be added after recording and publication.

## Conclusion

The Smart Change Calculator demonstrates that algorithm selection involves balancing execution efficiency and solution correctness. Greedy is efficient but may produce suboptimal results, while Dynamic Programming guarantees the minimum number of coins when a valid solution exists.
