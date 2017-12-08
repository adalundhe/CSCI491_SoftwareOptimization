#include "./vector.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include "../Clock.hpp"

struct StrAndInt {
  std::string key;
  long int val;
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
  const unsigned long N = 100000;


  Vector<StrAndInt> vec;
  std::map<std::string , long int> std_map;
  std::unordered_map<std::string, long int> unordered_m;
  std::vector<std::string> names;
  std::vector<std::pair<std::string, long int>> vec_std;

  for(unsigned int i=1; i<=N; ++i){
    std::string name = random_string();
    vec.push_back({name, long(i)});
    vec_std.push_back(std::make_pair(name, i));

    names.push_back(name);
    std_map[name] = i;
    unordered_m[name] = i;

  }

  std::sort(vec_std.begin(), vec_std.end());

  Clock c;
  unsigned long sum = 0;
  for(unsigned int i=0; i<N; ++i){
    if(vec[i].key[0] == 'A'){
      sum += vec[i].val;
    }
  }

  c.ptock();
  std::cout<<"SUM: "<<sum<<std::endl;

  Clock p;

  unsigned long sum_two = 0;
  for(const std::string & name : names){
    if(name[0] == 'A'){
        sum_two += std_map[name];
    }
  }
  p.ptock();
  std::cout<<"SUM TWO: "<<sum_two<<std::endl;

  Clock z;

  unsigned long sum_three = 0;
  for(const std::string & name : names){
    if(name[0] == 'A'){
      sum_three += unordered_m[name];
    }
  }

  z.ptock();
  std::cout<<"SUM THREE: "<<sum_three<<std::endl;

  Clock q;

  unsigned long sum_four = 0;
  for(unsigned int i=0; i<N; ++i){
    if(vec_std[i].first[0] == 'A'){
      sum_four += vec_std[i].second;
    }
  }

  q.ptock();
  std::cout<<"SUM FOUR: "<<sum_four<<std::endl;
}
