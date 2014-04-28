#include<iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
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

NODO toState(unsigned long long int state[]){

  NODO st;
  st.state = 0ULL;

  for(int i=0;i<16;i++){

    st.state+= state[i]<<(4*(15-i));
    if(!state[i]) st.extra = i;

  }
  
 st.cost = manhattan_init(st);
 st.typeson = 5ULL;
 st.path = 0ULL; 
 st.ord = st.cost;
 // cout<<(unsigned int) st.extra<<endl;
  
  return st;

}


int main(int argc, char *argv[]){


  unsigned long long initstate[16];
  NODO st;
  clock_t atime, idatime;

	precalcManhattan(4);
	takeandclean();
	makeGoal();
	int a=0, ida=0;

  while(true){

    for(int i=0;i<16;i++){

      cin >> initstate[i];
      if(initstate[i]==16ULL) return 1;

    }

    if(isSolvable(initstate)){
      
      st = toState(initstate);
      //cout<<manhattan(st)<<endl;
      //return 1;
      imprimir(st);
      atime = clock();
      a  = A_Star(st);
      atime = clock()-atime;
      idatime = clock();
      ida = IDA_Star(st);
      idatime = clock() - idatime;
  
      cout << "\nA* costo: " <<a<<" time: "<< atime/(double)CLOCKS_PER_SEC << endl;
      cout << "IDA* costo: " <<ida<<" time: "<< idatime/(double)CLOCKS_PER_SEC<<endl<<
      "Generados "<<gen()<<" nodos ->"<<gen()/(idatime/(double)CLOCKS_PER_SEC)<<endl;
      
      genclean();

    }  

  //  cout << "IDA* costo: " <<ida<<" sizeof: "<< sizeof(NODO)<<endl;
    
  } 

}



