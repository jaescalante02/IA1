#include<iostream>
#include<vector>
#define ull unsigned long long

using namespace std;

struct NODO{
	ull p1,p2;
	int pos;
	unsigned char extra;
	unsigned char cost;
	unsigned char typeson;
	unsigned char path;
	unsigned char ord;
	
	NODO(){}

	//constructor que hace un nodo de p1=p p2=pp y pos=posi
	NODO(int p, int pp, int posi):p1(p),p2(pp),pos(posi){
	  cost=0;
	  ord=0;
	  path=0;
	  extra=0;
	}

	//constructor que copia un nodo
	NODO(const NODO &n):p1(n.p1),p2(n.p2),pos(n.pos),cost(n.cost),\
			    ord(n.ord),typeson(n.typeson),extra(n.extra),\
			    path(n.path){}
};



inline int valPos(NODO &n,int pos){
	ull x1,x2,tmp;
	tmp = 0ULL;
	x1 = n.p1;
	x2 = n.p2;
	if(pos<12){
		tmp = x1 & (31ULL<<(5*pos));
		tmp >>= (pos*5);
	}	
	else if(pos>12){
		tmp = x2 & (31ULL<< (5*(pos-13)+1));
		tmp >>= (5*(pos-13)+1);
	}
	else{
		tmp = x1 & (15ULL<<60);
		tmp>>=60;
		if(x2&(1ULL))
			tmp+=16ULL;
	}

	return (int)tmp;
}

inline void imprimir(NODO &n,char c){
	for(int i=0;i<25;i++){
		if(i%5==0) cout << c;
		if(valPos(n,i)<10) cout<<"0";
		cout << valPos(n,i) << " ";
	}
	cout << endl;
}



inline void clearPos(NODO &n,int pos){
	if(pos<12)
		n.p1 -= (n.p1 & (31ULL<<(5*pos)));
	else if(pos>12)
		n.p2 -= (n.p2 & (31ULL<< (5*(pos-13)+1)));
	else{
		n.p1 -= (n.p1 & (15ULL<<60));
		if(n.p2&(1ULL))
			n.p2--;
	}
}

inline void putPos(NODO &n,int pos, int val){
	ull v = (ull)val;
	clearPos(n,pos);
	if(pos<12)
		n.p1 += v<<(5*pos);
	else if(pos>12)
		n.p2 += v<<(5*(pos-13)+1);
	else
		n.p1+=(15ULL&v)<<60,n.p2+=(16ULL & v)?1ULL:0ULL;
}

inline void addV(vector<NODO> &ref, NODO &n, int p1, int p2,int (*h)(NODO,NODO,int)){
	NODO nw = NODO(n);
	
	int tmp = valPos(nw,p2);
	clearPos(nw,p2);
	putPos(nw,p1,tmp);
	nw.pos = p2;
	nw.path = n.path +1; //a*star

	nw.cost = h(nw,n,0);
	
	nw.ord = nw.path + nw.cost;
	
	ref.push_back(nw);
}

vector<NODO> next(int (*h)(NODO,NODO,int),NODO &n){
	vector<NODO> ret;
	int p = n.pos;

	if(p>4) addV(ret,n,p,p-5,h);

	if(p<20) addV(ret,n,p,p+5,h);

	if(p%5) addV(ret,n,p,p-1,h);

	if(p%5!=4) addV(ret,n,p,p+1,h);

	return ret;
}
/*
int main(){
	for(int j=0;j<25;j++){
		NODO n(0,0,j);
		int p1,p2;
			p1=j;
			p2=0;

		for(int i=0;i<25;i++){
			putPos(n,i,i);
		}
	
		
		putPos(n,p1,p2);
		putPos(n,p2,p1);
		cout << "Para j=" << j << endl;
		imprimir(n);
		vector<NODO> vec = next(n);
		for(int i=0;i<vec.size();i++){
			imprimir(vec[i]);
			cout << endl;
			cout << "Pos del 0: " << vec[i].pos << endl;
		}
	}
	return 0;
}*/
