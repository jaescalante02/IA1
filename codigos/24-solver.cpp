#include<iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "24-puzzle.h"
#include "algorithms2.h" 

using namespace std;


//unsigned long long int goal;

bool isSolvable(unsigned long long state[]){

  int i=0, j=0;
  int res = 0;
  
  for(i=0;i<25;i++){
  
    if(state[i]==0){
      res+=i/4;
      continue;
    }
  
    for(j = i+1;j<25; j++){ 
  
      if(state[i]>state[j]) res++;
      if(state[j]==0) res--;
    }   
  
  }


  return !(res%2);


}

NODO toState(unsigned long long int state[]){
  NODO st = NODO(0ULL,0ULL,0);

  for(int i=0;i<25;i++){
	putPos(st,i,state[i]);

  }

  st.cost = hashpdb(st,st,0);
  st.typeson = 5ULL;
  st.path = 0ULL; 
  st.ord = st.cost;
  
  return st;

}


int main(int argc, char *argv[]){


  unsigned long long initstate[25];
  NODO st;
  int pos;
  cargar();
  clock_t idatime;

	//precalcManhattan(4);
  makeGoal();
	int ida=0;

  while(true){

    for(int i=0;i<25;i++){

      cin >> initstate[i];
      if(initstate[i]==25ULL) return 1;
	  if(initstate[i]==0ULL) pos=i;

    }

    if(isSolvable(initstate)){
	
	    st = toState(initstate);
		st.pos = pos;
    //  imprimir(st);

      idatime = clock();
      ida = IDA_Star(st,hashpdb);
      idatime = clock() - idatime;
  
      cout << "IDA* costo: " <<ida<<" time: "<< idatime/(double)CLOCKS_PER_SEC <<endl;
    //  imprimir(st); 
	  cout << endl<<st.pos << endl;
    }  

    
    
  } 

}



