#ifndef IA_PDB
#define IA_PDB

#include "heuristics.h"


unsigned long long acum[7];

int k(unsigned long long arg[],int pos){

  int mayor = 0;
  for(int i=0;i<pos;i++) 
    if(arg[i]<arg[pos]) mayor++; 

  return mayor;

}

void acumulados(){

  acum[6] = 1ULL;
  unsigned long long aux = 10ULL;
  for(int i=5;i>=0;i--){
  
  acum[i] = acum[i+1]*aux;
  aux++;
  
  }

}

void arguments(unsigned long long arg[], NODO n){

	int left=0;
	unsigned long long right=15ULL;
  for(int i=15;i>=0;i--){
  
    unsigned long long tmp = n.state & right;
		tmp>>=left;
	  right<<=4;
		left+=4;        
    if((tmp<8ULL) && (tmp>0ULL)) arg[tmp-1ULL] = i;
  
  }

}

/*
16*15*14*13*12*11*10 = 58 millones 

f(a0,a1,a2,a3,a4,a5,a6) = (a0-k0)*15*14*13*12*11*10 +
                          (a1-k1)*14*13*12*11*10+
                          (a2-k2)*13*12*11*10+
                          .
                          .
                          .
                          (a5-k5)*10+
                          (a6-k6)

*/

unsigned long long int hash_15pdb_one(NODO n){

  unsigned long long arg[7];
  arguments(arg,n);
  for(int i=0;i<7;i++)
   cout<<arg[i]<<" ";
    for(int i=0;i<7;i++)
   cout<<acum[i]<<" "; 
  unsigned long long index=0ULL;
  for(int i=0;i<7;i++)
    index += (arg[i]-k(arg,i))*acum[i];

return index;

}




#endif
