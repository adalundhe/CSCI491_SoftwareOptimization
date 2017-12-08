#include "../Clock.hpp"
#include <iostream>
#include <omp.h>

"""NOTE: Compile using -fopenmp"""

const unsigned int R = 1<<10;
const unsigned int C = 1<<11;

const bool prev_and_alive_neighbors_to_next[2][9] = {
  {false, false, false, true, false, false, false, false, false},
  {false, false, false, true, true, false, false, false, false}
};

void advance_single(bool*next, bool*board, int r, int c){
  unsigned char living_neighbors = 0;

  for(int i = -1; i<=1; ++i)
    for(int j=-1; j<=1; ++j)
      living_neighbors += (board[(r+i) * (C+2) + (c+j)] &1);

  bool is_this_cell_living = board[r*(C+2)+c];

  next[r*(C+2)+c] = prev_and_alive_neighbors_to_next[is_this_cell_living][living_neighbors];

}


void advance(bool*next, bool*board){
  #pragma omp parallel for collapse(2)
  for(unsigned int i=1; i<R+1; ++i)
    for(unsigned int j=1; j<C+1; ++j)
        advance_single(next, board, i, j);
}

void print_board(const bool*board){
  for(unsigned int i=1; i<R+1; ++i){
    for(unsigned int j=1; j<C+1; ++j)
      std::cout << int(board[i * (C+2) + j]);
    std::cout << std::endl;
  }
}

int main(int argc, char**argv){
  if(argc == 3){
    unsigned int NUM_REPS = atoi(argv[1]);
    bool print = bool(atoi(argv[2]));

    srand(0);
    bool*board = (bool*)calloc((R+2)*(C+2), sizeof(bool));
    bool*next = (bool*)calloc((R+2)*(C+2), sizeof(bool));

    for(unsigned int i=1; i<R+1; ++i)
      for(unsigned int j=1; j<C+1; ++j)
        next[i*(C+2)+j] = (rand()%2 == 0);

    if(print)
      print_board(next);

    Clock c;

    for(unsigned int rep=0; rep<NUM_REPS; ++rep){
      std::swap(next, board);
      advance(next, board);
    }


    c.ptock();

    if(print)
      print_board(next);
  }
  else
    std::cerr << "usage game-of-life <generations> <0: don't print, 1: print>"<<std::endl;

  return 0;
}
