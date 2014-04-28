#include<iostream>
#include<vector>
#define ull unsigned long long

using namespace std;

struct node{
	ull p1,p2;
	int pos;
	node(){}

	//constructor que hace un nodo de p1=p p2=pp y pos=posi
	node(int p, int pp, int posi):p1(p),p2(pp),pos(posi){}

	//constructor que copia un nodo
	node(const node &n):p1(n.p1),p2(n.p2),pos(n.pos){}
};


inline int valPos(node &n,int pos){
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

inline void imprimir(node &n,char c){
	for(int i=0;i<25;i++){
		if(i%5==0) cout << c;
		if(valPos(n,i)<10) cout<<"0";
		cout << valPos(n,i) << " ";
	}
	cout << endl;
}



inline void clearPos(node &n,int pos){
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

inline void putPos(node &n,int pos, int val){
	ull v = (ull)val;
	clearPos(n,pos);
	if(pos<12)
		n.p1 += v<<(5*pos);
	else if(pos>12)
		n.p2 += v<<(5*(pos-13)+1);
	else
		n.p1+=(15ULL&v)<<60,n.p2+=(16ULL & v)?1ULL:0ULL;
}

inline void addV(vector<node> &ref, node &n, int p1, int p2){
	node nw = node(n);
	
	int tmp = valPos(nw,p2);
	clearPos(nw,p2);
	putPos(nw,p1,tmp);
	nw.pos = p2;
	ref.push_back(nw);
}

inline vector<node> next(node &n){
	vector<node> ret;
	int p = n.pos;

	if(p>4) addV(ret,n,p,p-5);

	if(p<20) addV(ret,n,p,p+5);

	if(p%5) addV(ret,n,p,p-1);

	if(p%5!=4) addV(ret,n,p,p+1);

	return ret;
}
/*
int main(){
	for(int j=0;j<25;j++){
		node n(0,0,j);
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
		vector<node> vec = next(n);
		for(int i=0;i<vec.size();i++){
			imprimir(vec[i]);
			cout << endl;
			cout << "Pos del 0: " << vec[i].pos << endl;
		}
	}
	return 0;
}*/
