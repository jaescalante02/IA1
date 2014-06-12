all: sudoku-encoder sudoku-decoder sudoku-encoder16 sudoku-decoder16 zchaff64 solver

solver:
	g++ -O2 solver.cpp -o solver  

sudoku-encoder:
	g++ -O2 encoder.cpp -o sudoku-encoder
	
sudoku-decoder:
	g++ -O2 decoder.cpp -o sudoku-decoder	

sudoku-encoder16:
	g++ -O2 encoder16.cpp -o sudoku-encoder16
	
sudoku-decoder16:
	g++ -O2 decoder16.cpp -o sudoku-decoder16	

zchaff64: sudoku-encoder sudoku-decoder
	tar -zxvf zchaff64.tar.gz
	cd zchaff64 && make
	cp zchaff64/zchaff sat-zchaff

zchaff32: sudoku-encoder sudoku-decoder
	tar -zxvf zchaff32.tar.gz
	cd zchaff32 && make
	cp zchaff32/zchaff sat-zchaff	
	
clean:
	rm -rf zchaff32
	rm -rf zchaff64
	rm -f *~ sat-zchaff sudoku-encoder sudoku-decoder sudoku-encoder16 sudoku-decoder16 solver
	

