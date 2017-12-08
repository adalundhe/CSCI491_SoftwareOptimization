#include "../Clock.hpp"
#include <set>

int main(){
  const unsigned long NUMBER_SETS = 1<<18;
  const unsigned long SET_INSERTIONS = 1<<8;
  const unsigned long MAX_ELEMENT_PLUS_ONE = 1<<8;

  srand(0);

  Clock c;
  std::set<std::set<unsigned int>> collection_of_sets;

  for(unsigned int i=0; i<NUMBER_SETS; ++i){
    std::set<unsigned int> st;
    for(unsigned int j=0; j<SET_INSERTIONS; ++j){
      st.insert(rand() % MAX_ELEMENT_PLUS_ONE);
    }
    collection_of_sets.insert(st);
  }

  for(auto set : collection_of_sets){
    if(set.size()%2 == 1){
      set.clear();
    }
  }

  c.ptock();
}
