all: puzzle

puzzle: puzzle.o board.o puzzle_solver.o puzzle_move.o
	g++ -g -o puzzle puzzle.o board.o puzzle_solver.o puzzle_move.o

puzzle.o: puzzle.cpp board.h puzzle_heur.h puzzle_move.h
	g++ -g -c puzzle.cpp

board.o: board.cpp board.h
	g++ -g -c board.cpp

puzzle_solver.o: puzzle_solver.cpp puzzle_solver.h
	g++ -g -c puzzle_solver.cpp 

puzzle_move.o: puzzle_move.cpp puzzle_move.h
	g++ -g -c puzzle_move.cpp








