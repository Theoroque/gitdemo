#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b) : _b(b)

{ }

int PuzzleSolver::run(PuzzleHeuristic *ph) {

  PuzzleMoveHeap openlist;
  BoardSet myboards; 
  vector<PuzzleMove*> closedlist;
  map<int, Board*> moveMap;
  map<int, Board*>::iterator it;


  PuzzleMove *pm = new PuzzleMove(_b);   
  pm->score(ph);  
  openlist.push(pm);
  myboards.insert(pm->_b);
  
  _expansions=0;

/*
cout << "boardset after putting original board into boardset" << endl;
cout << **myboards.begin() << endl;
*/

while (!openlist.empty() || _b.solved() ) {

/*
for (int i=0; i< openlist->top()->_b->getSize(); i++) {
  cout << openlist->top()->_b->getTiles()[i] << endl;
}
break;
*/
 

  PuzzleMove *pm = (openlist.top());
  closedlist.push_back(pm);

/*
cout << "size of openlist = " << openlist.size() << endl;
cout << *openlist.top()->_b << endl;
cout << "end of open list" << endl;
*/

  openlist.pop();

/*
for (int i=0; i<pm->_b->getSize(); i++) {
cout << pm->_b->getTiles()[i] << endl;
}
*/

if (pm->_b->solved()) {
//cout << " hello " << endl;
 _solution.clear();
  while (pm->_prev != NULL) {
    _solution.push_front(pm->_tileMove);
    pm = pm->_prev;
  }
//  cout << "solution size = " << _solution.size() << endl;
  return 1;
}
  
  pm->_b->potentialMoves(moveMap);

/*
cout << "boardset" << endl;
set<Board *, BoardLessThan>::iterator set_it;
 for (set_it = myboards.begin(); set_it != myboards.end(); set_it++) {    
   cout << **(set_it) << endl;
 }
*/
  for (it = moveMap.begin(); it != moveMap.end(); it++) { 

/*
cout << "size of moveMap = " << moveMap.size() << endl;
cout << *(it->second) << endl; 
*/
/*
cout << "size of boardset = " << myboards.size() << endl;
 if ( myboards.find(it->second) != myboards.end()) {
    cout << *(it->second) << endl;
    
 }
cout << "size of boardset" << myboards.size() << endl;
    if ( myboards.find(&_b) == myboards.end()){
	cout<<"your pointers are screwy"<<endl;
}
*/
    if ( myboards.find(it->second) == myboards.end()) {
     PuzzleMove *pmv = new PuzzleMove((it->first), (it->second), pm);
     _expansions++;
     pmv->score(ph);
//cout << "hello" << endl;
     openlist.push(pmv);  
/*
cout << "openlist" << endl;
cout << *openlist.top()->_b << endl;
cout << "end of open list" << endl;
*/

     myboards.insert(it->second);
     closedlist.push_back(pmv);
    } 
    else { delete it->second; }
    
   }

 }

return 1;
  
}

deque<int> PuzzleSolver::getSolution() {
 
  return _solution;

}

int PuzzleSolver::getNumExpansions() {

  return _expansions;

}



