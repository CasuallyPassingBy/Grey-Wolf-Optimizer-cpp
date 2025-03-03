# Benchmark Functions for Optimization

## Overview

Benchmark functions are widely used in optimization to evaluate the performance of algorithms. These functions present challenges such as multiple local minima, high dimensionality, and rugged landscapes, helping to test the effectiveness of optimization techniques like the Grey Wolf Optimizer (GWO).

This document describes the benchmark functions implemented in the GWO project.

## Benchmark Functions

### 1. De Jong’s Function (Sphere Function)

**Equation:**

$$
 f(x) = \sum_{i=1}^{n} x_i^2
$$

**Domain:** \(-5.12 \leq x_i \leq 5.12\)

- A simple convex function with a global minimum at \(x = 0\).
- Often used to test basic optimization performance.

### 2. Rosenbrock’s Function (Valley or Banana Function)

**Equation:**

$$
 f(x, y) = \sum_{i=1}^{n-1} [100(x_{i+1} - x_i^2)^2 + (x_i - 1)^2]
$$

**Domain:** \(-2.048 \leq x_i \leq 2.048\)

- Features a narrow, curved valley making optimization difficult.
- Global minimum at \((1,1,...,1)\).

### 3. Rastrigin’s Function

**Equation:**

$$
 f(x) = 10n + \sum_{i=1}^{n} [x_i^2 - 10 \cos(2\pi x_i)]
$$

**Domain:** \(-5.12 \leq x_i \leq 5.12\)

- Highly multimodal with many local minima.
- Used to test an algorithm’s ability to escape local optima.

### 4. Ackley’s Function

**Equation:**

$$
 f(x) = -20 \exp\left(-0.2 \sqrt{\frac{1}{n} \sum_{i=1}^{n} x_i^2} \right) -
 \exp\left(\frac{1}{n} \sum_{i=1}^{n} \cos(2\pi x_i) \right) + 20 + e
$$

**Domain:** \(-32.768 \leq x_i \leq 32.768\)

- Contains a nearly flat outer region and a large number of local minima.
- Global minimum at \(x = 0\).

### 5. Michalewicz’s Function

**Equation:**

$$
 f(x) = - \sum_{i=1}^{n} \sin(x_i) \left( \sin \left( \frac{i x_i^2}{\pi} \right) \right)^{2m}
$$

**Domain:** \(0 \leq x_i \leq \pi\)

- Highly irregular with steep ridges.
- Increasing \(m\) increases difficulty.

### 6. Shekel’s Function

**Equation:**

$$
 f(x) = - \sum_{i=1}^{m} \left( \sum_{j=1}^{n} (x_j - A_{ji})^2 + C_i \right)^{-1}
$$

- Commonly used with \(m = 4\), \(n = 2\).
- Represents a multimodal function with known local minima.

## Usage in Optimization

Each function presents unique challenges, from convex landscapes (Sphere) to highly multimodal functions (Rastrigin, Michalewicz). The Grey Wolf Optimizer is tested against these functions to evaluate its effectiveness in global optimization.

## References

- Jamil, M., & Yang, X. S. (2013). *A literature survey of benchmark functions for global optimization problems*. International Journal of Mathematical Modelling and Numerical Optimisation, 4(2), 150-194.

