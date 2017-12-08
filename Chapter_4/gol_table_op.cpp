// I authorize my name to be shown at runtime.
#include "../Clock.hpp"
#include <iostream>

/*
 * Sean Corbett
 * 10/06/2017
 * CSCI 491
 * Game of Life
*/

// Abstracting out R and C (for table dimensions) to global constants
// helps me find table dimensions more easily. I didn't notice any
// real speedup in making this change, but the code plays better with
// my head.
const unsigned int R = 1<<10;
const unsigned int C = 1<<11;


// I went with the table representation to reduce memory footprint.
// If sacrificing an occasional bit of speed means not clobbering my
// memory, I'll take it.
const bool prev_and_alive_neighbors_to_next[2][9] = {
  {0, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0, 0}
};

void advance_single(bool*board, const int r,const int c){
  // I was able to remove a single for loop and improve performance somewhat here. Note that
  // I've changed the "r" and "c" to be const, as we don't end up modifying them. This did
  // result in a bit of a speedup as well.
  unsigned char living_neighbors = 0;

  for(int i = -1; i<1; ++i)
      living_neighbors |= (board[(r+i) * (C+2) + (c-1)] &1) + (board[(r+i) * (C+2) + (c)] &1) + (board[(r+i) * (C+2) + (c+1)] &1);



  board[r*(C+2)+c] = prev_and_alive_neighbors_to_next[board[r*(C+2)+c]][living_neighbors];

}

void shift_current_to_prev(bool*board){
  // Swapping out the second for loop means we have to perform "useless operations"
  // on more cells, but this is offset (in performance) by not have to make n
  // comparison operations (given an m*n matrix). I tried foregoing loops
  // alltogether and tried to find a way to shift the matrix as a whole, but
  // hours of Google research yielded no method that produced an accurate
  // board.
  for(unsigned int i=1; i<(R+2) * (C+2)-1; ++i) board[i] >>= 1;
}

void advance(bool*board){
  // This is where the biggest speedup came from. Loop unrolling the advance
  // function result in a massive speedup of approximately x8 (0.58 sec for
 // 1000 iters vs. 4.77 sec on avg.). Note that I've absracted out the R
 // and C vals to global constants.
  for(unsigned int i=1; i+32<R+1; i+=32){
    for(unsigned int j=1; j+32<C+1; j+=32){
      advance_single(board, i, j);
      advance_single(board, i+1, j+1);
      advance_single(board, i+2, j+2);
      advance_single(board, i+3, j+3);
      advance_single(board, i+4, j+4);
      advance_single(board, i+5, j+5);
      advance_single(board, i+6, j+6);
      advance_single(board, i+7, j+7);
      advance_single(board, i+8, j+8);
      advance_single(board, i+9, j+9);
      advance_single(board, i+10, j+10);
      advance_single(board, i+11, j+11);
      advance_single(board, i+12, j+12);
      advance_single(board, i+13, j+13);
      advance_single(board, i+14, j+14);
      advance_single(board, i+15, j+15);
      advance_single(board, i+16, j+16);
      advance_single(board, i+17, j+17);
      advance_single(board, i+18, j+18);
      advance_single(board, i+19, j+19);
      advance_single(board, i+20, j+20);
      advance_single(board, i+21, j+21);
      advance_single(board, i+22, j+22);
      advance_single(board, i+23, j+23);
      advance_single(board, i+24, j+24);
      advance_single(board, i+25, j+25);
      advance_single(board, i+26, j+26);
      advance_single(board, i+27, j+27);
      advance_single(board, i+28, j+28);
      advance_single(board, i+29, j+29);
      advance_single(board, i+30, j+30);
      advance_single(board, i+31, j+31);
    }
  }

  shift_current_to_prev(board);
}

void print_board(bool*board){
  for(unsigned int i=1; i<R+1; ++i){
    for(unsigned int j=1; j<C+1; ++j)
      std::cout << int(board[i * (C+2) + j]);
    std::cout << std::endl;
  }
}

int main(int argc, char**argv){
  if(argc == 3){

    const unsigned int NUM_REPS = atoi(argv[1]);
    bool print = bool(atoi(argv[2]));

    srand(0);

    // Switching the board to a bool-type resulted in a notable speedup
    // of approximately 1.7 times.
    bool*board = (bool*)calloc((R+2)*(C+2), sizeof(bool));

    for(unsigned int i=1; i<R+1; ++i)
      for(unsigned int j=1; j<C+1; ++j)
        board[i*(C+2)+j] = (rand()%2 == 0);

    if(print)
      print_board(board);

    Clock c;

    // Because I've absracted the R and C values to globals, we no longer
    // need to pass them all over the place.
    for(unsigned int rep=0; rep<NUM_REPS; ++rep)
      advance(board);

    c.ptock();

    if(print)
      print_board(board);
  }
  else
    std::cerr << "usage game-of-life <generations> <0: don't print, 1: print>"<<std::endl;

  return 0;
}
