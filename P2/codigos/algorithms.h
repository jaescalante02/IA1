#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <algorithm>
#include <limits>
#include <time.h>

using namespace std; 

unsigned long long generated = 0;
unsigned long long gen() {return generated;}
void genclean() {generated=0;}


int minimax(state_t node, int depth, bool maxPlayer){
  if ((depth == 0) || (node.terminal())){
   return node.value();
  } 
  int bestValue, value;
  std::vector<int> moves = node.valid_moves(maxPlayer);
  state_t child; 
  if (moves.size() == 0) {
    generated++;
    return minimax(node,depth-1,!maxPlayer); 
  }
  if (maxPlayer) { 
    bestValue = numeric_limits<int>::min(); 
    for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
       generated++;
       child = node.move(maxPlayer,*it);
       value = minimax(child,depth-1,false);
       bestValue = max(bestValue,value);
    }
    return bestValue;
  }  
  else {
    bestValue = numeric_limits<int>::max();
    for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
       generated++;
       child = node.move(maxPlayer,*it);
       value = minimax(child,depth-1,true);
       bestValue = min(bestValue,value);
    }
    return bestValue;
  }
  
}

int alphabeta_call(state_t node, int depth, int alpha, int beta, bool maxPlayer){
  if ((depth == 0) || (node.terminal())){
   return node.value();
  } 
  int value;
  std::vector<int> moves = node.valid_moves(maxPlayer);
  state_t child; 
  if (moves.size() == 0) {
    generated++;
    return alphabeta_call(node,depth,alpha,beta,!maxPlayer); 
  }
  if (maxPlayer) { 
    for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
       generated++; 
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
       generated++;
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
  return alphabeta_call(node, depth, min, max, maxPlayer);
}

int negamax_call(state_t node, int depth, bool maxPlayer){
  if ((depth == 0) || (node.terminal())){
    return (maxPlayer*2-1)*node.value();
  }  
  int bestValue, value;
  std::vector<int> moves;
  bestValue = numeric_limits<int>::min();
  moves = node.valid_moves(maxPlayer);
  state_t child; 
  if (moves.size() == 0) {
    generated++;
    return -negamax_call(node,depth,!maxPlayer); 
  }
  for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
     generated++;
     child = node.move(maxPlayer,*it);
     value = -negamax_call(child,depth-1,!maxPlayer);
     bestValue = max(bestValue,value);
  }
  return bestValue;
} 

int negamax(state_t node, int depth, bool maxPlayer){
  return (maxPlayer*2-1)*negamax_call(node,depth,maxPlayer);
}   

int negamax_alphabeta_call(state_t node, int depth, int alpha, int beta, bool maxPlayer){
  if ((depth == 0) || (node.terminal())){
    return (maxPlayer*2-1)*node.value();
  }  
  int bestValue, value;
  std::vector<int> moves;
  bestValue = numeric_limits<int>::min();
  moves = node.valid_moves(maxPlayer);
  state_t child; 
  if (moves.size() == 0) {
    generated++;
    return -negamax_call(node,depth-1,!maxPlayer); 
  }
  for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it) {
     generated++;
     child = node.move(maxPlayer,*it);
     value = -negamax_alphabeta_call(child,depth-1,-beta,-alpha,!maxPlayer);
     bestValue = max(bestValue,value);
     alpha = max(alpha,value);
     if (alpha >= beta){
      break;
     }
  }
  return bestValue;
} 


int negamax_alphabeta(state_t node, int depth, bool maxPlayer){
  int min, max;
  min = numeric_limits<int>::min();
  max = numeric_limits<int>::max();
  return (maxPlayer*2-1)*negamax_alphabeta_call(node,depth,min,max,maxPlayer);
}    

//maxi es true si es un nodo de maximizacion y false si es de minimizacion
//st es el estado a verificar en la funcion
bool test(state_t &st, int depth, int v, bool maxi){
	if(!depth || st.terminal()) return st.value()>v;
	vector<int> vect = st.valid_moves(maxi);
	state_t child;

	if(!vect.size()) {
	  generated++;
	  return test(st,depth,v,!maxi);
	}
	for(int i=0;i<vect.size();i++){
		if(&(child = st.move(maxi,vect[i]))!=NULL){ 
		  generated++;
		  if (test(child,depth-1,v,!maxi)==maxi)
			  return maxi;
		}	  
	}
	return !maxi;
}


