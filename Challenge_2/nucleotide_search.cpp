/*
Sean Corbett
CSCI 491 Project 2
Nucleotide Search
*/

// Please compile using g++ -std=c++1 -O3 nucleotide_searh.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Clock.hpp"

int find_reads(const std::vector<std::string> reads_in, const std::string genome_in){

  std::vector<std::pair<std::string, std::vector<std::size_t>>> positions;
  for(auto read :reads_in){
      std::vector<std::size_t> read_pos;
      std::size_t pos = genome_in.find(read,0);
      while(pos != std::string::npos){
        read_pos.push_back(pos);
        pos = genome_in.find(read, pos +1);
      }

      positions.push_back(std::make_pair(read,read_pos));
  }

  for(auto read : positions){
    std::cout<<read.first;
    for(auto pos : read.second){
      std::cout<<" "<<pos;
    }
    std::cout<<std::endl;
  }

  return 0;

}

int main(int argc, char**argv){

    std::string main_genome;
    std::string genome_in;
    std::string read_line;
    std::vector<std::string> reads;
    std::ifstream f_genome;
    std::ifstream f_reads;

    f_genome.open(argv[1]);
    while(std::getline(f_genome, main_genome))
    {
      genome_in.append(main_genome);
    }

    f_genome.close();


    f_reads.open(argv[2]);
    while(std::getline(f_reads, read_line))
    {
      reads.push_back(read_line);
    }
    f_reads.close();

    Clock c;

    find_reads(reads, genome_in);

    c.ptock();

  return 0;
}
