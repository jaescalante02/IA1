
#ifndef IA_ALGORITHMS
#define IA_ALGORITHMS

#include<iostream>
#include<queue>
#include<utility>
#include <unordered_map>
#include <limits>
#include "heuristics.h"

using namespace std;

class ComparePair{
public:
  bool operator()(pair<int,unsigned long long> n1,pair<int,unsigned long long> n2){
    return (n1.first + manhattan(n1.second)) > (n2.first + manhattan(n2.second));
  }
};

typedef unordered_map<unsigned long long,bool> ullmap;
typedef pair<int,unsigned long long> nodeType;

int A_Star(unsigned long long r){
   
  priority_queue<nodeType,vector<nodeType>,ComparePair> open;
  ullmap closed; //replace with hash table
  open.push(make_pair(0,r));
  
  nodeType n;
  vector<unsigned long long> nextStates;
  
  while (!open.empty()){
    n = open.top();
    open.pop();
    if (isGoal(n.second)){
      return n.first;
    }
    closed.insert(make_pair(n.first,true)); 
   
    nextStates = next(n.second);
    for (vector<unsigned long long>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
      if (closed.find(*it) != closed.end()) {
        continue;
      }
      open.push(make_pair(n.first+1,*it));
    }  
  }
  
  return -1;
 
}

pair<int,bool> depthSearch(unsigned long long node, int nodeCost, int cost_limit, unsigned long long parent){
  int minimumCost = manhattan(node) + nodeCost;
  if (minimumCost > cost_limit){
    return make_pair(minimumCost,false);
  }
  if (isGoal(node)) {
    return make_pair(nodeCost,true);
  }
  int min = numeric_limits<int>::max();
  pair<int,bool> t;
  vector<unsigned long long> nextStates = next(node);
  for (vector<unsigned long long>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
    if (*it == parent){
      continue;
    }
    t = depthSearch(*it, nodeCost + 1, cost_limit,node);
    if (t.second){
      return make_pair(t.first,true);
    }
    if (t.first < min){
      min = t.first;
    }
  }  
  return make_pair(min,false);
} 

int IDA_Star(unsigned long long r){

  pair<int,bool> t;

  int cost_limit = manhattan(r);
  while (cost_limit != numeric_limits<int>::max()){
    t =  depthSearch(r,0,cost_limit,r);
    if (t.second){
      return t.first;
    }
    if (t.first == numeric_limits<int>::max()){
      return -1;
    }
    cost_limit = t.first;
  }  
}


 
/*
int main(){

  unsigned long long z1 = 81985529216486895ULL;
  unsigned long long z2 = 1162849439785405935ULL; 
  unsigned long long z3 = 1297957428606520815ULL; 
  
  precalcManhattan(4);
  makeGoal();
  imprimir(z3);
  int a = A_Star(z3);
  int ida = IDA_Star(z3);
  
  cout << "\nCosto al goal es " <<  a << "\n";
  cout << "Costo al goal es " <<  ida << "\n";
  
}
*/




#endif



