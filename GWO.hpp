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

// Core GWO function
std::pair<std::vector<double>, double> GreyWolfOptimizer(
    const std::function<double(const std::vector<double>&)>& function,
    const std::vector<double>& lowerbound,
    const std::vector<double>& upperbound, int population, int iter, std::mt19937& gen);

#endif // GWO_HPP
