#include<iostream>
#include<map>
using namespace std;

const int tam_hash = 1<<16;

map<unsigned long long,bool> hash[tam_hash];

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
	return hash[v].count(st)==1;
}


//inserta un estado cerrado en la tabla de hash
void insertar(unsigned long long st){
	int v = hashea(st);
	hash[v][st]=true;
}


int main(){
	 unsigned long long tmp = 0ULL;
	 
	 for(unsigned long long i=0ULL;i<16ULL;i++) tmp += (i<<(4*i));
	 
	 tmp-=(6ULL<<24);
	 tmp+=6;
	cout << hashea(tmp) << endl;

	return 0;
}
