#include "../Clock.hpp"
#include <math.h>
#include <exception>
#include <omp.h>

__attribute__((noinline))
static void multiply(double*__restrict A, double*__restrict B, double*__restrict C, const unsigned long N){
  constexpr unsigned long T = 16;
  unsigned long I,J,K,i,j,k;
  double sum;

  #pragma omp parallel for collapse(2) private(I,J,K,i,j,k,sum)shared(A,B,C)
  for(I=0; I<N; I+=T)
    for(J=0; J<N; J+=T)
      for(K=0; K<N; K+=T)
        for(i=I; i<std::min(I + T, N); ++i)
          for(j=J; j<std::min(J + T, N); ++j){
            sum = 0;
            for(k=K; k<std::min(K+T, N); ++k)
              sum += A[i * N + k] * B[k * N + j];
            C[i * N + j] = C[i * N +j] + sum;
          }
}

int main() {
  constexpr unsigned long N=1<<12;

  srand(0);

  double*A=new double[N*N];
  double*B=new double[N*N];

  for (unsigned long i=0; i<N*N; ++i)
    A[i] = (rand() % 1000)/999.0;
  for (unsigned long i=0; i<N*N; ++i)
    B[i] = (rand() % 1000)/999.0;

  double*C=new double[N*N];

  Clock c;

  // TODO: Compute matrix product in C:
  // C = A*B, means
  // C[i,j] = A[i,0]*B[0,j] + A[i,1]*B[1,j] + ... + A[0,N-1]*B[N-1,j]


  multiply(A,B,C,N);

  c.ptock();

  for (unsigned long i=0; i<N*N; ++i)
    std::cout << C[i] << " ";
  std::cout << std::endl;

  return 0;
}
