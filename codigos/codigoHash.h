#include <unordered_map>
//#include "heuristics"

const int tam_hash = 1<<10;
const unsigned long long MIN_STATE = 81985529216486895ULL;

unordered_map<unsigned long long, NODO> tabla[tam_hash];

void limpiar(){
	for(int i=0;i<tam_hash;i++)
		tabla[i].clear();
}

int valor(unsigned long long st,int pos){
	int ret =0 ;

	unsigned long long tmp = st & (15ULL<<(4*pos));
	ret = tmp>>(4*pos);

	return ret;
}

//Devuelve la posicion en el arreglo a la cual pertenece el hasheo
int hashea(unsigned long long st){
	
	return (st-MIN_STATE)%tam_hash;
}


//verifica si un estado ya ha sido cerrado
  bool cerrado(NODO st){
	int v = hashea(st.state);
	if(tabla[v].count(st.state)){
	
		NODO *n = &tabla[v][st.state];
	  if(st.path<n->path){

	    *n = st;	
	    return false;
	
	  }	else return true;
		
	} else {


	  return false;

	
	} 
	
}


//inserta un estado cerrado en la tabla de hash
void insertar(NODO st){

	int v = hashea(st.state);
	if(tabla[v].count(st.state)) {
	NODO *n = &tabla[v][st.state];
	*n= (st.path<n->path)?st:*n;

	}else tabla[v][st.state] = st;
	
	//falta
}



