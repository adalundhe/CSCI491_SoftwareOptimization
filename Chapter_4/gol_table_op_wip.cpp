#include "./clock.hpp"
#include <iostream>

const bool prev_and_alive_neighbors_to_next[2][9] = {
  {0, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0, 0}
};

const int dead_neighborhood(char *board, const unsigned int C, int i, int j){

  return (board[i * (C+2) + j] + board[(i+1) * (C+2) + (j+1)] + board[(i+2) * (C+2) + (j+2)] + board[(i+3) * (C+2) + (j+3)] + board[(i+4) * (C+2) + (j+4)] + board[(i+5) * (C+2) + (j+5)] + board[(i+6) * (C+2) + (j+6)] + board[(i+7) * (C+2) + (j+7)]) == 0;
}

void advance_single(char*board, const unsigned int R, const unsigned int C, int r, int c){
  unsigned char living_neighbors = 0;

  for(int i = -1; i<1; ++i)
    for(int j = -1; j<=1; ++j)
      living_neighbors += (board[(r+i) * (C+2) + (c+j)] &1);

  bool is_this_cell_living = board[r*(C+2)+c];
  living_neighbors -= (board[r*(C+2)+c] & 1);

  board[r*(C+2)+c] = prev_and_alive_neighbors_to_next[is_this_cell_living][living_neighbors];

}

void shift_current_to_prev(char*board, const unsigned int R, const unsigned int C){
  // for(unsigned int i=1; i<R+1; ++i)
  //   for(unsigned int j=1; j<C+1; ++j)
  //     board[i*(C+2)+j] >>= 1;

  *board >>= 1;
}

void advance(char*board, const unsigned int R, const unsigned int C){
  if(R <= 16 || C <= 16){
    for(unsigned int i=1; i+16<R+1; i+=16){
      for(unsigned int j=1; j+16<C+1; j+=16){
        // if(!dead_neighborhood(board, C, i, j)){
        advance_single(board, R, C, i, j);
        advance_single(board, R, C, i+1, j+1);
        advance_single(board, R, C, i+2, j+2);
        advance_single(board, R, C, i+3, j+3);
        advance_single(board, R, C, i+4, j+4);
        advance_single(board, R, C, i+5, j+5);
        advance_single(board, R, C, i+6, j+6);
        advance_single(board, R, C, i+7, j+7);
        // }
        //
        advance_single(board, R, C, i+8, j+8);
        advance_single(board, R, C, i+9, j+9);
        advance_single(board, R, C, i+10, j+10);
        advance_single(board, R, C, i+11, j+11);
        advance_single(board, R, C, i+12, j+12);
        advance_single(board, R, C, i+13, j+13);
        advance_single(board, R, C, i+14, j+14);
        advance_single(board, R, C, i+15, j+15);
      }
    }
    shift_current_to_prev(board, R, C);
    return;
  }

  advance(board, R/2, C/2);

}

void print_board(const char*board, const unsigned int R, const unsigned int C){
  for(unsigned int i=1; i<R+1; ++i){
    for(unsigned int j=1; j<C+1; ++j)
      std::cout << int(board[i * (C+2) + j]);
    std::cout << std::endl;
  }
}

int main(int argc, char**argv){
  if(argc == 3){
    const unsigned int R = 1<<10;
    const unsigned int C = 1<<11;

    unsigned int NUM_REPS = atoi(argv[1]);
    bool print = bool(atoi(argv[2]));

    srand(0);
    char*board = (char*)calloc((R+2)*(C+2), sizeof(char));
    char*next = (char*)calloc((R+2)*(C+2), sizeof(char));

    for(unsigned int i=1; i<R+1; ++i)
      for(unsigned int j=1; j<C+1; ++j)
        board[i*(C+2)+j] = (rand()%2 == 0);

    if(print)
      print_board(board, R, C);

    Clock c;

    for(unsigned int rep=0; rep<NUM_REPS; ++rep)
      advance(board, R, C);

    c.ptock();

    if(print)
      print_board(board, R, C);
  }
  else
    std::cerr << "usage game-of-life <generations> <0: don't print, 1: print>"<<std::endl;

  return 0;
}
