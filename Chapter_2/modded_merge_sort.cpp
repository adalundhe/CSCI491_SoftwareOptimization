#include "./clock.hpp"
#include <iostream>

void selection_sort(unsigned long*source, const unsigned long n) {
  for (unsigned long i=0; i<n; ++i)
    for (unsigned long j=i+1; j<n; ++j)
      if (source[j] < source[i])
      std::swap(source[i], source[j]);
}


void merge_sort(unsigned long*source, unsigned long*buffer, unsigned long*source_2,const unsigned long n){
  if(n <= 4096){
    selection_sort(source, n);
    return;
  }

  merge_sort(source, buffer, source_2, n/2);
  merge_sort(source_2, buffer, source_2, n-n/2);

  unsigned long i=0, j=0, buffer_ind=0;
  while(i < n/2 && j < (n-n/2)){
    if (source[i] < source_2[j]){
      buffer[buffer_ind] = source[i];
      ++i;
    }
    else {
      buffer[buffer_ind] = source_2[j];
      ++j;
    }
    ++buffer_ind;
  }

  for (; i<n/2; ++i, ++buffer_ind)
    buffer[buffer_ind] = source[i];
  for (; j<n-n/2; ++j, ++buffer_ind)
    buffer[buffer_ind] = source_2[j];

  for (i=0; i<n; ++i){
    source[i] = buffer[i];
  }
}

int main(int argc, char**argv){
  if(argc == 2){
    const unsigned long N = atoi(argv[1]);
    unsigned long*x = new unsigned long[N];
    unsigned long*buffer = new unsigned long[N];
    unsigned long*source_2 = x + N/2;

    for (unsigned long i=0; i<N; ++i)
      x[i] = N-i;

    Clock c;
    merge_sort(x, buffer, source_2, N);
    c.ptock();
  }
  else
    std::cerr << "Usage: srot <n>" << std::endl;
  return 0;
}