//maxi es similar a la funcion anterior
int scout(state_t &st, int depth, bool maxi){
	if(!depth || st.terminal()) return st.value();
	vector<int> v = st.valid_moves(maxi);

	//if(!v.size()) cout << "no " << endl;

	if(!v.size()) {
	  generated++;
	  return scout(st,depth,!maxi);
	}
	state_t child;
	child = st.move(maxi,v[0]);
	int val = scout(child,depth-1,!maxi);
	for(int i=1;i<v.size();i++)
		if((&(child = st.move(maxi,v[i]))!=NULL) && (test(child,depth-1,val,!maxi))==maxi){
		  generated++;
			val = scout(child,depth-1,!maxi);
		}	
	

	return val;
}
int negascout_call_g(state_t node, int depth, int alpha, int beta, bool maxp);
int negascout_call_f(state_t node, int depth, int alpha, int beta, bool maxp){
	if(!depth || node.terminal()) return node.value();
		
	vector<int> v = node.valid_moves(true);
	if(!v.size()) {
	  generated++;
	  //cout<<generated<<"caso f\n";	  
    //exit(0);
	  return negascout_call_g(node,depth,alpha,beta,false);
	}
	int m,n;
	m=numeric_limits<int>::min();
	n=negascout_call_g(node.move(true,v[0]),depth-1,alpha,beta, false);
	m=(n>m)?n:m;
	if(m>=beta) return m;
	state_t child;
	for(int i=1;i<v.size();i++){
	  generated++;
	  child = node.move(true,v[i]);
	  int t = negascout_call_g(child,depth-1,m,m+1, false);
	  if(t>m){
	  
	    if((depth<3)||(t>=beta)) 
	      m=t;
	    else 
	      m = negascout_call_g(child,depth-1,t,beta, false);
	  
	  }
	  if(m>=beta) return m;
	
	}

  return m;

}

int negascout_call_g(state_t node, int depth, int alpha, int beta, bool maxp){
//cout<<"entra en g\n";
	if(!depth || node.terminal()) return node.value();
		
	vector<int> v = node.valid_moves(false);
	if(!v.size()) {
	  generated++;
	  //cout<<"caso g\n";
	  return negascout_call_f(node,depth,alpha,beta,true);
	}
	int m,n;
	m=numeric_limits<int>::max();
	n=negascout_call_f(node.move(false,v[0]),depth-1,alpha,beta,true);
	m=(n<m)?n:m;
	if(m<=alpha) return m;
	state_t child;
	for(int i=1;i<v.size();i++){
	  generated++;
	  child = node.move(false,v[i]);
	  int t = negascout_call_f(child,depth-1,m,m+1,true);
	  if(t<=m){
	  
	    if((depth<3)||(t<=alpha)) 
	      m=t;
	    else 
	      m = negascout_call_f(child,depth-1,alpha,t,true);
	  
	  }
	  if(m<=alpha) return m;
	
	}

  return m;

}


int negascout_call2(state_t node, int depth, int alpha, int beta, bool maxp){
//cout<<"entra en g\n";
	if(!depth || node.terminal()) return (maxp*2-1)*node.value();
		
	vector<int> v = node.valid_moves(maxp);
	if(!v.size()) {
	  generated++;
	  //cout<<"caso g\n";
	  return -negascout_call2(node,depth-1,-beta,-alpha,!maxp);
	}
	int m,n,a;
	m=numeric_limits<int>::min();
	n=beta;
	state_t child;
	for(int i=0;i<v.size();i++){
	  generated++;
	  child = node.move(maxp,v[i]);
	  a = -max(alpha,m);
	  int t = -negascout_call2(child,depth-1,-n,a,!maxp);
	  if(t>m){
	  
	    if((depth<3)||(n==beta) || (t>=beta)) 
	      m=t;
	    else 
	      m = -negascout_call2(child,depth-1,-beta,-t,!maxp);
	  
	  }
	  if(m>=beta) return m;
	  n = max(alpha,m) + 1;
	
	}

  return m;

}



int negascout(state_t node, int depth, bool maxPlayer){
  int min, max;
  min = numeric_limits<int>::min()+1;
  max = numeric_limits<int>::max();
  return (maxPlayer*2-1)*negascout_call2(node,depth,min,max,maxPlayer);
/*  if (maxPlayer)
    return negascout_call_f(node, depth, min, max, true);
  else   
    return negascout_call_g(node, depth, min, max, false);
***/
}


#endif
