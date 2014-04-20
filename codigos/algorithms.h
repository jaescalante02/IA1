
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

typedef tuple<int,int,unsigned long long> nodeType2;

class CompareTuple{
public:
  bool operator()(nodeType2 n1, nodeType2 n2){
    return get<1>(n1) > get<1>(n2);
  }
};


int A_Star(unsigned long long r){
   
  priority_queue<nodeType2,vector<nodeType2>,CompareTuple> open;
  limpiar();


  open.push(make_tuple(0,0,r));
  
  nodeType2 n;
  vector<unsigned long long> nextStates;
  int cost;
  unsigned long long state;
  
  while (!open.empty()){
    n = open.top();
    open.pop();
    cost = get<0>(n);
    state = get<2>(n);
     
    if (isGoal(state)){
      return cost;
    }
    insertar(state); 
   
    nextStates = next(state);
    for (vector<unsigned long long>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
      if (cerrado(*it)) 
        continue;
      open.push(make_tuple(cost+1,cost+1+manhattan(*it),*it));
    }  
  }
  
  return -1;
 
}


int depthSearch(unsigned long long node, int nodeCost, int cost_limit, unsigned long long parent, bool &found){
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
  vector<unsigned long long> nextStates = next(node);
  for (vector<unsigned long long>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
    if (*it == parent){
      continue;
    }
    t = depthSearch(*it, nodeCost + 1, cost_limit,node,found);
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

int IDA_Star(unsigned long long r){

  int t;

  int cost_limit = manhattan(r);
  bool found = false; 
  
  while (cost_limit != numeric_limits<int>::max()){
    t =  depthSearch(r,0,cost_limit,r,found);
    if (found){
      return t;
    }
    if (t == numeric_limits<int>::max()){
      return -1;
    }
    cost_limit = t;
  }  
}

 
#endif



