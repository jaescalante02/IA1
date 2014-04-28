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

  typedef tuple<unsigned long long,int,int,int> pdbTuple;

class ComparePdbTuple{
public:
  bool operator()(pdbTuple n1, pdbTuple n2){
    return get<1>(n1) > get<1>(n2);
  }
};


int main(int argc, char *argv[]){
	
  //Generating pdb for 15 puzzle;
  
  //Array of store cost of each pattern
  int *pdb15_8 = new int[518918400]; 
  std::fill (pdb15_8,pdb15_8 + 518918400,-1);
  int *pdb15_7 = new int[57657600]; 
  std::fill (pdb15_7,pdb15_7 + 57657600,-1);
  
  //Array to hold current pattern
  int pattern7[7];
  int pattern8[8];
  
  //Hashing from pattern to int
  pdbHash pdbHash7(16,7);
  pdbHash pdbHash8(16,8);
  

  
  int unfilledPattern7 = 57657600;
  int unfilledPattern8 = 518918400;
  
  int posPattern7;
  int posPattern8;
  
  cout << "Filling done!";
  
  vector<unsigned long long>nextStates;
  pdbTuple node;
  vector<set<unsigned long long>> closed(5761455);

  unsigned long long st = goalState();
 
  priority_queue<pdbTuple, vector<pdbTuple>,ComparePdbTuple> states; 
  
  pattern15_7(pattern7,st);
  posPattern7 =pdbHash7.hash(pattern7);
    
        
  pattern15_8(pattern8,st);
  posPattern8 =pdbHash8.hash(pattern8);
    
  ///(state,cost,pos7,pos8)
  states.push(make_tuple(st,0,posPattern7,posPattern8));
  
  int cost = 0;
  int threshold = 100000;
  int h; //hashing to closed


  while(((unfilledPattern7 > 0) || (unfilledPattern8 > 0)) && (!states.empty())){
    node = states.top();
    st = get<0>(node);
    cost = get<1>(node);
    posPattern7 = get<2>(node);
    posPattern8 = get<3>(node);
    states.pop();
    
    h = (int) (posPattern8 / 5761455ULL);
    closed[h].insert(st);
          
    if (assign(pdb15_7,posPattern7,cost)) unfilledPattern7--;
    if (assign(pdb15_8,posPattern8,cost)) unfilledPattern8--;
    

    cout << "F7: " << unfilledPattern7 << " F8: " << unfilledPattern8 << endl;

    nextStates = next(st);
    for (vector<unsigned long long>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
    
      pattern15_8(pattern8,*it);
      posPattern8 =pdbHash8.hash(pattern8);
    
      h = (int) (posPattern8 / 5761455ULL);

      
      if(closed[h].find(*it) != closed[h].end()){
        continue;
      }
      pattern15_7(pattern7,*it);
      posPattern7 =pdbHash7.hash(pattern7);


      states.push(make_tuple(*it,cost+1,posPattern7,posPattern8));
    }  
    
  
  }  


}



