#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

// Función de DeJong
double DeJong(const std::vector<double>& x) {
  double sum = 0.0;
  for (double xi : x) sum += xi * xi;
  return sum;
}

// Función Hiperellipsoide Paralelo a los Ejes
double AxisParallelHyperEllipsoid(const std::vector<double>& x){
double sum = 0.0;
for (size_t i = 0; i < x.size(); ++i) {
  sum += i * x[i] * x[i];
}
return sum;
}

// Función de Hyperellipsoide Rotado
double RotatedHyperEllipsoid(const std::vector<double>& x){
double sum = 0.0;
double cumulative = 0.0;

for (size_t i = 0; i < x.size(); ++i){
  cumulative += x[i] * x[i];
  sum += cumulative;
}

return sum;
}

// Función Rosenbrok (Valle de Rosenbrock)
double RosenbrockValley(const std::vector<double>& x){
double sum = 0.0;

for (size_t i = 0; i < x.size() - 1; ++i){
  sum += 100* (x[i+1] - x[i]* x[i]) * (x[i+1] - x[i]* x[i]);
  sum += (1-x[i])*(1-x[i]);
}
return sum;
}

// Función de Rastring
double Rastring(const std::vector<double>& x){
double sum = 10 * x.size();

for (double xi : x){
  sum += xi*xi;
  sum += -10*cos(2*M_PI*xi);
}

return sum;
}

// Función de Schwefel
double Schwefel(const std::vector<double> x){
double sum = 0.0;

for (double xi: x){
  sum -= xi*sin(sqrt(abs(xi)));
}
return sum;
}

// Función de Griewangk
double Griewangk(const std::vector<double>& x){
double sum = 0.0;
double product = 1.0;

for (size_t i = 0; i <x.size(); ++i){
  sum += x[i] * x[i];
  product *= cos(x[i]/sqrt(i+1));
} 
sum /= 4000;
return sum - product + 1;
}

// Función Suma de Diferentes Potencias
double SumDifferentPower(const std::vector<double>& x){
double sum = 0.0;
for (size_t i = 0; i < x.size(); ++i){
  sum += pow(abs(x[i]), i+2);
}

return sum;
}

// Función Ackley
double Ackley(const std::vector <double>& x, const std::vector<double>& a){
if (a.size() != 3){
  throw std::invalid_argument("");
}
const int n = x.size();
if ( n == 0) return 0.0;
double mean_1 = 0.0, mean_2 = 0.0;

for (double xi : x){
  mean_1 += xi * xi;
  mean_2 += cos(a[2] * xi);
}

mean_1 /= n;
mean_2 /= n;

return -a[0] * exp(-a[1] * sqrt(mean_1)) - exp(mean_2) + a[0] + M_E;
}

// Función auxiliar para fijar parametros de la función de Ackley
std::function<double(std::vector<double>)> bindAckley(const std::vector<double>& a) {
return std::bind(Ackley, std::placeholders::_1, a);  // Bind 'a' and leave 'x' as the argument
}

//Función de Langermann
double Langermann(const std::vector<double>& x, const std::vector<std::vector<double>>& a, const std::vector<double>& c){

double sum = 0.0;
const size_t m = c.size();

for (size_t i = 0; i < m; ++i){
  double dist_sq = 0.0;

  for (size_t j = 0; j < x.size(); ++j){
    dist_sq += pow(x[j]-a[i][j], 2);
  }

  double exponent = -dist_sq/M_PI;
  double cosine = cos(M_PI * dist_sq);

  sum += c[i] * exp(exponent) * cosine;
}

return sum;
}

// Función auxiliar para fijar parametros de la función de Langermann
std::function<double(std::vector<double>)> bindLangermann(const std::vector<std::vector<double>>& a, const std::vector<double>& c) {
return std::bind(Langermann, std::placeholders::_1, a, c);  // std::Bind 'a' and 'c' and leave 'x' as the argument
}

// Función de Michalewicz
double Michalewicz(const std::vector<double>& x, const int& m){
double sum = 0.0;

for (size_t i = 0; i < x.size();++i){
  sum -= sin(x[i]) * pow(sin((i+1) * x[i]/M_PI), 2 * m);
}
return sum;
}

// Función auxiliar para fijar parametros de la función de Michalewicz
std::function<double(std::vector<double>)> bindMichalewicz(const int& m){
  return std::bind(Michalewicz, std::placeholders::_1, m);
}

