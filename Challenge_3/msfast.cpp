// Hello Oliver!
// Please compile as folow: g++ std=c++11 -O3 -fopenmp msfast.cpp!
// Thanks for an awesome class.

#include "../Clock.hpp"
#include <math.h>
#include <exception>
#include <omp.h>
#include <immintrin.h>

__attribute__((noinline))
static void multiply(double*__restrict A, double*__restrict B, double*__restrict C, const unsigned long N){
  constexpr unsigned long T = 16;
  unsigned long I,J,K,i,j,k;
  double sum;

  #pragma omp parallel for collapse(3)private(I,J,K,i,j,k,sum)shared(A,B,C)
  for(I=0; I<N; I+=T)
    for(J=0; J<N; J+=T)
      for(K=0; K<N; K+=T)
        for(i=I; i<std::min(I + T, N); ++i)
          for(j=J; j<std::min(J + T, N); ++j)
            for(k=K; k<std::min(K+T, N); k += 4){
              double outdata[4] = {0.0, 0.0, 0.0, 0.0};
              __m256d a = _mm256_set_pd(A[i * N + k], A[i * N + (k + 1)], A[i * N + (k + 2)], A[i * N + (k + 3)]);
              __m256d b = _mm256_set_pd(B[k * N + j], B[(k + 1) * N + j ], B[(k + 2) * N + j], B[(k + 3) * N + j]);
              __m256d c = _mm256_mul_pd(a, b);
               _mm256_storeu_pd(outdata, c);

              C[i * N + j] += outdata[0] + outdata[1] + outdata[2] + outdata[3];
            }

}

int main() {
  constexpr unsigned long N=1<<12;

  srand(0);

  double*A=new double[N*N];
  double*B=new double[N*N];

  for (unsigned long i=0; i<N*N; ++i)
    A[i] = (rand() % 1000)/999.0;;

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
