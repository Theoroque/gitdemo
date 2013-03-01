#include <iostream>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_move.h"
#include "puzzle_solver.h"
#include <cmath>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {

  int size = atoi(argv[1]);
  int num_initialmoves = atoi(argv[2]);
  int seed_val = atoi(argv[3]);

  Board gameboard(size, num_initialmoves, seed_val);
  PuzzleHeuristic *heuristic;
  int h;

  map<int,Board*> moves;
  map<int,Board*>::iterator it;  
//  PuzzleMove puzzlemove(gameboard);
  PuzzleSolver solver(gameboard);

  // Print board
  cout << gameboard;
  cout << endl;

while (!gameboard.solved()) {
  
  int tile;
  // Ask for user input
  cout << "Enter tile number to move or -1 for a cheat: ";
  cin >> tile;


  if (tile == -1) {

  solver.run(heuristic);

  deque<int> solution = solver.getSolution();
  deque<int>::iterator it;

	
  cout << "Try this sequence: " << endl;
  for (it = solution.begin(); it != solution.end(); it++) {
    cout << *it << " ";
  }
    cout << endl;
    cout << "Expansions = " << solver.getNumExpansions() << endl;
    cout << endl;
    cout << gameboard << endl;
    
  } 

  else { gameboard.move(tile);
        cout << gameboard << endl; }

}

cout << "You Win! Hoooorrayyyy!!!! Go do your homework now..." << endl;

return 0;

}	
