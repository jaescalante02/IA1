#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define TAM_PATRON 6375600
#define TAM_PATRON2 303600

unsigned char pdb24_1[TAM_PATRON];
unsigned char pdb24_2[TAM_PATRON];
unsigned char pdb24_3[TAM_PATRON];
unsigned char pdb24_4[TAM_PATRON2];
unsigned char pdb24_5[TAM_PATRON];


void cargar(){

  string line;
  int i=0;
  ifstream file1("pdbs/pdb24_55554_first.txt");
  if (file1.is_open()){
    while (i<TAM_PATRON) {
      getline (file1,line);
      pdb24_1[i] = atoi(line.c_str());
      i++;
    }
    file1.close();
  }

  i=0;
  ifstream file2("pdbs/pdb24_55554_second.txt");
  if (file2.is_open()){
    while (i<TAM_PATRON) {
      getline (file2,line);
      pdb24_2[i] = atoi(line.c_str());     
      i++;
    }
    file2.close();
  }

  i=0;
  ifstream file3("pdbs/pdb24_55554_third.txt");
  if (file3.is_open()){
    while (i<TAM_PATRON) {
      getline (file3,line);
      pdb24_3[i] = atoi(line.c_str());
      i++;
    }
    file3.close();
  }


  i=0;
  ifstream file4("pdbs/pdb24_55554_fourth.txt");
  if (file4.is_open()){
    while (i<TAM_PATRON2) {
      getline (file4,line);
      pdb24_4[i] = atoi(line.c_str());
      i++;
    }
    file4.close();
  }

  i=0;
  ifstream file5("pdbs/pdb24_55554_fifth.txt");
  if (file5.is_open()){
    while (i<TAM_PATRON) {
      getline (file5,line);
      pdb24_5[i] = atoi(line.c_str());
      i++;
    }
    file5.close();
  }
}
/*
int main(){

cargar();

}
*/


