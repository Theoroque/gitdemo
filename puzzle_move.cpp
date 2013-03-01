#include <functional>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_move.h"
#include <iostream>

using namespace std;

PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent) : _b(b) , _tileMove(tile) , _prev(parent) 

 { _g = _prev->_g + 1; }

bool PuzzleMove::operator<(const PuzzleMove& p) const {

  if ( (_g + _h) < (p._g + p._h) ) {return true; }
  else                             {return false;}

}

bool PuzzleMove::operator>(const PuzzleMove& p) const {

  if ( (_g + _h) > (p._g + p._h) ) {return true; }
  else                             {return false;}

}

void PuzzleMove::score(PuzzleHeuristic *ph) {

  _h = ph->compute(_b->getTiles(),_b->getSize());

}
