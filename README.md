# Grey Wolf Optimizer in C++

This is a C++ implementation of the meta-heuristic based on the grey wolves hunting patterns :wolf:. This implementation is based on the [research paper](https://www.researchgate.net/publication/260010809_Grey_Wolf_Optimizer) that first published this meta-heuristic. 

This projects implemnts the **Grey Wolf Optimizer (GWO)**, a nature inspired optimization algorithm that mimics the leadership hierarchy and hunting of grey wolves 🐺. The algorithm is tested on multiple benchmark functions.

# Summary

The Grey Wolf Optimizer (GWO) is a metaheuristic optimization algorithm inspired by the social hierarchy and hunting behavior of grey wolves. The algorithm simulates the leadership structure of a wolf pack, where alpha, beta, and delta wolves guide the search process, while omega wolves follow their lead.

![image](https://github.com/user-attachments/assets/a8ed802d-ff7e-4b7b-a2c3-62238c914a87)

 The hunting process consists of encircling prey, tracking, and attacking, making GWO effective for solving complex optimization problems.

 ![image](https://github.com/user-attachments/assets/fb604451-bb73-4dc9-a6de-fee9d7b436b8)

# Features
- Implementation of the Grey Wolf Optimizer
- Optimization of various [benchmark functions](benchmark_functions.md)
- Supports parameter tuning for population size, iterations, and repetitions
- Uses C++ for efficient computation

# Prerequisites
To build and run the project, you need:
- A C++ compiler that supports C++17 or later.
- CMake (optional, for better build management)

# Installation
1. Clone the repository 
```bash
git clone https://github.com/CasuallyPassingBy/Grey-Wolf-Optimizer-cpp.git
```
2. Ensure you have a C++ compiler installed (e.g. g++ for GCC)

# Usage 
Modify `Tesing.cpp` to optimize different functions or adjust the parameters:
```cpp
const int population = 20;    // Number of wolves
const int iterations = 1000;  // Number of iterations
const int repetitions = 30;   // Number of repetitions
```
You can replace the benchmark function being optimized:
```cpp
function<double(vector<double>)> target_function = Ackley;
```

# Compilation
To compile the project using g++, run:
```bash
g++ -o optimizer src/Testing.cpp src/GWO.cpp src/functions.cpp
```
Then, excute the program:
```bash
./optimizer
```
This will optimize various benchmark functions using the GWO algorithm and output the results. 

# Contributors
- Mauricio Moscoso (@CasuallyPassingBy)
- Digeo Gerardo Casados 

# Contributing
Feel free to contribute by adding new branch functions, improving optimization techniques, or refactoring the code.

# Sources

- **Grey Wolf Optimizer:**
  - Mirjalili, S., Mirjalili, S. M., & Lewis, A. (2014). *Grey wolf optimizer*. Advances in Engineering Software, 69, 46-61. [DOI: 10.1016/j.advengsoft.2013.12.007](https://doi.org/10.1016/j.advengsoft.2013.12.007)

- **Benchmark Functions:**
  - Jamil, M., & Yang, X. S. (2013). *A literature survey of benchmark functions for global optimization problems*. International Journal of Mathematical Modelling and Numerical Optimisation, 4(2), 150-194. [DOI: 10.1504/IJMMNO.2013.055204](https://doi.org/10.1504/IJMMNO.2013.055204)


# Licence
This project is open-source and distributed under the [MIT License](LICENSE). 
