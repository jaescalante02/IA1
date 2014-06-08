#include<iostream>
#include<cstdio>
#include<string>
#include <string.h>
#include <stdlib.h> 

using namespace std;
char tab[100];
bool sat;
FILE *fpr1;
FILE *fpr2;
int vars[9][9];

void add(int i){
  int fila, columna, valor;
  valor = (i % 9);
  if (valor == 0) valor = 9;
  fprintf(fpr2,"%d",valor);
}

void process(){
  char s[20];
  fgets(s,100,fpr1);
  if (strcmp(s,"SAT\n") != 0){
    fprintf(fpr2,"%s", "unsatisfiable");
    exit(1);
  }  
  int input;
  while (!feof (fpr1)){  
      fscanf (fpr1, "%d", &input);
      if (input == 0) break;
      //cout << input << endl;
      if (input > 0) add(input);      
  }
  
}


int main(int argc, char *args[]){

	
	if(argc>2) fpr2 = fopen(args[2],"w");
	else fpr2 = stdout;

	if(argc>1) fpr1 = fopen(args[1],"r");
	else fpr1 = stdin;
	
	process();
	
	fclose(fpr1);
	fclose(fpr2);

	return 0;
}
