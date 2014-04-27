
#ifndef IA_HEURISTICS
#define IA_HEURISTICS

#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<cmath>

using namespace std;

//matriz para el precalculo del costo de manhattan
unsigned char costo[16][16];

unsigned long long take[16];

unsigned long long clean[16];


#pragma pack(1)

typedef struct node{

unsigned long long int state;
unsigned char extra;
unsigned char cost;
} NODO;

#pragma pack()

//Este long long tendra el valor del goal 
NODO goal;


void imprimir(NODO r){
	for(int i=0;i<64;i++){
		if(i%16==0) cout << endl;
		if(i%4==0) cout << " ";
		if(r.state & (1ULL<<(63-i))) cout << 1 ;
		else cout << 0;

	}
	cout << endl<<r.state<<endl;
}

void takeandclean(){

  unsigned long long t = 15ull;
  unsigned long long c = 0xFFFFFFFFFFFFFFF0;

  for(int i=0;i<16;i++){

    take[15-i] = t;
    clean[15-i] = c;
    t<<=4;
    c<<=4;
    c|=15ull;

  }

// for(int j=0;j<16;j++) cout<<take[j]<<" "<<clean[j]<<endl;

}


inline void makeGoal(){
	goal.state=0ULL;
	for(unsigned long long i=0ULL;i<16ULL;i++) goal.state += (i<<(4*(15-i)));
}

inline bool isGoal(NODO state){
	return state.state == goal.state;
}

//la constante n representa el tamanio de uno de los lados del puzzle
void precalcManhattan(const int n){
	for(int i=0;i<n*n;i++)
		for(int j=0;j<n*n;j++){
			int f1,f2,c1,c2; 
			f1 = i/n;
			f2 = j/n;
			c1 = i%n;
			c2 = j%n;
			costo[i][j] = abs(f1-f2) + abs(c1-c2);
		
		}

/*	for(int i=0;i<n*n;i++){
		for(int j=0;j<n*n;j++){

		cout<<(int) costo[i][j]<<" ";
		}
		cout<<endl;
	}	
*/		
}
 

inline int pairwise(NODO state){
	int ret =0;
	int mask1,mask2;
	mask1=mask2=0;
	for(int i=0;i<16;i++){
		unsigned long long t = state.state & (15ULL<<((15-i)*4));
		t>>= ((15-i)*4);
		if(t==0) continue;
		int j;
		if(t%4==i%4){
			j=i+4;
			while(15-j>=0){
				unsigned long long tmp = state.state & (15ULL<<((15-j)*4));
				tmp>>= ((15-j)*4);
				if(t%4 == tmp%4 && tmp<t && tmp && !(mask2 & 1<<t) && !(mask2 & 1<<tmp))
					ret+=2,mask2+=(1<<t)+(1<<tmp);
				j+=4;
			}
		}

		j=i+1;
		if(t/4==i/4)
			while(j%4){
				unsigned long long tmp = state.state & (15ULL<<((15-j)*4));
				tmp>>= ((15-j)*4);
				if(t/4 == tmp/4 && tmp<t && tmp && !(mask1 & (1<<t)) && !(mask1 & (1<<tmp)) )
					ret+=2,mask1+=(1<<t)+(1<<tmp);
				j++;
			}

	}

	return ret;
}



int manhattan_init(NODO state){
	int tot = 0, left=0;
	unsigned long long right=15ULL;
	for(int i=15;i>=0;i--){
		unsigned long long t = state.state & right;
		t>>= left;
	  right<<=4;
		left+=4;
		if (t == 00ULL) continue;
		tot+=costo[t][i];

	}
	return tot ;
}

inline int manhattan(NODO st){

  return st.cost ;//+ pairwise(st);

}


