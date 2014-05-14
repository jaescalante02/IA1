#include <unordered_map>
//#include "heuristics"

const int tam_hash = 1<<10;
const unsigned long long MIN_STATE = 81985529216486895ULL;

unordered_map<unsigned long long, unsigned char> tabla[tam_hash];

void limpiar(){
	for(int i=0;i<tam_hash;i++)
		tabla[i].clear();
}


//Devuelve la posicion en el arreglo a la cual pertenece el hasheo
int hashea(unsigned long long st){
	
	return (st-MIN_STATE)%tam_hash;
}


//verifica si un estado ya ha sido cerrado
bool cerrado(NODO st){
	int v = hashea(st.state);
	/*if(tabla[v].count(st.state)){
	
		unsigned char *n = &tabla[v][st.state];
	  if(st.path<*n){
	    cout <<"no debiste caer aca"<<endl;
	    *n = st.path;	
	    return false;
	
	  }	else return true;
		
	} else {

   
	  return false;

	
	} */
	
	return tabla[v].count(st.state);
	
}


//inserta un estado cerrado en la tabla de hash
void insertar(NODO st){

	int v = hashea(st.state);
	//if(!tabla[v].count(st.state)) 
	  tabla[v][st.state] = st.path;	
	
	//else {
	
	//unsigned char *n = &tabla[v][st.state];
	//if(st.path<*n){
	//  cout <<"no debiste caer aca"<<endl;
	//  *n = st.path;
	//}


	//}
	
	//falta

}



