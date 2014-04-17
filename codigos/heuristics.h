#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

//matriz para el precalculo del costo de manhattan
int costo[25][25];

//Este long long tendra el valor del goal
unsigned long long goal;


void imprimir(unsigned long long r){
	for(int i=0;i<64;i++){
		if(i%16==0) cout << endl;
		if(i%4==0) cout << " ";
		if(r & (1ULL<<(63-i))) cout << 1 ;
		else cout << 0;

	}
	cout << endl;
}



inline void makeGoal(){
	goal=0ULL;
	for(unsigned long long i=0ULL;i<16ULL;i++) goal += (i<<(4*(15-i)));
}

inline bool isGoal(unsigned long long state){
	return state == goal;
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
}


int manhattan(unsigned long long state){
	int tot = 0;
	for(int i=0;i<16;i++){
		unsigned long long t = state & (15ULL<<((15-i)*4));
		t>>= ((15-i)*4);
		tot+=costo[t][i];
	}
	return tot;
}


inline unsigned long long vecino(unsigned long long state, int ind, int vec, int mov){
		unsigned long long tmp = state & (15ULL<<(4*ind));
		unsigned long long tmp2 = state & (15ULL<<(4*vec));
		unsigned long long tmp3 = state - tmp - tmp2;
		tmp>>=mov;
		tmp2<<=mov;
		return tmp3 + tmp + tmp2;

}

vector<unsigned long long> next(unsigned long long state){
	int pos = -1;
	for(int i=0;i<16 && pos ==-1;i++)
		if(!(state & (15ULL<<(4*i)))) pos = i;
	
	vector<unsigned long long> ret;

	if(pos % 4)
		ret.push_back(vecino(state,pos,pos-1,4));
	if(pos % 4 != 3)
		ret.push_back(vecino(state,pos+1,pos,4));
	if(pos>3)
		ret.push_back(vecino(state,pos,pos-4,16));
	if(pos<12)
		ret.push_back(vecino(state,pos+4,pos,16));

	return ret;
}
