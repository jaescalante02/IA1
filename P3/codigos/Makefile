all: sudoku-encoder sudoku-decoder zchaff-sat solver

solver:
	g++ -O2 solver.cpp -o solver  

sudoku-encoder:
	g++ -O2 encoder.cpp -o sudoku-encoder
	
sudoku-decoder:
	g++ -O2 decoder.cpp -o sudoku-decoder	

zchaff-sat:
	tar -zxvf zchaff.tar.gz
	cd zchaff && make
	cp zchaff/zchaff sat-zchaff
	
	
clean:
	rm -rf zchaff
	rm -f *~ sat-zchaff sudoku-encoder sudoku-decoder solver
	

