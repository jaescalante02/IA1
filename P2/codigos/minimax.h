#ifndef MINIMAX_H
#define MINIMAX_H

#include <iostream>
#include <algorithm>
#include <limits>

using namespace std; 

int minimax_call(state_t node, int depth, bool maxPlayer){
  if ((depth == 0) || (node.terminal())){
   return node.value();
  } 
  int bestValue, value;
  std::vector<int> moves = node.valid_moves(maxPlayer);
  state_t child; 
  if (moves.size() == 0) {
    return minimax_call(node,depth-1,!maxPlayer); 
  }
  if (maxPlayer) { 
    bestValue = numeric_limits<int>::min(); 
    for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
       child = node.move(maxPlayer,*it);
       value = minimax_call(child,depth-1,false);
       bestValue = max(bestValue,value);
    }
    return bestValue;
  }  
  else {
    bestValue = numeric_limits<int>::max();
    for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
       child = node.move(maxPlayer,*it);
       value = minimax_call(child,depth-1,true);
       bestValue = min(bestValue,value);
    }
    return bestValue;
  }
  
}

int minimax(state_t node, int depth, bool maxPlayer){
  return (maxPlayer*2-1)*minimax_call(node,depth,maxPlayer);
}


int negamax(state_t node, int depth, bool maxPlayer){
  if ((depth == 0) || (node.terminal())){
    return (maxPlayer*2-1)*node.value();
  }  
  int bestValue, value;
  std::vector<int> moves;
  bestValue = numeric_limits<int>::min();
  moves = node.valid_moves(maxPlayer);
  state_t child; 
  if (moves.size() == 0) {
    return minimax_call(node,depth-1,!maxPlayer); 
  }
  for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
     child = node.move(maxPlayer,*it);
     value = -negamax(child,depth-1,!maxPlayer);
     bestValue = max(bestValue,value);
  }
  return bestValue;
}    

int alphabeta_call(state_t node, int depth, int alpha, int beta, bool maxPlayer){
  if ((depth == 0) || (node.terminal())){
   return node.value();
  } 
  int value;
  std::vector<int> moves = node.valid_moves(maxPlayer);
  state_t child; 
  if (moves.size() == 0) {
    return minimax_call(node,depth-1,!maxPlayer); 
  }
  if (maxPlayer) { 
    for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
       child = node.move(maxPlayer,*it);
       value = alphabeta_call(child,depth-1,alpha,beta,false);
       alpha = max(alpha,value);
       if (beta <= alpha){
        break;
       }
    }
    return alpha;
  }  
  else {    
    for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
       child = node.move(maxPlayer,*it);
       value = alphabeta_call(child,depth-1,alpha,beta,true);
       beta = min(beta,value);
       if (beta <= alpha){
        break;
       }
    }
    return beta;
  } 

}


int alphabeta(state_t node, int depth, bool maxPlayer){
  int min, max;
  min = numeric_limits<int>::min();
  max = numeric_limits<int>::max();
  return (maxPlayer*2-1)*alphabeta_call(node, depth, min, max, maxPlayer);
}


#endif
