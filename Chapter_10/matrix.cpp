#include <iostream>
#include <time.h>

int main(){
  unsigned int i = 10;
  unsigned int j = 10;
  unsigned int n = 10;
  double *dist2 = (double*)malloc(n * n * sizeof(double));
  double *dist = (double*)malloc(n * n * sizeof(double));

  srand(time(NULL));

  for(unsigned int i=0; i<n; ++i){
    for(unsigned int j=0; j<n; ++j){
        dist[i * n + j] = rand() % 10000;
        dist2[i * n + j] = dist[i * n + j];
    }
  }

  for(unsigned int k=0; k<n; ++k){
    for(unsigned int i=0; i<n; ++i){
      for(unsigned int j=0; j<n; ++j){
          dist[i * n +j] = std::min(dist[i * n + j], dist[i * n + k] + dist[k * n + j]);
          std::cout<<"MTX 1: "<<dist[i * n + j]<<std::endl;
      }
    }
  }

  for(unsigned int k=0; k<n; ++k){
    for(unsigned int j=0; j<n; ++j){
      for(unsigned int i=0; i<n; ++i){
        dist2[i * n + j] = std::min(dist2[i * n + j], dist2[i * n + k] + dist2[k * n + j]);
        std::cout<<"MTX 2: "<<dist2[i * n + j]<<std::endl;
      }
    }
  }
}