inline NODO vecino(NODO state, int ind, int vec, int mov, int ext){
		unsigned long long tmp = state.state & (15ULL<<(4*ind));
		unsigned long long tmp2 = state.state & (15ULL<<(4*vec));
		unsigned long long tmp3 = state.state - tmp - tmp2;
		tmp>>=mov;
		tmp2<<=mov;
		NODO n;
		n.state = tmp3 + tmp + tmp2;
		n.extra = ext;
		return n;

}

inline void left(list<NODO>* ret, NODO st, int vecino){

	unsigned long long tmp = st.state & take[vecino];
	unsigned long long tmp2 = st.state & clean[vecino];
	//cout<<st.state<<endl;
  tmp>>=4;
  //cout<<tmp2<<endl;
  NODO n;
  unsigned long long tmp3 = tmp;
  //cout<<" tmp3 ficha"<<tmp3<<endl;
  tmp3>>=((15-st.extra)*4);
  //cout<<"vecino antes"<<vecino<<" tmp3 ficha"<<tmp3<<" extra desps"<<(unsigned int) st.extra<<endl;
  n.cost = st.cost -costo[tmp3][vecino]+costo[tmp3][st.extra];
  n.state = tmp2 | tmp;
  n.extra = vecino;
  //cout<<(unsigned int)st.cost<<"left n "<<(unsigned int) n.cost <<(unsigned int)costo[tmp3][vecino]<<"despues"<<(unsigned int)costo[tmp3][st.extra]<<endl;
  //imprimir(n);
  //exit(0);
  if(n.cost<st.cost) ret->push_front(n);
  else ret->push_back(n);
}

inline void right(list<NODO>* ret, NODO st, int vecino){

	unsigned long long tmp = st.state & take[vecino];
	unsigned long long tmp2 = st.state & clean[vecino];
  tmp<<=4;
  NODO n;
  unsigned long long tmp3 = tmp;
  tmp3>>=((15-st.extra)*4);  
  n.cost = st.cost - costo[tmp3][vecino]+costo[tmp3][st.extra];
  n.state = tmp2 | tmp;
  n.extra = vecino;
  //imprimir(n);
  if(n.cost<st.cost) ret->push_front(n);
  else ret->push_back(n);
}

inline void up(list<NODO>* ret, NODO st, int vecino){

	unsigned long long tmp = st.state & take[vecino];
	unsigned long long tmp2 = st.state & clean[vecino];
  tmp>>=16;
  NODO n;
  unsigned long long tmp3 = tmp;
  tmp3>>=((15-st.extra)*4);
  //  cout<<"vecino antes"<<vecino<<" tmp3 ficha"<<tmp3<<" extra desps"<<(unsigned int) st.extra<<endl;
  n.cost = st.cost  -costo[tmp3][vecino]+costo[tmp3][st.extra];
  //cout<<(unsigned int)st.cost<<"up n "<<(unsigned int) n.cost <<endl;
  n.state = tmp2 | tmp;
  n.extra = vecino;
  //imprimir(n);
  if(n.cost<st.cost) ret->push_front(n);
  else ret->push_back(n);
}

inline void down(list<NODO>* ret, NODO st, int vecino){

	unsigned long long tmp = st.state & take[vecino];
	unsigned long long tmp2 = st.state & clean[vecino];
	
  tmp<<=16;
  NODO n;
  unsigned long long tmp3 = tmp;
  tmp3>>=((15-st.extra)*4);
  n.cost = st.cost -costo[tmp3][vecino]+costo[tmp3][st.extra];
  n.state = tmp2 | tmp;
  n.extra = vecino;
  //imprimir(n);
  if(n.cost<st.cost) ret->push_front(n);
  else ret->push_back(n);
}

list<NODO> next(NODO state){
	
	int pos = state.extra;
	//cout<<"poss"<<pos<<state.state<<endl;
	list<NODO> ret;
  
	if(pos % 4 != 3)
		right(&ret,state, pos+1);
	if(pos % 4)
		left(&ret,state, pos-1);
	if(pos<12)
		down(&ret,state, pos+4);		
	if(pos>3)
		up(&ret,state, pos-4);

	return ret;
}

#endif
