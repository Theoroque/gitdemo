#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <functional>

using namespace std;

class Board
{
 public:
  // default constructor
  Board() { } 

  // Init a board of given size and scramble it with numInitMoves 
  // by moving the space tile with a randomly chosen direction N, W, S, E
  // some of which may be invalid, in which case we skip that move
  Board(int size, int numInitMoves, int seed);

  // Copy constructor
  Board(const Board &b);

  // Destructor
  ~Board() {};

  // Swaps the blank with the specified tile
  void move(int tile);

  // Generate potential moves and fill in the map with 
  // Key=tile, Value=Ptr to corresponding Board
  // Clear the moveMap as the first order of business.
  void potentialMoves(map<int, Board*> &moveMap); 

  // Returns true if the board is solved, false otherwise
  bool solved();

  // Operators
  friend ostream& operator<<(ostream &os, const Board &b);
  bool operator==(const Board& rhs) const;
  bool operator<(const Board& rhs) const;

  // Accessors
  int *getTiles() const ;
  int getSize() const;

  // Set board (used for copy constructor
  void setTiles(int *tiles);
  void setSize(int size);
  
 private:
  int *_tiles; // Will point to an array
  int _size;   // Size of the array
};

// Leave this alone and don't touch it!
struct BoardLessThan : 
  public binary_function<const Board*, const Board*,bool>
{
  bool operator()(const Board *b1, const Board *b2) const
  {
    return *b1 < *b2;
  }
};



#endif