// Función de Branin 
double Branin(const std::vector<double>& x, const std::vector<double>& a){

if (x.size() != 2) {
  throw std::invalid_argument("Branin function is only for two variables (x1, x2).");
} else if (a.size() != 6) {
  throw std::invalid_argument("Branin function requires only 6 arguments. ");
}

return a[0] * pow(x[1] - a[1] * x[0] * x[0] + a[2] * x[0] - a[3], 2) 
+ a[4] * (1 - a[5]) * cos(x[0]) + a[5];
}

// Función auxiliar para fijar parametros de la función de Branin
std::function<double(std::vector<double>)> bindBranin(const std::vector<double>& a) {
return std::bind(Branin, std::placeholders::_1, a);  // std::Bind 'a' and leave 'x' as the argument
}

// Función de Easom
double Easom(const std::vector<double> x) {
if (x.size() != 2){
  throw std::invalid_argument("La función de Easom solo toma dos variables.");
}
return -cos(x[0])*cos(x[1]) * exp(-(pow(x[0] - M_PI, 2) + pow(x[1] - M_PI, 2)));
}

// Función de Goldstein-Price
double GoldsteinPrice(const std::vector<double>& v) {
if (v.size() != 2) {
  throw std::invalid_argument("La función sólo toma dos variables.");
}

double x = v[0];
double y = v[1];

return (1 + pow(x + y + 1, 2) * (19 - 14 * x + 3 * pow(x, 2) - 14 * y + 6 * x * y + 3 * pow(y, 2))) *
      (30 + pow(2 * x - 3 * y, 2) * (18 - 32 * x + 12 * pow(x, 2) + 48 * y - 36 * x * y + 27 * pow(y, 2)));
}

// Función Six-Hump Camel Back
double SixHumpCamelBack(const std::vector<double> x){
if (x.size() != 2){
  throw std::invalid_argument("La función sólo toma dos variables.");
}
double x1 = x[0];
double x2 = x[1];

return (4 - 2.1 * pow(x1, 2) + pow(x1, 4) / 3.0) * pow(x1, 2) + x1 * x2 +
        (-4 + 4 * pow(x2, 2)) * pow(x2, 2);
}

//Quinta función de DeJong
double FifthDeJong(const std::vector<double> x){
if (x.size() != 2){
  throw std::invalid_argument("La función sólo toma dos variables.");
}
double x1 = x[0];
double x2 = x[1];
double sum = 0.0;

for (int i = -2; i <= 2; i++) {
  for (int j = -2; j <= 2; j++) {
    sum += 1 / (5 + (i + 2) + j + 3 + pow(x1 - 16 * j, 6) + pow(x2 - 16 * i, 6));
  }
}
return 1 / (0.002 + sum);
}

// Función de Dropwave
double DropWave(const std::vector<double> x) {
if (x.size() != 2){
  throw std::invalid_argument("La función sólo toma dos variables.");
}
return -(1 + cos(12 * sqrt(x[1] + pow(x[1], 2)))) /
        (((pow(x[0], 2) + pow(x[1], 2)) / 2) + 2);
}

// Función de Shubert
double Shubert(const std::vector<double> x) {
double suma1 = 0;
double suma2 = 0;

for (int i = 1; i <= 5; i++) {
  suma1 += i * cos((i + 1) * x[0] + 1);
  suma2 += i * cos((i + 1) * x[1] + 1);
}
return -(suma1 * suma2);
}

// Función de hoyos de zorros de Shekel
double ShekelFoxholes(const std::vector<double>& x, const std::vector<std::vector<double>>& a, const std::vector<double>& c) {
if (x.size() != a[0].size()) {
    throw std::invalid_argument("Dimension mismatch: x must have the same size as the rows of a.");
}
if (c.size() < a.size()) {
    throw std::invalid_argument("Dimension mismatch: c must have at least as many elements as a has rows.");
}

double suma1 = 0.0;

for (size_t i = 0; i < a.size(); ++i) {
    double suma2 = 0.0;
    for (size_t j = 0; j < x.size(); ++j) {
        suma2 += pow(x[j] - a[i][j], 2);
    }
    suma2 += c[i];
    suma1 -= 1.0 / suma2;
}
return suma1;
}

// Función auxiliar para fijar parametros de la función de hoyos de zorros de Shekel
std::function<double(std::vector<double>)> bindShekelFoxholes(const std::vector<std::vector<double>>& a, const std::vector<double>& c){
return std::bind(ShekelFoxholes, std::placeholders::_1 , a, c);
}
