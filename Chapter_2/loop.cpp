#include "./clock.hpp"

const unsigned int N=1<<24;

int main() {
  Clock c;
  double tot=0.0;

  for(unsigned int i=0; i<N; ++i)
    tot += 1;
  c.ptock();

  std::cout << tot << std::endl;
  return 0;
}
