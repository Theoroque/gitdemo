#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "board.h"

class PuzzleHeuristic
{
 public:
  int compute(int *tiles, int size) {

  int sum=0;
  int dim = static_cast<int>(sqrt(size));

//cout << "array" << endl;
//for (int i=0; i< size; i++) {cout << tiles[i] << endl; }

  for (int i=0; i<size; i++) {

    if (tiles[i] != 0) {
      sum = sum + ((abs(tiles[i] -i)/dim) + (abs(tiles[i] - i) % dim));
    }
/*
cout << "for " << tiles[i] << endl;
cout << "row distance = " << abs(tiles[i] -i)/dim << endl;
cout << "col distance = " << abs(tiles[i] - i) % dim << endl;
cout << "sum = " << sum << endl;
*/
  }
  return sum;
 }
};


#endif
