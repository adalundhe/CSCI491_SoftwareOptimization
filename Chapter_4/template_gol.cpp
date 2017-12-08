#include "./clock.hpp"
#include "./static_for.hpp"
#include "./random_int.hpp"
#include "./static_array.hpp"
#include <iostream>
#include <assert.h>
#include <string.h>
#include <iterator>
#include <typeinfo>

constexpr unsigned int R = 1<<10;
constexpr unsigned int C = 1<<11;

constexpr bool prev_and_alive_neighbors_to_next[2][9] = {
  {0, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0, 0}
};

struct static_shift_inner
{
  template<size_t j> static inline void func(char  board[], const size_t i)
  {
    board[i*(C+2)+j] >>= 1;
  }
};

struct static_shift_outer
{
  template<size_t i>  static inline void func(char  board[])
  {
    const size_t i_index = i;
    static_for<C+1, static_shift_inner>(board, i_index);
  }
};

struct cols_sweep
{
  template<size_t j> static inline void func(char  board[], const size_t r)
  {
    unsigned char living_neighbors = 0;
    const unsigned int c = j + 1;

    living_neighbors += (board[(r-1) * (C+2) + (c-1)] &1) + (board[(r-1) * (C+2) + c] &1) + (board[(r-1) * (C+2) + (c+1)] &1);
    living_neighbors += (board[r * (C+2) + (c-1)] &1) + (board[r * (C+2) + c] &1) + (board[r * (C+2) + (c+1)] &1);

    bool is_this_cell_living = board[r*(C+2)+c];
    living_neighbors -= (board[r*(C+2)+c] & 1);

    board[r*(C+2)+c] = prev_and_alive_neighbors_to_next[is_this_cell_living][living_neighbors];
  }
};

struct rows_sweep
{
  template<size_t i> static inline void func(char  board[])
  {
      const size_t i_index = i + 1;
      static_for<C+1, cols_sweep>(board, i_index);
  }
};

struct loop_two
{
    template<size_t j> static inline void func(char  board[], const size_t i)
    {
      board[i * (C+2) + j] = generateRandomNumber(0,2);
    }
};

struct loop_one
{
  template<size_t i> static inline void func(char  board[])
  {
    const size_t i_index = i;
    static_for<C+1, loop_two>(board, i_index);
  }
};

struct static_advance
{
  template<size_t reps> static inline void func(char  board[])
  {
    static_for<R+1, rows_sweep>(board);
    static_for<R+1, static_shift_outer>(board);
  }
};

void print_board(const char board[], const unsigned int R, const unsigned int C){
  for(unsigned int i=1; i<R+1; ++i){
    for(unsigned int j=1; j<C+1; ++j)
      std::cout << int(board[i * (C+2) + j]);
    std::cout << std::endl;
  }
}

template<size_t index> struct MetaFunc {
    enum { value = index + 1 };
};

int main(int argc, char**argv){
  bool print = bool(atoi(argv[1]));
  char board[(R+2) * (C+2)];
  memset(board, 0, (R+2) * (C+2));


  const size_t count = 5;
  typedef generate_array<count, MetaFunc>::result A;
  for (size_t i=0; i<count; ++i)
        std::cout << A::data[i] << "\n";


  static_for<R+1, loop_one>(board);


  srand(0);
  if(print)
    print_board(board, R, C);

  Clock c;


  constexpr int for_count = 1000;

  static_for<for_count, static_advance>(board);

  c.ptock();

  if(print)
    print_board(board, R, C);

  return 0;
}
