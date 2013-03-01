#include <iostream>
#include <iomanip>
#include "board.h"
#include <cmath>
#include <cstdlib>
#include <map>

using namespace std;

Board::Board(int size, int numInitMoves, int seed) {

  setSize(size);
  srand(seed);

  _tiles = new int[_size];

  for (int i=0; i<_size; i++) {

    _tiles[i] = i;

  }

//scramble the board
int blank;
int mv;
int i;
int count=numInitMoves;
int dim = static_cast<int>(sqrt(_size));

while(count != 0) {
for (i=0; i< _size; i++) {
  //find blank tile (blank)
  if ( _tiles[i] == 0 )  {
     blank = i;
     break;
  }
}
  //cout << "blank = " << blank << endl;
  //generate random number
  mv = rand() % 4;
  //cout << "mv = " << mv << endl;

 //move north
  int north = blank - dim;
  if (mv == 0 && north >= 0) {

    _tiles[blank] = _tiles[north];
    _tiles[north] = 0;

  }

  //move west
  int west = blank - 1;
  if (mv == 1 && blank%dim != 0) {

    _tiles[blank] = _tiles[blank-1];
    _tiles[blank-1] = 0;

  }

  //move south
  int south = blank + dim;
  if (mv == 2 && south <_size) {


    _tiles[blank] = _tiles[south];
    _tiles[south] = 0;

  }

  //move east
  int east = blank + 1;
  if (mv == 3 && east%dim != 0) {

    _tiles[blank] = _tiles[east];
    _tiles[east] = 0;

  }
 count--;
 }
}

Board::Board(const Board &b) {

  _size = b.getSize();
  _tiles = b.getTiles();


}

void Board::move(int tile) {

 int current_tile;
 int blank;
 int dim = static_cast<int>(sqrt(_size));
/*
int crow = current_tile/dim;
int ccol = current_tile%dim;
int brow = blank/dim;
int bcol = blank%dim;
*/

 for (int i=0; i<_size; i++) {

   if (_tiles[i] == tile)
     { current_tile = i;
       break; }
 }

 for (int i=0; i<_size; i++) {

   if (_tiles[i] == 0)
     { blank = i;
       break; }
 }

int crow = current_tile/dim;
int ccol = current_tile%dim;
int brow = blank/dim;
int bcol = blank%dim;

  if (abs(crow - brow) > 1 || abs(ccol - bcol) > 1 )      { cout << "Invalid move!!!" << endl; }
  else if (crow == brow + 1 && ccol == bcol + 1 || crow == brow - 1 && ccol == bcol - 1 )    { cout << "Invalid move!!!" << endl; }
  else if (crow == brow + 1 && ccol == bcol - 1 || crow == brow - 1 && ccol == bcol + 1 )    { cout << "Invalid move!!!" << endl; }
  else if (current_tile%dim == 0 && blank == current_tile -1 || blank%dim == 0 && current_tile == blank - 1 )    { cout << "Invalid move!!!" << endl; }
//  if (crow == brow + 1 && ccol == bcol + 1 || crow == brow - 1 && ccol == bcol - 1 )    { cout << "Invalid move!!!" << endl; }
//  if (crow == brow + 1 && ccol == bcol + 1 || crow == brow - 1 && ccol == bcol - 1 )    { cout << "Invalid move!!!" << endl; }

 _tiles[blank] = _tiles[current_tile];
 _tiles[current_tile] = 0;


}

void Board::potentialMoves(map<int, Board*> &moveMap) {

  //clear the map
  map<int,Board*>::iterator it;
  for (it = moveMap.begin(); it != moveMap.end(); it++) {
      moveMap.erase(it);
  }

  Board *potmove =  new Board(_size,0,0);
  potmove->setTiles(_tiles);

/*
  cout << " potmove " << endl;
  for (int i=0; i<_size; i++) { cout << potmove->getTiles()[i] << endl; }
*/

  int dim = static_cast<int>(sqrt(potmove->getSize()));

  //find blank
  int blank;

  for (int i=0; i<potmove->getSize();i++) {

    if (potmove->getTiles()[i] == 0) {
      blank = i;
      break;

    }
  }

  //move north
  int north = blank - dim;
  if (north >= 0) {
    potmove = new Board(_size,0,0);
    potmove->setTiles(_tiles);
    potmove->getTiles()[blank] = potmove->getTiles()[north];
    potmove->getTiles()[north] = 0;
    moveMap[potmove->getTiles()[blank]] = potmove;
  }
/*
cout << "original board" << endl;
cout << *this << endl;
*/
  //move west
  int west = blank - 1;
  //cout << "west = " << _tiles[west] << endl;
  if (blank%dim != 0) {
    potmove = new Board(_size,0,0);
    potmove->setTiles(_tiles);
    potmove->getTiles()[blank] = potmove->getTiles()[west];
    potmove->getTiles()[west] = 0;
    moveMap[potmove->getTiles()[blank]] = potmove;
//cout << "west = " << potmove->getTiles()[blank] << endl;
/*for (int i=0; i< moveMap[west]->getSize(); i++) {
cout << moveMap[west]->getTiles()[i] << endl; }*/
  }
/*
cout << "original board" << endl;
cout << *this << endl;
*/
  //move south
  int south = blank + dim;
  if (south <_size) {
    potmove = new Board(_size,0,0);
    potmove->setTiles(_tiles);
    potmove->getTiles()[blank] = potmove->getTiles()[south];
    potmove->getTiles()[south] = 0;
    moveMap[potmove->getTiles()[blank]] = potmove;
  }
/*
cout << "original board" << endl;
cout << *this << endl;
*/
  //move east
  int east = blank + 1;
  if (east%dim != 0) {
    potmove = new Board(_size,0,0);
    potmove->setTiles(_tiles);
    potmove->getTiles()[blank] = potmove->getTiles()[east];
    potmove->getTiles()[east] = 0;
    moveMap[potmove->getTiles()[blank]] = potmove;
  }
/*
cout << "original board" << endl;
cout << *this << endl;
*/
/*
  for (int i=0; i<potmove->getSize(); i++ ) {
    cout << moveMap[blank]->getTiles()[i] << endl;
  }

  hello
  hello
  hello
  hello
  hello
  hello
*/


}


bool Board::solved() {

  for (int i=0; i< _size; i++) {

    if (_tiles[i] != i)
    { return false; }

  }
  return true;
}

bool Board::operator==(const Board& rhs) const {

  for (int i=0; i< _size; i++) {

    if (_tiles[i] != rhs.getTiles()[i] ) { return false; }

  }
  return true;
}

bool Board::operator<(const Board& rhs) const {

  for (int i=0; i< _size; i++) {
  if (_tiles[i] < rhs.getTiles()[i]) { return true; }
  else if(_tiles[i] > rhs.getTiles()[i]) { return false; }

  }
  return false;
}

ostream& operator<<(ostream &os, const Board &b) {

  for (int i=0; i < sqrt(b._size); i++ ) {
  for (int j=i*sqrt(b._size); j<(i+1)*sqrt(b._size); j++) {

    if (b._tiles[j] == 0) {os << setw(2) << " " << " ";}
    else os << setw(2) << b._tiles[j] << " ";
  }
    os << endl;
  }

return os;



}


int Board::getSize() const {

  return _size;

}

int *Board::getTiles() const {

  return _tiles;

}

void Board::setTiles(int *tiles) {

  for (int i=0; i<_size; i++) {

  _tiles[i] = tiles[i];

  }

}

void Board::setSize(int size) {

  _size = size;

}




















