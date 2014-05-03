all: 15-solver 24-solver pdb5 pdb6

15-solver: 15-solver.cpp algorithms.h heuristics.h codigoHash.h
	g++ -std=gnu++0x 15-solver.cpp -o 15-solver

24-solver: 24-solver.cpp algorithms.h heuristics.h codigoHash.h
	g++ -std=gnu++0x 24-solver.cpp -o 24-solver

pdb5: pdb5.cpp 
	g++ -std=gnu++0x pdb5.cpp -o pdb5
	
pdb6: pdb6.cpp 
	g++ -std=gnu++0x pdb6.cpp -o pdb6
	
clean:	
	rm -rf *~ 15-solver 24-solver pdb5 pdb6
