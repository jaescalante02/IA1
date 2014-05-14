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

class CompareNodo{
public:
  bool operator()(NODO n1, NODO n2){
    return n1.ord > n2.ord;
  }
};

unsigned long long generated = 0;


unsigned long long gen() {return generated;}
void genclean() {generated=0;}


int A_Star(NODO r, int (*h)(NODO,NODO,int)){
   
  priority_queue<NODO,vector<NODO>,CompareNodo> open;
  limpiar();

  open.push(r);
  NODO n, *naux;
  list<NODO> nextStates;
  int cost;
  NODO state;
 
  
  while (!open.empty()){
    n = open.top();
    open.pop();
    cost = n.path;
    state = n;
     
    if (isGoal(state))return cost;
 
    insertar(state); 
    //cout <<"costo nodo "<<(int)state.ord<<endl;
    nextStates = next(h, state);
    for (list<NODO>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
      //cout <<"llegate ya"; 
      if (cerrado(*it)) continue; 
      //cout <<"llegate";            
      open.push(*it);
      
    }  
  }
  
  return -1;
 
}


int depthSearch(int (*h)(NODO,NODO,int), NODO node, int nodeCost, int cost_limit, NODO parent, bool &found){
  int minimumCost = node.cost + nodeCost;
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
  list<NODO> nextStates = next(h, node);
  for (list<NODO>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
    generated++;
    t = depthSearch(h, *it, nodeCost + 1, cost_limit, node, found);
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

int IDA_Star(NODO r, int (*h)(NODO,NODO,int)){

  int t;

  int cost_limit = r.cost;
  bool found = false; 
  
  while (cost_limit != numeric_limits<int>::max()){
    cout << cost_limit<<" ";
    t =  depthSearch(h, r , 0, cost_limit, r, found);
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
