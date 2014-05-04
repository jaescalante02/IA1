#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define TAM_PATRON 524160

unsigned char pdb15_555_1[TAM_PATRON];
unsigned char pdb15_555_2[TAM_PATRON];
unsigned char pdb15_555_3[TAM_PATRON];


void cargar(){

  string line;
  int i=0;
  ifstream file1("pdbs/pdb15_555_first.txt");
  if (file1.is_open()){
    while (i<TAM_PATRON) {
      getline (file1,line);
      pdb15_555_1[i] = atoi(line.c_str());
      i++;
    }
    file1.close();
  }

  i=0;
  ifstream file2("pdbs/pdb15_555_second.txt");
  if (file2.is_open()){
    while (i<TAM_PATRON) {
      getline (file2,line);
      pdb15_555_2[i] = atoi(line.c_str());     
      i++;
    }
    file2.close();
  }

  i=0;
  ifstream file3("pdbs/pdb15_555_third.txt");
  if (file3.is_open()){
    while (i<TAM_PATRON) {
      getline (file3,line);
      pdb15_555_3[i] = atoi(line.c_str());
      i++;
    }
    file3.close();
  }

}
/*
int main(){

cargar();

}*/


