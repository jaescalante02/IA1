#include<cstdio>

using namespace std;

#ifndef SCOUT
#define	SCOUT

//maxi es true si es un nodo de maximizacion y false si es de minimizacion
//st es el estado a verificar en la funcion
bool test(state_t &st, int depth, int v, bool maxi){
	if(!depth || st.terminal()) return st.value()>v;
	vector<int> vect = st.valid_moves(maxi);
	state_t child;

	if(!vect.size()) return test(st,depth,v,!maxi);
	
	for(int i=0;i<vect.size();i++)
		if((&(child = st.move(maxi,vect[i]))!=NULL) && test(child,depth-1,v,!maxi)==maxi)
			return maxi;
	
	return !maxi;
}


//maxi es similar a la funcion anterior
int scout(state_t &st, int depth, bool maxi){
	if(!depth || st.terminal()) return st.value();
	vector<int> v = st.valid_moves(maxi);

	//if(!v.size()) cout << "no " << endl;

	if(!v.size()) return scout(st,depth,!maxi);
	state_t child;
	child = st.move(maxi,v[0]);
	int val = scout(child,depth-1,!maxi);
	for(int i=1;i<v.size();i++)
		if((&(child = st.move(maxi,v[i]))!=NULL) && (test(child,depth-1,val,!maxi))==maxi)
			val = scout(child,depth-1,!maxi);
	

	return val;
}

	


#endif
