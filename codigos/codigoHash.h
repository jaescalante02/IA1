#include<map>


const int tam_hash = 1<<16;

map<unsigned long long,bool> tabla[tam_hash];

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
	int pos=-1;
	for(int i=0;i<16 && pos==-1;i++)
		if((st & 15ULL<<(4*i))==0ULL) 
			pos = i;
	int ret = 0;

	if(pos % 4)
		ret+=valor(st,pos-1);
	ret<<=4;
	if(pos % 4 != 3)
	    ret+=valor(st,pos+1);
	ret<<=4;
	if(pos>3)
	    ret+=valor(st,pos-4);
	ret<<=4;
	if(pos<12)
		ret+=valor(st,pos+4);;	
	
	return ret;
}


//verifica si un estado ya ha sido cerrado
bool cerrado(unsigned long long st){
	int v = hashea(st);
	return tabla[v].count(st)==1;
}


//inserta un estado cerrado en la tabla de hash
void insertar(unsigned long long st){
	int v = hashea(st);
	tabla[v][st]=true;
}


