#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
char tab[100];
FILE *fpr1;
FILE *fpr2;
int vars[9][9][9];

int valor(int x, int y , int val){
	return vars[x][y][val-1];
}

void agregar_int(int val){
	fprintf(fpr2,"%d ",val);
}

void agregar_char(char val){
	fprintf(fpr2,"%c",val);
}

void terminar_clausula(){
	agregar_int(0);
	agregar_char('\n');
}

void procesar(int x, int y){
	
	//la celda debe poseer alguno de los valores, y esto forma una clausula
	for(int i=0;i<9;i++)
		agregar_int(valor(x,y,i+1));

	terminar_clausula();

	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){
			if(i==j) continue;
	
			agregar_int(-valor(x,y,i+1));		
			agregar_int(-valor(x,y,j+1));
			terminar_clausula();

		}
	//Prohibido tener mismos valores en la misma fila	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(j==y) continue;
			
			agregar_int(-valor(x,y,i+1));		
			agregar_int(-valor(x,j,i+1));
			terminar_clausula();


		}
	}

	//Prohibido tener mismos valores en una misma columna
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(j==x) continue;
			agregar_int(-valor(x,y,i+1));		
			agregar_int(-valor(j,y,i+1));
			terminar_clausula();
		}
	}
	
	//Prohibido tener mismos valores en un mismo cuadro
	int m,n;
	m=n=0;
	while(m+3<=x)m+=3;
	while(n+3<=y)n+=3;
	for(int i=0;i<9;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++){
				if(m+j==x && n+k==y) continue;
				agregar_int(-valor(x,y,i+1));
				agregar_int(-valor(m+j,n+k,i+1));
				terminar_clausula();
			}
	
}

void computar(){
	int i=0;
	int cnt =0;
//	cout << "tab = "<<tab <<endl;
	for(int i=0;i<81;i++)
		if(tab[i]!='.') cnt++;
	fprintf(fpr2,"p cnf 729 %d\n",23409+cnt);
	while(i<81){
		if(tab[i]!='.'){
			int t2 = tab[i]-'0';
			fprintf(fpr2,"%d %c\n",valor(i/9,i%9,t2),'0');
		}
		procesar(i/9,i%9);
		i++;
	}

}

void init(){
	int val = 1;
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			for(int k=0;k<9;k++)
				vars[i][j][k] = val++;
}

int main(int argc, char *args[]){

	
	if(argc>2) fpr2 = fopen(args[2],"w");
	else fpr2 = stdout;

	if(argc>1) fpr1 = fopen(args[1],"r");
	else fpr1 = stdin;
	
	init();
	while(fgets(tab,100,fpr1)!=NULL)
		computar();
	
	fclose(fpr1);
	fclose(fpr2);

	return 0;
}
