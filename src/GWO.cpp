#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <random>
#include <array>
#include <omp.h>

// Structure to represent a single wolf
struct Wolf {
    std::vector<double> position;
    double fitness;

    Wolf() : fitness(std::numeric_limits<double>::max()) {}

    Wolf(const std::vector<double>& lower_bound, const std::vector<double>& upper_bound, std::mt19937& gen) {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        position.resize(lower_bound.size());

        for (size_t i = 0; i < position.size(); ++i) {
            position[i] = lower_bound[i] + dist(gen) * (upper_bound[i] - lower_bound[i]);
        }

        fitness = std::numeric_limits<double>::max();
    }

    bool operator<(const Wolf& other) const {
        return fitness < other.fitness;
    }
};

// Compute the `a` parameter that decreases over iterations
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
double compute_a(int iter, int current_iter) {
    return 2.0 * (1 - static_cast<double>(current_iter) / iter);
}

// Update a wolf’s position based on the leader’s influence
double update_position(double wolf_pos, double leader_pos, double a, std::mt19937& gen) {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double r1 = dist(gen);
    double r2 = dist(gen);
    double A = 2 * a * r1 - a;
    double C = 2 * r2;
    double D = fabs(C * leader_pos - wolf_pos);
    return leader_pos - A * D;
}

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
    const std::function<double(int, int)>& compute_a = compute_a) 
{
    std::vector<Wolf> pack;
    pack.reserve(population);

    // Initialize wolves randomly
    for (int i = 0; i < population; ++i) {
        pack.emplace_back(lowerbound, upperbound, gen);
    }

    // Track the best solution found
    Wolf best_solution = pack[0];

    for (int i = 0; i < iter; ++i) {
        // Evaluate fitness
        #pragma omp parallel for
        for (int j = 0; j < population; ++j) {
            pack[j].fitness = function(pack[j].position);

            #pragma omp critical
            if (pack[j].fitness < best_solution.fitness) {
                best_solution = pack[j];
            }
        }

        // Get the three best wolves (leaders)
        std::partial_sort(pack.begin(), pack.begin() + 3, pack.end());
        std::array<Wolf, 3> leaders = { pack[0], pack[1], pack[2] }; // Alpha, Beta and Delta Wolves

        double a = compute_a(iter, i);

        // Update positions
        #pragma omp parllel for
        for (Wolf& wolf : pack) {
            for (size_t j = 0; j < lowerbound.size(); ++j) {
                double X1 = update_position(wolf.position[j], leaders[0].position[j], a, gen); // Alpha's Influence on the wolf
                double X2 = update_position(wolf.position[j], leaders[1].position[j], a, gen); // Beta's Influence on the wolf
                double X3 = update_position(wolf.position[j], leaders[2].position[j], a, gen); // Delta's Influence on the wolf

                wolf.position[j] = std::clamp((X1 + X2 + X3) / 3.0, lowerbound[j], upperbound[j]);
            }
        }
    }

    return { best_solution.position, best_solution.fitness };
}
