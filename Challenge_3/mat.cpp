#include "../Clock.hpp"

__attribute__((noinline))
static void multiply(double*__restrict mtx_A, double*__restrict mtx_B, double*__restrict mtx_C, const unsigned N){
  for(unsigned long i=0; i<N; ++i)
    for(unsigned long j=0; j<N; ++j){
      double sum = 0;
      for(unsigned long k=0; k<N; ++k) sum += mtx_A[i * N + k] * mtx_B[k * N + j];

      mtx_C[i * N + j] = sum;
    }


}

int main() {
  constexpr unsigned N=1<<1;

  srand(0);

  double*A=new double[N*N];
  double*B=new double[N*N];

  for (unsigned long i=0; i<N*N; ++i){
        A[i] = (rand() % 1000)/999.0;
        std::cout<<A[i]<<" ";
  }
  std::cout<<std::endl;

  for (unsigned long i=0; i<N*N; ++i){
    B[i] = (rand() % 1000)/999.0;
    std::cout<<B[i]<<" ";
  }
  std::cout<<std::endl;

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
