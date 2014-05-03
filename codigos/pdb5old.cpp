#include<iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <queue> 
#include <utility>
#include <set>
#include <list>
#include <unordered_map>

using namespace std;

#define TAMPATRON 6



struct NODO {

unsigned char ficha[TAMPATRON];
unsigned char costo;

};


class CompareNodo{
public:
  bool operator()(NODO n1, NODO n2){
    return n1.costo > n2.costo;
  }
};

unsigned char pdb15_5[5765760];
int unfilledPattern15_5 = 5765760;
unsigned long long acum[6];

NODO goal;

void makegoal(){

goal.ficha[0]=0;
goal.ficha[1]=9;
goal.ficha[2]=12;
goal.ficha[3]=13;
goal.ficha[4]=14;
goal.ficha[5]=15;
goal.costo =0;


}


inline void vecino(list<NODO>* ret, NODO st, int vecino){

NODO n;
n.ficha[0]= vecino;
n.costo = st.costo;

for (int i=1;i<TAMPATRON;i++){
if(st.ficha[i]==vecino){
n.costo++;
n.ficha[i]=st.ficha[0];

}else{

n.ficha[i]=st.ficha[i];
  
}
}

ret->push_back(n);

}

list<NODO> next(NODO state){
	
	//cout<<"poss"<<pos<<state.state<<endl;
	list<NODO> ret;
	unsigned char pos = state.ficha[0]; 
  
	if((pos % 4 != 3))
		vecino(&ret,state, pos+1);
	if((pos<12))
		vecino(&ret,state, pos+4);		
	if((pos % 4))
		vecino(&ret,state, pos-1);		
	if((pos>3))
		vecino(&ret,state, pos-4);

	return ret;
}

void acumulados(){

acum[TAMPATRON-1] = 1ULL;

unsigned long long aux = 11ULL;

for(int i=4;i>=0;i--){

  acum[i] = acum[i+1]*aux;
  aux++;

}



}

int k(unsigned char arg[],int pos){

  int mayor = 0;
  for(int i=0;i<pos;i++) 
    if(arg[i]<arg[pos]) mayor++; 

  return mayor;

}

unsigned long long myhash(unsigned char arg[]){
  unsigned long long index=0ULL;
  for(int i=0;i<6;i++)
    index += (arg[i]-k(arg,i))*acum[i];

  return index;
}

void asignar(NODO n){

unsigned long long index = myhash(n.ficha);

if(n.costo<pdb15_5[index]){ 

  unfilledPattern15_5--;
  pdb15_5[index] = n.costo;
}

}

unordered_map<unsigned long long, unsigned char> tabla[360360];
 

bool cerrar(unsigned long long index, unsigned char costo){

if(tabla[index%360360].count(index)){
unsigned char *c =  &tabla[index%360360][index];
 if(*c>costo){ *c=costo;return true;}
 else {return false;}
 
} else {

tabla[index%360360][index] = costo;
return true;
} 
 

}


int main(int argc, char *argv[]){
	  
//pdb15_5 = new unsigned char[5765760];  
acumulados();
std::fill (pdb15_5,pdb15_5 + 5765760,255);
//cout << (int) pdb15_5[45]<<endl;
makegoal();

priority_queue<NODO,vector<NODO>,CompareNodo> states;
states.push(goal);
NODO node;
int threshold = 1000000;
list<NODO> nextStates;

  while((unfilledPattern15_5 > 0)){
  
    node = states.top();
    states.pop();              
    asignar(node);
    if (threshold < 0){
        //cout << unfilledPattern15_5 << endl;
        threshold = 1000000;
    }   
    threshold--;
    nextStates = next(node);
    for (list<NODO>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
      //cout<<threshold<<endl;
      unsigned long long index = myhash(it->ficha);
      if(cerrar(index,it->costo)){
       
          states.push(*it);
          //int y = 0;
          //while(y<6){ cout <<(int)it->ficha[y]<<" "; y++;}
          //cout<<endl;

      } 
    }  
    
   //exit(0); 
  
  }
  int i =0;
  while(i<5765760){
  
  cout <<(int) pdb15_5[i]<< endl;
  i++;
  }  


}



