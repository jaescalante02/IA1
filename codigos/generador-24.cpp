#include<iostream>
#include<queue>
#include<utility>
#include"24-puzzle.h"

using namespace std;
int t;
int niv;
int cnt;
int cnt2;
int lim;
void dfs(node n,int n2,node par){
	if(niv==n2){
		if( cnt%t==0 && cnt2<lim) imprimir(n,' '),cnt2++;
		cnt++;
		return;
	}
	vector<node> v = next(n);
	for(int i=0;i<v.size();i++) if(n.p1!=v[i].p2 || n.p2!=v[i].p2)dfs(v[i],n2+1,n);

}
int main(){
	niv = 100;
	t=1000000;
	cnt=0;
	lim=100;
	cnt2=0;
	node n = node(0ULL,0ULL,20);
	for(int i=0;i<25;i++)
		putPos(n,i,i);
	putPos(n,0,5);
	putPos(n,5,10);
	putPos(n,10,0);
	dfs(n,0,n);

	return 0;
}
