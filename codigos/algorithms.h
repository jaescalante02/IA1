#ifndef IA_ALGORITHMS
#define IA_ALGORITHMS

#include<iostream>
#include<queue>
#include<utility>
#include <unordered_map>
#include <limits>
#include <tuple>
#include "heuristics.h"
#include "codigoHash.h"

using namespace std;

typedef tuple<int,int,NODO> nodeType2;

class CompareTuple{
public:
  bool operator()(nodeType2 n1, nodeType2 n2){
    return get<1>(n1) > get<1>(n2);
  }
};

unsigned long long generated = 0;


unsigned long long gen() {return generated;}
void genclean() {generated=0;}


int A_Star(NODO r){
   
  priority_queue<nodeType2,vector<nodeType2>,CompareTuple> open;
  limpiar();


  open.push(make_tuple(0,0,r));
  
  nodeType2 n;
  list<NODO> nextStates;
  int cost;
  NODO state;
  
  while (!open.empty()){
    n = open.top();
    open.pop();
    cost = get<0>(n);
    state = get<2>(n);
     
    if (isGoal(state)){
      return cost;
    }
    insertar(state.state); 
   
    nextStates = next(state);
    for (list<NODO>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
      if (cerrado(it->state)) 
        continue;
      open.push(make_tuple(cost+1,cost+1+manhattan(*it),*it));
      
    }  
  }
  
  return -1;
 
}


int depthSearch(NODO node, int nodeCost, int cost_limit, NODO parent, bool &found){
  int minimumCost = manhattan(node) + nodeCost;
  if (minimumCost > cost_limit){
    found = false;
    return minimumCost;
  }
  if (isGoal(node)) {
    found = true;
    return nodeCost;
  }
  int min = numeric_limits<int>::max();
  int t;
  list<NODO> nextStates = next(node);
  for (list<NODO>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
    generated++;
    t = depthSearch(*it, nodeCost + 1, cost_limit, node, found);
    if (found){
      return t;
    }
    if (t < min){
      min = t;
    }
  }  
  found = false;
  return min;
} 

int IDA_Star(NODO r){

  int t;

  int cost_limit = manhattan(r);
  bool found = false; 
  
  while (cost_limit != numeric_limits<int>::max()){
    cout << cost_limit<<" ";
    t =  depthSearch(r,0,cost_limit,r,found);
    if (found){
      return t;
    }
    if (t == numeric_limits<int>::max()){
      return -1;
    }
    cost_limit = t;
  }  
  cout<<endl;
}

 
#endif

