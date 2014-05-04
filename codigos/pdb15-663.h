#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define TAM_PATRON 5765760
#define TAM_PATRON2 3360 

unsigned char pdb15_663_1[TAM_PATRON];
unsigned char pdb15_663_2[TAM_PATRON];
unsigned char pdb15_663_3[TAM_PATRON2];


void cargar(){

  string line;
  int i=0;
  ifstream file1("pdbs/pdb15_663_first.txt");
  if (file1.is_open()){
    while (i<TAM_PATRON) {
      getline (file1,line);
      pdb15_663_1[i] = atoi(line.c_str());
      i++;
    }
    file1.close();
  }

  i=0;
  ifstream file2("pdbs/pdb15_663_second.txt");
  if (file2.is_open()){
    while (i<TAM_PATRON) {
      getline (file2,line);
      pdb15_663_2[i] = atoi(line.c_str());     
      i++;
    }
    file2.close();
  }

  i=0;
  ifstream file3("pdbs/pdb15_663_third.txt");
  if (file3.is_open()){
    while (i<TAM_PATRON2) {
      getline (file3,line);
      pdb15_663_3[i] = atoi(line.c_str());
      i++;
    }
    file3.close();
  }

}
/*
int main(){

cargar();

}*/


