#include <iostream>
#include <random>

double funcInt(double varInd1, double varInd2) {
  return varInd1 + varInd2;
}

double monteCarlo(double limInf1, double limSup1, double limInf2, double limSup2, int numale, double (*func)(double, double)) {
  
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist1(limInf1, limSup1);
  std::uniform_real_distribution<double> dist2(limInf2, limSup2);
  
  double suma = 0.0;

  for (int i = 0; i < numale; ++i) {
    double aleatorio1 = dist1(mt);
    double aleatorio2 = dist2(mt);
    
    double funcEvaluada = func(aleatorio1, aleatorio2);
      
    suma += funcEvaluada;
  }
  double aproximación = ((limSup1 - limInf1) * (limSup2 - limInf2)) * (suma / numale);

  return aproximación;
}
    
int main() {
  double resultado = monteCarlo(0.0, 1.0, -1.0, 2.0, 1000, funcInt);
  
  std::cout << "El resultado de la integral es: " << resultado << std::endl;

  return 0;
}

