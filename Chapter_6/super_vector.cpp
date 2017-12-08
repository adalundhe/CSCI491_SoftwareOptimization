#include <stdio.h>
#include <math.h>
#include <exception>
#include "./clock.hpp"
#include <vector>

template <typename T>
class Vector {
  private:
    unsigned long _size;
    unsigned long _capacity;
    T*__restrict _data;
  public:
    Vector():
      _size(0),
      _capacity(4),
      _data((T*) malloc(_capacity * sizeof(T)))
    {}

    Vector(unsigned long sz):
      _size(sz),
      _capacity(sz),
      _data((T*) malloc(_capacity * sizeof(T)))
    {}

    ~Vector() {
      free(_data);
    }

    void push_back(const T & element) {
      unsigned long grow_by = _capacity/log2(1 + _capacity);
      if (_capacity == _size) {
        _capacity += (_capacity + grow_by) + 1;
        _data  = (T*)realloc(_data, _capacity * sizeof(T));
        if(_data == NULL){
          throw std::domain_error("Reallocation return NULL. Memory error.");
        }
      }

      _data[_size] = element;
      ++_size;
    }

    const T & operator [](unsigned long i) const {
      return _data[i];
    }

    T & operator [](unsigned long i){
      return _data[i];
    }
};

int main(){
  const unsigned long N = 256000;
  const unsigned long REPS = 128;

  Clock c;

  for(unsigned int r=0; r<REPS; ++r){
      Vector<int> vec;
      for(unsigned int i=0; i<N; ++i){
        vec.push_back(i);
      }
  }

  c.ptock();

  Clock c2;

  for(unsigned int r=0; r<REPS; ++r){
    std::vector<int> v_test;
    for(unsigned int i=0; i<N; ++i){
      v_test.push_back(i);
    }
  }

  c2.ptock();

  for (unsigned long i=0; i<N*N; ++i)
    std::cout << C[i] << " ";
  std::cout << std::endl;

  ~A;
  ~B;
  ~C;

  return 0;
};
