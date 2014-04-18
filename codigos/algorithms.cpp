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
    return n1.first>n2.first;
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
  int value;
  
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
      value = manhattan(*it) + n.first + 1;
      open.push(make_pair(value,*it));
    }  
  }
  
  return -1;
 
}

pair<int,bool> depthSearch(unsigned long long node, int nodeCost, int cost_limit){
  int minimumCost = manhattan(node) + nodeCost;
  if (minimumCost > cost_limit){
    return make_pair(minimumCost,false);
  }
  if (isGoal(node)) {
    return make_pair(minimumCost,true);
  }
  int min = numeric_limits<int>::max();
  pair<int,bool> t;
  vector<unsigned long long> nextStates = next(node);
  for (vector<unsigned long long>::iterator it = nextStates.begin() ; it != nextStates.end(); ++it){
    t = depthSearch(*it, nodeCost + 1, cost_limit);
    if (t.second){
      return make_pair(nodeCost+1,true);
    }
    if (t.first < min){
      min = t.first;
    }
  }  
  return make_pair(t.first,false);
} 

int IDA_Star(unsigned long long r){

  pair<int,bool> t;

  int cost_limit = manhattan(r);
  while (cost_limit != numeric_limits<int>::max()){
    t =  depthSearch(r,0,cost_limit);
    if (t.second){
      return t.first;
    }
    if (t.first == numeric_limits<int>::max()){
      return -1;
    }
    cost_limit = t.first;
  }  
}


 
 
int main(){

  unsigned long long z1 = 81985529216486895ULL;
  unsigned long long z2 = 1162849439785405935ULL; 
  imprimir(z2);
  makeGoal();
  
  precalcManhattan(4);
 
  int a = A_Star(z2);
  int ida = IDA_Star(z2);
  
  cout << "Costo al goal es " <<  a << "\n";
  cout << "Costo al goal es " <<  ida << "\n";
  
}









