#include "../Clock.hpp"
#include <functional>
#include <set>
#include <unordered_map>

class SimpleRandomGenerator {
  private:
    unsigned long _random_value;

    static unsigned long ROL(unsigned long v, unsigned char shift){
      return ((((v) >> ((sizeof(v) * 8) - (shift))) | ((v) << (shift))));
    }
  public:
    SimpleRandomGenerator(unsigned long seed):
      _random_value(seed)
    {}

    unsigned long next(){
      _random_value = _random_value * 214013L + 2531011L;
      _random_value = ROL(_random_value, 16);
      return _random_value;
    }
};

template<typename T>
class UniversalSetHash{
  public:
    static const unsigned int big_prime = 18446744073709551557ul;

    std::size_t operator() (const std::set<T> & s) const {
      SimpleRandomGenerator srg(0);

      std::hash<T> single_hash;
      std::size_t combined_hash = 0;

      for(const T & obj : s) {
        unsigned long single = (single_hash(obj) * srg.next()) & big_prime;
        combined_hash += single;
      }
      combined_hash += (s.size() * srg.next()) % big_prime;
      return combined_hash;
    }
};

int main(){
  const unsigned long NUMBER_SETS = 1<<18;
  const unsigned long SET_INSERTIONS = 1<<8;
  const unsigned long MAX_ELEMENT_PLUS_ONE = 1<<8;

  srand(0);

  Clock c;
  std::unordered_map<std::set<unsigned int>, int, UniversalSetHash<unsigned int>> collection;

  for(unsigned int i=0; i<NUMBER_SETS; ++i){
    std::set<unsigned int> st;
    for(unsigned int j=0; j<SET_INSERTIONS; ++j)
      st.insert(rand() % MAX_ELEMENT_PLUS_ONE);
    collection[st] = st.size();
  }


  for(auto set : collection){
    if(set.first.size()%2 == 1){
      set.second = 0;
    }
  }

  c.ptock();
}
