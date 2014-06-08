#! /bin/bash

make config prefix=$(pwd)
make install
#./bin/minisat
LD_LIBRARY_PATH=/usr/local/lib
echo $LD_LIBRARY_PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/lib
echo $LD_LIBRARY_PATH
export LD_LIBRARY_PATH

