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
#include "pdb.h"
#include "codigoHash.h"

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
 // cout<<(unsigned int) st.extra<<endl;
  
  return st;

}


bool assign(int a[], int pos, int c){
  if (a[pos] == -1){
    a[pos] = c;
    return true;
  }
  
  return false;
}

class ComparePair{
public:
  bool operator()(pair<unsigned long long, int> n1, pair<unsigned long long, int> n2){
    return n1.second > n2.second;
  }
};

typedef tuple<unsigned long long,int,int> pdbTuple;

class ComparePdbTuple{
public:
  bool operator()(pdbTuple n1, pdbTuple n2){
    return get<1>(n1) > get<1>(n2);
  }
};

void pdbgen(){
  //Array of store cost of each pattern
  int *pdb15_5 = new int[5765760]; 
  std::fill (pdb15_5,pdb15_5 + 5765760,-1);
  
  //Array to hold current pattern
  int pattern5[5];
  
  //Hashing from pattern to int
  pdbHash pdbHash5(16,5);
 
  int unfilledPattern15_5 = 5765760;
  int posPattern15_5;
  
  
  vector<unsigned long long>nextStates;
  pdbTuple node;
  vector<set<unsigned long long>> closed(100000);

  unsigned long long st = goalState();
 
  priority_queue<pdbTuple, vector<pdbTuple>,ComparePdbTuple> states; 
  
  pattern15_5_1(pattern5,st);
  posPattern15_5 =pdbHash5.hash(pattern5);
 
    
  ///(state,cost,pos5)
  states.push(make_tuple(st,0,posPattern15_5));
  
  int cost = 0;
  int threshold = 100000;
  int h; //hashing to closed


  while((unfilledPattern15_5 > 0) && (!states.empty())){
    node = states.top();
    st = get<0>(node);
    cost = get<1>(node);
    posPattern15_5 = get<2>(node);
    states.pop();
    
    h = posPattern15_5 % 100000;
    closed[h].insert(st);
          
    if (assign(pdb15_5,posPattern15_5,cost)) {
    unfilledPattern15_5--;
    if (threshold < 0){
    cout << unfilledPattern15_5 << endl;
    threshold = 1000000;
    }
    }
    threshold--;
    nextStates = next(st);
    for (vector<unsigned long long>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
    
      pattern15_5_1(pattern5,*it);
      posPattern15_5 =pdbHash5.hash(pattern5);

      h = posPattern15_5 % 100000;
      if(closed[h].find(*it) != closed[h].end()){
        continue;
      }
      
      states.push(make_tuple(*it,cost+1,posPattern15_5));
    }  
    
  
  }  


}


int main(int argc, char *argv[]){
	  
  pdbgen();




}



