#include <set>
#include <unordered_set>
#include <functional>
#include "../Clock.hpp"

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
class HashSet{
  private:
    const std::set<T> hash_set;
    std::size_t gen_hash(const std::set<T> & s) const {
      SimpleRandomGenerator srg(0);
      static const unsigned int big_prime = 18446744073709551557ul;
      std::hash<T> single_hash;
      std::size_t combined_hash = 0;

      for(const T & obj : s) {
        unsigned long single = (single_hash(obj) * srg.next()) % big_prime;
        combined_hash += single;
      }
      combined_hash += (s.size() * srg.next()) % big_prime;

      return combined_hash;
    }
  public:
    const std::size_t _hash;
    HashSet(const std::set<T> & s):
      _hash(gen_hash(s)),
      hash_set(s)
    {};
    std::set<T> get_all() const{
      return hash_set;
    };
    T get(T & i) const{
      for(const T & el : hash_set){
        if(el == i){
          return el;
        }
      }
    };
    std::set<T> clear(){
      std::set<T> *new_set;
      std::set<T> clear_set;
      new_set = (std::set<T>*)(&hash_set);
      *new_set = clear_set;
      return hash_set;
    };
    unsigned int size() const{
      return hash_set.size();
    };
    bool operator==(const HashSet &rhs) const {
        return rhs._hash == _hash;
    }
};

template<typename T>
class UniversalSetHash{
  public:
    std::size_t operator() (const HashSet<T> & s) const {
      return s._hash;
    }
};

int main(){
  const unsigned long NUMBER_SETS = 1<<18;
  const unsigned long SET_INSERTIONS = 1<<8;
  const unsigned long MAX_ELEMENT_PLUS_ONE = 1<<8;

  srand(0);

  Clock c;
  std::unordered_set<HashSet<unsigned int>, UniversalSetHash<unsigned int>> collection;

  for(unsigned int i=0; i<NUMBER_SETS; ++i){
    std::set<unsigned int> st;
    for(unsigned int j=0; j<SET_INSERTIONS; ++j)
      st.insert(rand() % MAX_ELEMENT_PLUS_ONE);

    HashSet<unsigned int> h_set(st);
    collection.insert(h_set);
  }

  for(auto h_set : collection){
    if(h_set.size()%2 == 1){
      h_set.clear();
    }
  }

  c.ptock();


}
