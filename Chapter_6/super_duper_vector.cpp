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
      if (_capacity == _size) {
        _capacity += (_capacity >> 1) + 1;
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
