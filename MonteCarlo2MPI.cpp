
#include <iostream>
#include <random>
#include <mpi.h>

double funcInt(double varInd1, double varInd2) {
 return (varInd1 * varInd1) * (varInd2 * varInd2 * varInd2);
}

double sustfunc(double varInd1) {
  return varInd1 * varInd1;
}

double monteCarlo(double limInf1, double limSup1, int numale,
                  double (*func1)(double), double (*func)(double, double),
                  int rank, int size) {

  double suma = 0.0;
  double sumaTotal = 0.0;
  double limSup2 = 1.0;

  std::random_device rd;
  std::mt19937 mt(rd() + rank);
  std::uniform_real_distribution<double> dist1(limInf1, limSup1);

  int numaleLocal = numale / size;

  if (rank < numale % size) {
    numaleLocal++;
  }

  for (int i = 0; i < numaleLocal; ++i) {
     double aleatorio1 = dist1(mt);

     double limInf2 = func1(aleatorio1);

     std::uniform_real_distribution<double> dist2(limInf2, limSup2);

     double aleatorio2 = dist2(mt);

     double funcEvaluada = func(aleatorio1, aleatorio2);

     suma += (limSup2 - limInf2) * funcEvaluada;
  }

  MPI_Reduce(&suma, &sumaTotal, 1, MPI_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);

  double aproximación = 0.0;

  if (rank == 0) {
    aproximación = (limSup1 - limInf1) * (sumaTotal / numale);
  }

  return aproximación;
}

int main(int argc, char* argv[]) {

  MPI_Init(&argc, &argv);

  int rank;
  int size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_Barrier(MPI_COMM_WORLD);
  double tiempoInicio = MPI_Wtime();

  double resultado = monteCarlo(-1.0, 1.0, 1000000,
                                sustfunc, funcInt, rank, size);

  double tiempoFinal = MPI_Wtime();

  double tiempoLocal = tiempoFinal - tiempoInicio;
  double tiempoTotal = 0.0;

  MPI_Reduce(&tiempoLocal, &tiempoTotal, 1, MPI_DOUBLE, MPI_MAX, 0,
             MPI_COMM_WORLD);

  if (rank == 0) {
    std::cout << "Resultado de la integral: " << resultado << std::endl;
    std::cout << "Numero de procesos: " << size << std::endl;
    std::cout << "Tiempo de ejecucion: " << tiempoTotal << " segundos" << std::endl;
  }

  MPI_Finalize();

  return 0;
}

