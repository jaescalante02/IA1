#ifndef MINIMAX_H
#define MINIMAX_H

#include <iostream>
#include <algorithm>
#include <limits>

using namespace std; 

int minimax(state_t node, int depth, bool maxPlayer){
  if ((depth == 0) || (node.terminal())){
   return node.value();
  } 
  int bestValue, value;
  std::vector<int> moves;
  if (!maxPlayer) { 
    bestValue = numeric_limits<int>::min();
    moves = node.valid_moves(maxPlayer);
    state_t child; 
    for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
       child = node.move(maxPlayer,*it);
       value = minimax(child,depth-1,!maxPlayer);
       bestValue = max(bestValue,value);
    }
    return bestValue;
  }  
  else {
    bestValue = numeric_limits<int>::max();
    moves = node.valid_moves(maxPlayer);
    state_t child; 
    for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
       child = node.move(maxPlayer,*it);
       value = minimax(child,depth-1,!maxPlayer);
       bestValue = min(bestValue,value);
    }
    return bestValue;
  }
  
}

int negamax(state_t node, int depth, bool maxPlayer){
  if ((depth == 0) || (node.terminal())){
    if (!maxPlayer){
      return node.value();
    } 
    return -node.value();
  }  

  int bestValue, value;
  std::vector<int> moves;
  bestValue = numeric_limits<int>::min();
  moves = node.valid_moves(maxPlayer);
  state_t child; 
  for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
     child = node.move(maxPlayer,*it);
     value = -negamax(child,depth-1,!maxPlayer);
     bestValue = max(bestValue,value);
  }
  return bestValue;
}    



//function negamax(node, depth, color)
//    if depth = 0 or node is a terminal node
//        return color * the heuristic value of node
//    bestValue := -∞
//    foreach child of node
//        val := -negamax(child, depth - 1, -color)
//        bestValue := max( bestValue, val )
//    return bestValue


//function minimax(node, depth, maximizingPlayer)
//    if depth = 0 or node is a terminal node
//        return the heuristic value of node
//    if maximizingPlayer
//        bestValue := -∞
//        for each child of node
//            val := minimax(child, depth - 1, FALSE)
//            bestValue := max(bestValue, val);
//        return bestValue
//    else
//        bestValue := +∞
//        for each child of node
//            val := minimax(child, depth - 1, TRUE)
//            bestValue := min(bestValue, val);
//        return bestValue

//(* Initial call for maximizing player *)
//minimax(origin, depth, TRUE)



#endif
