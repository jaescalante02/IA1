all: othello othello_hash

othello: main.cc algorithms.h othello_cut.h 
	g++ -std=gnu++0x  -O2 main.cc -o othello
	
othello_hash: main_with_hash_table.cc othello_cut.h
	g++ -std=gnu++0x -O2  main_with_hash_table.cc -o othello_hash


clean:	
	rm -rf *~ othello othello_hash
