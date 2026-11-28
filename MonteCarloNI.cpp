#include <iostream>
#include <cmath>
#include <vector>
#include <random> 

double funcInt(std::vector<double> varInd) {
  double sumaint = 0.0;
  std::vector<double> a = {1.0, 0.5,0.2,0.2,0.2};

  for(int i = 0; i < 5; ++i) {
    double sumaint2 = 0.0;
    for(int j = 0; j < 5; ++j) {
      if(j != i){
        sumaint2 += varInd[j];
      }
    }
    sumaint += 0.5 * a[i] * (varInd[i] * varInd[i]) * ( 2.0 + std::sin(sumaint2));
  }

  return std::exp(sumaint);
}
  
double monteCarlo(double limInf, double limSup, int numale, double (*func)(std::vector<double>)) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(limInf, limSup);
  
  double suma = 0.0;
  std::vector<double> varInd(5);

  for (int i = 0; i < numale; ++i) {
    varInd[0] = dist(mt);
    varInd[1] = dist(mt);
    varInd[2] = dist(mt);
    varInd[3] = dist(mt);
    varInd[4] = dist(mt);

    double funcEvaluada = func(varInd);
 
    suma += funcEvaluada;
  }
    double aproximación = ((limSup - limInf) * (limSup - limInf) * (limSup - limInf) * (limSup - limInf) * (limSup - limInf)) * (suma / numale);
 
    return aproximación;
}
 
int main() {
  double resultado = monteCarlo(0.0, 1.0, 100000, funcInt);
  
  std::cout << "El resultado de la integral es: " << resultado << std::endl;

  return 0;
}
