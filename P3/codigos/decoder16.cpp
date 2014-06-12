#include<iostream>
#include<cstdio>
#include<string>
#include <string.h>
#include <stdlib.h> 

using namespace std;
char tab[300];
FILE *fpr1;
FILE *fpr2;

char toChar(int i){
  char c;  
  switch(i){
    case 10:
      c = 'A';
      break;
    case 11:
      c = 'B';
      break;
    case 12:
      c = 'C';
      break;
    case 13:
      c = 'D';
      break;
    case 14:
      c = 'E';
      break;
    case 15:
      c = 'F';
      break;
    case 16:
      c = 'G';
  }
	return c;
}

void add(int i){
  int valor;
  valor = (i % 16);
  if (valor == 0) valor = 16;
  if (valor < 10) {
    fprintf(fpr2,"%d",valor);
  } else {
    fprintf(fpr2,"%c",toChar(valor)); 
  }
  
}

void process(){
  char s[20];
  //fgets(s,100,fpr1);
  /*if (strcmp(s,"SAT\n") != 0){
    fprintf(fpr2,"%s", "unsatisfiable");
    exit(1);
  } */ 
  tab[0]=0;
  while(tab[0]!='I'){ fscanf (fpr1, " %[^\n]", tab);} 
  int input;
  int i=0;
  while ((i<4096)&&(!feof (fpr1))){  
      fscanf (fpr1, "%d", &input);
      if (input == 0) break;
      //cout << input << endl;
      if (input > 0) add(input);
      i++;     
  }
  
}


int main(int argc, char *args[]){

	
  fpr2 = stdout;

	if(argc>1) fpr1 = fopen(args[1],"r");
	else fpr1 = stdin;
	process();

	printf("\n");	
	fclose(fpr1);
	fclose(fpr2);

	return 0;
}
