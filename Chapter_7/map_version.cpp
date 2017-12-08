#include <iostream>
#include <map>
#include "../Clock.hpp"
#include "./vector.hpp"

struct StrAndInt {
  char* name;
  int val;
};


char* random_string(){
  static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  const unsigned int len=32;
  char *s = (char*)malloc(32 * sizeof(char));

  for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

  s[len] = 0;
  return s;
};

int main(){

  srand(0);

  const unsigned long N = 1<<20; // Approx 10^5
  std::cout<<N<<std::endl;

  std::map<char* , int> vars_to_age;
  Vector<StrAndInt> vec;

  for(unsigned long i=0; i<N; ++i){
    char* var = random_string();
    int age = rand() % 1000 + 1;
    vars_to_age[var] = age;
    vec.push_back({var, age});
  }

  // Standard way to iterate through a map.
  unsigned long sum = 0;

  Clock c;

  // for(auto iter=vars_to_age.begin(); iter != vars_to_age.end(); ++iter){
  for(const std::pair<char*, int> & p : vars_to_age){
    // *iter will be a std::pair<std::string, int>
    // (*iter).first will be std::string
    // (*iter).second will be int
    // iter-> first will be std::string
    // iter-> second will be int

    if(p.first[0] == 'A'){
      sum += p.second;
    }
  }

  unsigned long avg = sum/N;

  c.ptock();
  std::cout<<"AVG AGE: "<<avg<<std::endl;

  Clock d;

  unsigned long sum_two = 0;

  for(unsigned int i=0; i<vec._size; ++i){
    if(vec[i].name[0] == 'A'){
      sum_two += vec[i].val;
    }
  }

  unsigned long avg_two = sum_two/N;

  d.ptock();
  std::cout<<"AVG AGE TWO: "<<avg_two<<std::endl;


}
