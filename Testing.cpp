#include <vector>
#include <functional>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>

#include "functions.hpp"
#include "GWO.hpp"

using namespace std;

struct BenchmarkFunction {
    function<double(vector<double>)> func;
    vector<double> lower_bound;
    vector<double> upper_bound;
    string name;
};

// Función para medir el desempeño de GWO
void Result_of_Optimization(const function<double(vector<double>)>& optimized_function, const vector<double>& lower_bounds, const vector<double>& upper_bounds, const int& population, const int& iterations, const int& repetitions, mt19937& gen, const string& name) {
    vector<double> data;
    for (size_t i = 0; i < repetitions; ++i) {
        auto [best_position, best_fitness] = GreyWolfOptimizer(optimized_function, lower_bounds, upper_bounds, population, iterations, gen);
        data.push_back(best_fitness);
    }

    double maximum = *max_element(data.begin(), data.end());
    double minimum = *min_element(data.begin(), data.end());
    double sum = accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / repetitions;
    double variance = 0.0;
    for (auto& fitness : data) variance += pow(fitness - mean, 2);
    double std_deviation = sqrt(variance / (repetitions - 1));

    cout << "Resultados de la función " << name << "\n";
    cout << "\ta) Valor máximo: " << maximum << "\n";
    cout << "\tb) Valor mínimo: " << minimum << "\n";
    cout << "\tc) Valor promedio: " << mean << "\n";
    cout << "\td) Desviación estándar: " << std_deviation << endl;
}

int main() {
    random_device rd;
    mt19937 gen(rd());

    const int repetitions = 30;
    const int population = 20;
    const int iterations = 1000;
    int dimensions = 20;

    // Definción de parámetros para la función objetivo de Ackley                                                       
    vector<double> usual_ackley_a = {20, 0.2, 2 * M_PI};                                                                
    function<double(vector<double>)> bound_ackley = bindAckley(usual_ackley_a);                                         

    // Definición de parámetros para la función objetivo de Langermann
    vector<vector<double>> usual_langermann_a = {{3, 5}, {5, 2}, {2, 1}, {1, 4}, {7, 9}};
    vector<double> usual_langermann_c = {1, 2, 5, 2, 3};
    int langermann_dimension = usual_langermann_a[0].size();
    function<double(vector<double>)> bound_langermann = bindLangermann(usual_langermann_a, usual_langermann_c);

    // Definición de parámetros para la función objetivo de Michalewicz
    int m = 10;
    function<double(vector<double>)> bound_michalewicz = bindMichalewicz(m);

    // Definición de parámetros para la función objetivo de Branin
    vector<double> usual_branin_a = {1, 1.275*M_1_PI*M_1_PI, 5*M_1_PI, 6, 10, 0.125 * M_1_PI};
    function<double(vector<double>)> bound_branin = bindBranin(usual_branin_a);

    // Definición de parámetros para la función objetivo de Six-Hump Camel Back
    vector<double> lowerbound_six_hump_camel_back{-3, -2};
    vector<double> upperbound_six_hump_camel_back{3, 2};

    // Definición de parámetros para la función objetivo de Shekel
    vector<vector<double>> usual_foxholes_a{
        {4.0, 4.0, 4.0, 4.0}
        ,{1.0, 1.0, 1.0, 1.0}
        ,{8.0, 8.0, 8.0, 8.0}
        ,{6.0, 6.0, 6.0, 6.0}
        ,{3.0, 7.0, 3.0, 7.0}
        ,{2.0, 9.0, 2.0, 9.0}
        ,{5.0, 3.0, 5.0, 3.0}
        ,{8.0, 1.0, 8.0, 1.0}
        ,{6.0, 2.0, 6.0, 2.0}
        ,{7.0, 3.6, 7.0, 3.6}
    };
    vector<double> usual_foxholes_c {
        0.1
        ,0.2
        ,0.2
        ,0.4
        ,0.4
        ,0.6
        ,0.3
        ,0.7
        ,0.5
        ,0.5
    };
    int foxholes_dimension = usual_foxholes_a[0].size();
    function<double(vector<double>)> bound_foxhholes = bindShekelFoxholes(usual_foxholes_a, usual_foxholes_c);


    vector<BenchmarkFunction> benchmark_functions = {
        { DeJong, vector<double>(dimensions, -5.12), vector<double>(dimensions, 5.12), "De Jong" },
        { AxisParallelHyperEllipsoid, vector<double>(dimensions, -5.12), vector<double>(dimensions, 5.12), "Axis Parallel Hyper Ellipsoid" },
        { RotatedHyperEllipsoid, vector<double>(dimensions, -65.536), vector<double>(dimensions, 65.536), "Rotated Hyper Ellipsoid" },
        { RosenbrockValley, vector<double>(dimensions, -2.048), vector<double>(dimensions, 2.048), "Rosenbrock Valley" },
        { Rastring, vector<double>(dimensions, -5.12), vector<double>(dimensions, 5.12), "Rastring" },
        { Schwefel, vector<double>(dimensions, -500), vector<double>(dimensions, 500), "Schwefel" },
        { Griewangk, vector<double>(dimensions, -600), vector<double>(dimensions, 600), "Griewangk" },
        { SumDifferentPower, vector<double>(dimensions, -1), vector<double>(dimensions, 1), "Sum of Different Power" },
        { bound_ackley, vector<double>(dimensions, -32.768), vector<double>(dimensions, 32.768), "Ackley" },
        { bound_langermann, vector<double>(langermann_dimension, -10), vector<double>(langermann_dimension, 10), "Langermann" },
        { bound_michalewicz, vector<double>(dimensions, 0), vector<double>(dimensions, M_PI), "Michalewicz" },
        { bound_branin, vector<double>(2, -10), vector<double>(2, 10), "Branin" },
        { GoldsteinPrice, vector<double>(2, -2), vector<double>(2, 2), "Goldstein-Price" },
        { SixHumpCamelBack, lowerbound_six_hump_camel_back, upperbound_six_hump_camel_back, "Six-Hump Camel" },
        { FifthDeJong, vector<double>(2, -65.536), vector<double>(2, 65.536), "Fifth De Jong" },
        { DropWave, vector<double>(2, -5.12), vector<double>(2, -5.12), "Drop Wave" },
        { Shubert, vector<double>(2, -5.12), vector<double>(2, -5.12), "Shubert" },
        { bound_foxhholes, vector<double>(foxholes_dimension, 0), vector<double>(foxholes_dimension, 10), "Shekel" }
    };

    vector<string> function_names = {"De Jong", "Axis Parallel Hyper Ellipsoid", "Rotated Hyper Ellipsoid", 
        "Rosenbrock Valley", "Rastring", "Schwefel", "Griewangk", "Sum of Different Power", "Ackley",
        "Langermann", "Michalewicz", "Branin", "Goldstein-Price", "Six-Hump Camel", "Fith De Jong", "Drop Wave", "Shubert",
        "Shekel"
    };

     // Evaluate the functions
     for (const auto& benchmark : benchmark_functions) {
        Result_of_Optimization(benchmark.func, benchmark.lower_bound, benchmark.upper_bound, population, iterations, repetitions, gen, benchmark.name);
    }

    return 0;
}