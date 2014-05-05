#ifndef IA_ALGORITHMS2
#define IA_ALGORITHMS2

#include<iostream>
#include<queue>
#include<utility>
#include <unordered_map>
#include <limits>
#include <tuple>
#include "hashpdb24.hpp"


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

NODO goal;

bool isGoal(NODO &n){
  return (n.p1==goal.p1) && (n.p2==goal.p2);
}

void makeGoal(){
  for(int i=0;i<25;i++){
    putPos(goal,i,i);
  }
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
  vector<NODO> nextStates = next(h, node);
  for (vector<NODO>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
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
