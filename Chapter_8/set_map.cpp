#include <set>
#include <iostream>
#include <map>
#include "../Clock.hpp"

int main(){
  const unsigned long NUMBER_SETS = 1<<18;
  const unsigned long SET_INSERTIONS = 1<<8;
  const unsigned long MAX_ELEMENT_PLUS_ONE = 1<<8;

  srand(0);

  std::map<std::set<unsigned int>, int> map_set;

  Clock c;
  for(unsigned int i=0; i<NUMBER_SETS; ++i){
    std::set<unsigned int> new_set;
    for(unsigned int j =0; j<SET_INSERTIONS; ++j)
      new_set.insert(rand() % MAX_ELEMENT_PLUS_ONE);
    map_set[new_set] = new_set.size();
  }

  for(auto set_key : map_set){
    if(set_key.second%2 == 1){
      map_set[set_key.first] = 0;
    }
  }

  c.ptock();

  return 0;
}
