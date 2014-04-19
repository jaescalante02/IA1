#include<iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "algorithms.h"

using namespace std;


//unsigned long long int goal;

bool isSolvable(unsigned long long state[]){

  int i=0, j=0;
  int res = 0;
  
  for(i=0;i<16;i++){
  
    if(state[i]==0){
      res+=i/4;
      continue;
    }
  
    for(j = i+1;j<16; j++){ 
  
      if(state[i]>state[j]) res++;
      if(state[j]==0) res--;
    }   
  
  }


  return !(res%2);


}

unsigned long long toState(unsigned long long int state[]){

  unsigned long long st = 0ULL;

  for(int i=0;i<16;i++){

    st+= state[i]<<(4*(15-i));

  }

  return st;

}


int main(int argc, char *argv[]){


  unsigned long long initstate[16];
  unsigned long long st = 0ULL;

	precalcManhattan(4);
	makeGoal();
	int a=0, ida=0;

  while(true){

    for(int i=0;i<16;i++){

      cin >> initstate[i];
      if(initstate[i]==16ULL) return 1;

    }

    if(isSolvable(initstate)){
      
      st = toState(initstate);
      cout << st << endl;
      a  = A_Star(st);
      ida = IDA_Star(st);
  
      imprimir(st);

      cout << "\nCosto al goal es " <<  a << "\n";
      cout << "Costo al goal es " <<  ida << "\n";
      
    }  

    
    
  } 

}



