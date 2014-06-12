#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std;
int seed;

//tablero
char tab[90];

int mask_v[9]; //mascaras para verificacion de filas
int mask_h[9]; //mascaras para verificacion de columnas
int mask_c[9]; //mascaras para verificacion de cuadritos


//verifica si una instancia de un tablero es correcta
bool verificar(){
	for(int i=0;i<9;i++) mask_v[i]=mask_h[i]=mask_c[i]=0;

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(tab[i*9+j]=='.') continue;

			if(mask_v[i] & 1<<(tab[i*9+j]-'0')) return false;
			mask_v[i]+=(1<<(tab[i*9+j]-'0'));

			if(mask_h[j] & 1<<(tab[i*9+j]-'0')) return false;
			mask_h[j]+=(1<<(tab[i*9+j]-'0'));
			
			if(mask_c[3*(i/3)+j/3] & 1<<(tab[i*9+j]-'0')) return false;
			mask_c[3*(i/3)+j/3]+=(1<<(tab[i*9+j]-'0'));

		}
	}

	return true;

}

void generate(){

	//pongo 50 posibles fichas iniciales y si la voy a colocar
	//verifico que tenga solucion
	int c =0;
	while(c++<50){
		int casilla = rand()%81;
		int valor = rand()%9+1;

		if(tab[casilla]!='.') continue;//casilla ya ocupada

		//coloco en la casilla random, el valor random 
		tab[casilla]=valor-'0';

		//Nota para Juan: En lugar del true en la siguiente linea,
		// debe ir la llamada Al solver y verificar si colocando 
		//esa ficha sigue teniendo por lo menos una solucion,
		//es decir, si devuelve SAT

		if(verificar() && true) continue; //si colocar esa ficha en esa 
										  //posicion, sigue teniendo aunque 
										  //sea una solicion entonces la dejo

		//en caso contrario la quito (dejo vacia) y sigo iterando
		tab[casilla]='.';
	}

	//ahora tengo un tablero valido
	//llamo al solver y coloco los valores validos de alguna solucion
	//que devolvio el solver en un vector o algo asi


	//en vez de true debe ir la funcion que verifica si el tablero
	//tiene sol unica
	while(true){
		//agrego valores de ese vector al tablero (tab)
		//mientras no haya una unica solucion

	}
	
}


int main(int argc, char *argv[]){

	//debe pasarse como argumento ajuro la semilla
	if(argc==1) return 1;

	seed = atoi(argv[1]);

	srand(time(NULL));

	for(int i=0;i<81;i++) tab[i]='.';
	generate();
	return 0;
}
