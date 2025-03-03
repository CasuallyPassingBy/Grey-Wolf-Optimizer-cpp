#ifndef FILE_H
#define FILE_H

#include <vector>
#include <functional>  

double DeJong(const std::vector<double>& x);
double AxisParallelHyperEllipsoid(const std::vector<double>& x);
double RotatedHyperEllipsoid(const std::vector<double>& x);
double RosenbrockValley(const std::vector<double>& x);
double Rastring(const std::vector<double>& x);
double Schwefel(const std::vector<double> x);
double Griewangk(const std::vector<double>& x);
double SumDifferentPower(const std::vector<double>& x);
std::function<double(std::vector<double>)> bindAckley(const std::vector<double>& a);
std::function<double(std::vector<double>)> bindLangermann(const std::vector<std::vector<double>>& a, const std::vector<double>& c);
std::function<double(std::vector<double>)> bindMichalewicz(const int& m);
std::function<double(std::vector<double>)> bindBranin(const std::vector<double>& a);
double Easom(const std::vector<double> x);
double GoldsteinPrice(const std::vector<double>& v);
double SixHumpCamelBack(const std::vector<double> x);
double FifthDeJong(const std::vector<double> x);
double DropWave(const std::vector<double> x);
double Shubert(const std::vector<double> x);
std::function<double(std::vector<double>)> bindShekelFoxholes(const std::vector<std::vector<double>>& a, const std::vector<double>& c);

#endif
