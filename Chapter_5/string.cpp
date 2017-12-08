#include "./clock.hpp"
#include <fstream>
#include <string>
#include <bitset>
#include <iostream>
using namespace std;


const unsigned char nuc_to_code[] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 1, 255, 3, 255, 255, 255, 0, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 2};

constexpr unsigned int NUCLEOTIDES_PER_BLOCK = sizeof(unsigned long) * 8 /2;

void bit_pack(unsigned long * & result, unsigned long & num_blocks, const std::string & genome){
  num_blocks = genome.size() /NUCLEOTIDES_PER_BLOCK;

  if(num_blocks * NUCLEOTIDES_PER_BLOCK != genome.size()) ++ num_blocks;

  result = (unsigned long*)calloc(num_blocks, sizeof(unsigned long));

  unsigned long i=0;

  for (unsigned long long block=0; block<num_blocks-1; ++block){
    unsigned long long next_block = 0;

    for(unsigned char j=0; j<NUCLEOTIDES_PER_BLOCK; ++j, ++i){
      next_block <<=2;
      next_block |= nuc_to_code[genome[i]];
    }
    result[block] = next_block;
  }

  unsigned long long next_block = 0;
  for(unsigned char j=0; j<NUCLEOTIDES_PER_BLOCK; ++j, ++i){
    next_block <<= 2;
    if(i< genome.size()) next_block |= nuc_to_code[genome[i]];
  }

  result[num_blocks-1] = next_block;
}

unsigned long* packed_complement(const unsigned long*packed_genome, unsigned long num_blocks){
  unsigned long * result = (unsigned long*)calloc(num_blocks, sizeof(unsigned long));

  for(unsigned long long block=0; block<num_blocks; ++block) result[block] = ~packed_genome[block];

  return result;
}

int main(){

  ifstream fin("reallybig.txt");
  string genome;

  char base;
  while(fin >> base) genome += base;

  cout<<"String loaded..."<<endl;
  unsigned long*packed;
  unsigned long num_blocks;
  bit_pack(packed, num_blocks, genome);
  cout<<"Bit packed: Step 1"<<endl;

  Clock c;

  unsigned long*comp = packed_complement(packed, num_blocks);

  c.ptock();

  for(unsigned int i=0; i<2*NUCLEOTIDES_PER_BLOCK; ++i) cout<<genome[i]<< " ";
  cout<< "..." << endl;

  for(unsigned int i=0; i<2; ++i){
    cout<< bitset<8 * sizeof(unsigned long)>(packed[i]);
    cout<<"..."<<endl;
  }

  for(unsigned int i=0; i<2; ++i) cout<<bitset<8 * sizeof(unsigned long)>(comp[i]);
  cout<< "..." <<endl;

  char ordered_nucleotides[] = {'G', 'A', 'T', 'C'};

  for(unsigned int i=0; i<2; ++i){
    unsigned long mask = -1ul & ~((-1ul)>>2);

    for(unsigned char j=0; j<NUCLEOTIDES_PER_BLOCK; ++j){
      unsigned long shifted_bit_pair = comp[i] & mask;
      cout<< ordered_nucleotides[shifted_bit_pair >> 2 * (NUCLEOTIDES_PER_BLOCK-j-1)] << " ";
      mask >>= 2;
    }
  }

  cout<<"..."<<endl;
  return 0;

}
