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
#include <time.h>
#include <unordered_map>

using namespace std;

#define TAMPATRON 6 //5 + cero
#define TAMPDB 524160
#define TOVISIT 5765760
#define MODNUMBER 360360
#define MULTINDEX 12

struct NODO {

unsigned char ficha[TAMPATRON];
unsigned char costo;

};

NODO goal;

void makegoal(){

goal.costo = 0;
goal.ficha[0]=0;
//elegir patron
goal.ficha[1]=9;
goal.ficha[2]=12;
goal.ficha[3]=13;
goal.ficha[4]=14;
goal.ficha[5]=15;
//goal.ficha[6]=15;
//goal.ficha[7]=15;
//goal.ficha[8]=15;

}

class CompareNodo{
public:
  bool operator()(NODO n1, NODO n2){
    return n1.costo > n2.costo;
  }
};

unsigned char pdb15_5[TAMPDB];
unsigned long long tovisit = TOVISIT;
unsigned long long acum1[TAMPATRON];
unsigned long long acum2[TAMPATRON];




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

acum1[TAMPATRON-1] = 1ULL;

unsigned long long aux = MULTINDEX-1;

for(int i=TAMPATRON-2;i>=0;i--){

  acum1[i] = acum1[i+1]*aux;
  aux++;

}

acum2[TAMPATRON-1] = 1ULL;

aux = MULTINDEX;

for(int i=TAMPATRON-2;i>=0;i--){

  acum2[i] = acum2[i+1]*aux;
  aux++;

}

}

int k(int begin, unsigned char arg[],int pos){

  int mayor = 0;
  for(int i=begin;i<pos;i++) 
    if(arg[i]<arg[pos]) mayor++; 

  return mayor;

}

unsigned long long myhash(int begin, unsigned long long acum[], unsigned char arg[]){
  unsigned long long index=0ULL;
  for(int i=begin;i<TAMPATRON;i++)
    index += (arg[i]-k(begin,arg,i))*acum[i];

  return index;
}

void asignar(NODO n){

unsigned long long index = myhash(1,acum2, n.ficha);

if(n.costo<pdb15_5[index]){ 

  
  pdb15_5[index] = n.costo;
}

}

unordered_map<unsigned long long, unsigned char> tabla[MODNUMBER];
 

bool cerrar(unsigned long long index, unsigned char costo){

if(tabla[index%MODNUMBER].count(index)){
unsigned char *c =  &tabla[index%MODNUMBER][index];
 if(*c>costo){ *c=costo;return true;}
 else {return false;}
 
} else {

tabla[index%MODNUMBER][index] = costo;
tovisit--;
return true;
} 
 

}


int main(int argc, char *argv[]){

clock_t tim = clock();	  
//pdb15_5 = new unsigned char[TAMPDB];  
acumulados();
std::fill (pdb15_5,pdb15_5 + TAMPDB,255);
//cout << (int) pdb15_5[45]<<endl;
makegoal();

priority_queue<NODO,vector<NODO>,CompareNodo> states;
states.push(goal);
unsigned long long index2 = myhash(0,acum1,goal.ficha);
cerrar(index2,goal.costo);
NODO node;
int threshold = 1000000;
list<NODO> nextStates;

  while(!states.empty()){
  
    node = states.top();
    states.pop();              
    asignar(node);
    if (threshold < 0){
        //cout << tovisit << endl;
        threshold = 1000000;
    }   
    threshold--;
    nextStates = next(node);
    for (list<NODO>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
      //cout<<threshold<<endl;
      unsigned long long index = myhash(0,acum1,it->ficha);
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
  while(i<TAMPDB){
  
    cout <<(int) pdb15_5[i]<< endl;
    i++;
  }  
 
 tim = clock()-tim;
 //cout <<" time: "<< tim/(double)CLOCKS_PER_SEC<<endl;
 /*
 unsigned char u[6];
 u[1] =  9;
 u[2] =  12;
 u[3] =  13;
 u[4] =  14;
 u[5] =  15;
 
 int i =0;
 unsigned long long f;
 while(i<16){
 if((i==9)||(i==12)||(i==13)||(i==14)||(i==15)){i++;continue;}
 u[0]=i;
 f = myhash(0,acum1,u);

  cout<<"linea: "<< f <<" u[0]= "<<i<<" costo: "<<(int)tabla[f%MODNUMBER][f]<<endl;
 
 i++;
 }
 f = myhash(1,acum2,u);    
  cout<<"MENOR linea: "<< f <<" costo: "<<(int)pdb15_5[f]<<endl;
*/

}



