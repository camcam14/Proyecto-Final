#include <iostream>
#include <random>

double funcInt(double varInd1, double varInd2) {
 return (varInd1 * varInd1) * (varInd2 * varInd2 * varInd2);
}

double sustfunc(double varInd1) {
  return varInd1 * varInd1;
}

double monteCarlo(double limInf1, double limSup1, int numale, double (*func1)(double), double (*func)(double, double)) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist1(limInf1, limSup1);

  double suma = 0.0;
  double limInf2 = 0.0;
  double limSup2 = 1.0;
  
  for (int i = 0; i < numale; ++i) {
     double aleatorio1 = dist1(mt);
    
     limInf2 = func1(aleatorio1);

     std::uniform_real_distribution<double> dist2(limInf2, limSup2);
     double aleatorio2 = dist2(mt);

     double funcEvaluada = func(aleatorio1, aleatorio2);
      
     suma += (limSup2 - limInf2) * funcEvaluada;
    }
    double aproximación = (limSup1 - limInf1) * (suma / numale);
    
    return aproximación;
}

int main() {
  double resultado = monteCarlo(-1.0, 1.0, 1000, sustfunc, funcInt);
  
  std::cout << "El resultado de la integral es: " << resultado << std::endl;
  
  return 0;
}
