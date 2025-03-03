#ifndef GWO_HPP
#define GWO_HPP

#include <vector>
#include <functional>
#include <random>
#include <limits>
#include <algorithm>

// Wolf struct representing an individual in the population
struct Wolf {
    std::vector<double> position;
    double fitness;

    Wolf();
    Wolf(const std::vector<double>& lower_bound, const std::vector<double>& upper_bound, std::mt19937& gen);

    bool operator<(const Wolf& other) const;
};

/**
 * @brief Computes the parameter `a` that decreases over iterations in the Grey Wolf Optimizer.
 * 
 * The parameter `a` influences the exploration and exploitation of the optimization process.
 * It starts at 2 and linearly decreases as the number of iterations increases.
 *
 * @param iter The total number of iterations in the optimization process.
 * @param current_iter The current iteration.
 * @return The computed value of `a`.
 */
double compute_a(int iter, int current_iter);

// The main Grey Wolf Optimizer function
/**
 * @brief Grey Wolf Optimizer (GWO) for solving optimization problems.
 * 
 * The Grey Wolf Optimizer (GWO) is a nature-inspired optimization algorithm 
 * based on the leadership hierarchy and social behavior of grey wolves. The algorithm 
 * uses the positions of alpha, beta, and delta wolves to guide the search for the global 
 * optimum by updating the positions of other wolves in the pack.
 * This version supports parallelization using OpenMP to speed up fitness evaluation 
 * and position updates, making it suitable for high-dimensional problems.
 * 
 * @param function A callable that evaluates the fitness of a solution. It should take 
 *                 a vector of doubles as input (representing the position of a wolf) 
 *                 and return a double representing the fitness of that solution.
 * @param lowerbound A vector containing the lower bounds for each dimension of the search space.
 * @param upperbound A vector containing the upper bounds for each dimension of the search space.
 * @param population The number of wolves in the pack.
 * @param iter The number of iterations (generations) to run the optimization process.
 * @param gen A random number generator (std::mt19937) used for generating random values in 
 *            the update process and initializing the wolves' positions.
 * @param compute_a A function that computes the parameter `a` (which influences exploration 
 *                  and exploitation) based on the current iteration and total iterations. 
 *                  Default is the provided `compute_a` function.
 * 
 * @return A pair containing:
 *         - A vector of doubles representing the best solution found (position of the wolf).
 *         - A double representing the fitness value of the best solution found.
 * 
 * @note The algorithm uses OpenMP for parallelizing fitness evaluation and position updates. 
 *       Ensure that your compiler supports OpenMP and that it is enabled during compilation.
 */
std::pair<std::vector<double>, double> GreyWolfOptimizer(
    const std::function<double(const std::vector<double>&)>& function,
    const std::vector<double>& lowerbound,
    const std::vector<double>& upperbound,
    int population, int iter, std::mt19937& gen, 
    const std::function<double(int, int)>& compute_a = compute_a);

#endif // GWO_HPP
