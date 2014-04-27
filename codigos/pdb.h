#ifndef IA_PDB
#define IA_PDB

#include <vector>
#include <iterator>
#include <stdio.h>
#include "heuristics.h"




//Functions to travel to state

unsigned long long goalState(){
	unsigned long long g=0ULL;
	for(unsigned long long i=0ULL;i<16ULL;i++) g += (i<<(4*(15-i)));
	return g;
}

inline unsigned long long vecino(unsigned long long state, int ind, int vec, int mov){
		unsigned long long tmp = state & (15ULL<<(4*ind));
		unsigned long long tmp2 = state & (15ULL<<(4*vec));
		unsigned long long tmp3 = state - tmp - tmp2;
		tmp>>=mov;
		tmp2<<=mov;
		return tmp3 + tmp + tmp2;

}

vector<unsigned long long> next(unsigned long long state){
	int pos = -1;
	for(int i=0;i<16 && pos ==-1;i++)
		if(!(state & (15ULL<<(4*i)))) pos = i;
	
	vector<unsigned long long> ret;

	if(pos % 4)
		ret.push_back(vecino(state,pos,pos-1,4));
	if(pos % 4 != 3)
		ret.push_back(vecino(state,pos+1,pos,4));
	if(pos>3)
		ret.push_back(vecino(state,pos,pos-4,16));
	if(pos<12)
		ret.push_back(vecino(state,pos+4,pos,16));

	return ret;
}



class pdbHash{
  public:
  int size; //Size of pattern
  int start; //
  vector<int> acum;
  pdbHash(int st, int s){
    start = st;
    size = s;
    acumulados();
  }
  
  void acumulados(){
  int acumAux[size];
  acumAux[size-1] = 1;
  int aux = start - (size - 1);
  for(int i=size-2;i>=0;i--){  
    acumAux[i] = acumAux[i+1]*aux;
    aux++;
  }
  acum = vector<int>(acumAux,acumAux + sizeof acumAux/ sizeof acumAux[0]);
 }

  int k(int arg[],int pos){

  int mayor = 0;
  for(int i=0;i<pos;i++) 
    if(arg[i]<arg[pos]) mayor++; 

  return mayor;

  }

  int hash(int arg[]){
  int index=0;
  for(int i=0;i<size;i++)
    index += (arg[i]-k(arg,i))*acum[i];

  return index;
}

  void print(){
    for (vector<int>::const_iterator i = acum.begin(); i != acum.end(); i++){
      std::cout << *i << "\n";
    }
  }
};


//Pattern for 15 puzzle, size 8.
void pattern15_8(int arg[], unsigned long long n){
	for (int i = 7; i >= 0; i--){
	  arg[i] = n & 15;
	  n>>=4;
	}
}

//Pattern for 15 puzzle, size 7.
void pattern15_7(int arg[], unsigned long long n){
  n>>=32;
	for (int i = 6; i >= 0; i--){
	  arg[i] = n  & 15;
	  n>>=4;
	}
}

#endif
