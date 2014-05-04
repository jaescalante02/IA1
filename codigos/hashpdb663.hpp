#include<iostream>
#include<cmath>
#include<set>
//#include"nodoDef.hpp"
using namespace std;

#ifndef pdbhash663

  #include"pdb15-663.h"
  #define pdbhash663
  #define TAMPATRON 7 //6 + cero
  #define TAMPATRON2 4 //3 + cero
  #define MULTINDEX 11
  #define MULTINDEX2 14
  
/*typedef struct node{

unsigned long long int state;
unsigned char extra;
unsigned char cost;
unsigned char typeson;
unsigned char path;
unsigned char ord;

} NODO;

*/
  
  struct NODO2 {
  
  unsigned char ficha[TAMPATRON];
  unsigned char costo;
  
  };
  
  struct NODO3 {
  
  unsigned char ficha[TAMPATRON2];
  unsigned char costo;
  
  };
  
  
  unsigned long long acum1[TAMPATRON];
  unsigned long long acum2[TAMPATRON2];
  
  void acumulados(){
  
    acum1[TAMPATRON2-1] = 1ULL;
  
    unsigned long long aux = MULTINDEX2;
    
    for(int i=TAMPATRON2-2;i>=0;i--){
    
      acum1[i] = acum1[i+1]*aux;
      aux++;
    
    }
    
    acum2[TAMPATRON-1] = 1ULL;
    
    aux = MULTINDEX;
    
    for(int i=TAMPATRON-2;i>=0;i--){
    
      acum2[i] = acum2[i+1]*aux;
	aux++;
    
    }
  
  }
  
  int k(int begin, unsigned char arg[],int pos){
  
    int mayor = 0;
    for(int i=begin;i<pos;i++) 
      if(arg[i]<arg[pos]) mayor++; 
  
    return mayor;
  
  }
  
  
  unsigned long long myhash(int begin,int tam, unsigned long long acum[], unsigned char arg[]){
    unsigned long long index=0ULL;
    for(int i=begin;i<tam;i++)
      index += (arg[i]-k(begin,arg,i))*acum[i];
  
    return index;
  }

  
  
int hashpdb663(NODO n,NODO n2, int mk){
    NODO2 v1,v2;
    NODO3 v3;
    cout<<"ENTRANDOOO\n";
    unsigned long long st = n.state;
    int ret =0;
    for(int i=0;i<16;i++){
      int t = 4*i;
      unsigned long long tmp = st & (15ULL<<(60-t));
      tmp>>=(60-t);
      
      switch(tmp){
	case 0ULL: 
		  v1.ficha[0]=v2.ficha[0]=v3.ficha[0]=i;
		  break;
	case 1ULL: 
		  v1.ficha[1]=i;
		  break;
	case 2ULL:
		  v1.ficha[2]=i;
		  break;
	case 3ULL:
		  v2.ficha[1]=i;
		  break;
	case 4ULL:
		  v1.ficha[3]=i;
		  break;
	case 5ULL:
		  v1.ficha[4]=i;
		  break;
	case 6ULL:
		  v2.ficha[2]=i;
		  break;
	case 7ULL:
		  v2.ficha[3]=i;
		  break;
	case 8ULL:
		  v1.ficha[5]=i;
		  break;
	case 9ULL:
		  v1.ficha[6]=i;
		  break;
	case 10ULL:
		  v2.ficha[4]=i;
		  break;
	case 11ULL:
		  v2.ficha[5]=i;
		  break;
	case 12ULL:
		  v3.ficha[1]=i;
		  break;
	case 13ULL:
		  v3.ficha[2]=i;
		  break;
	case 14ULL:
		  v3.ficha[3]=i;
		  break;
	default:
		  v2.ficha[6]=i;
		  break;
      }
    }
    
    
    unsigned long long index1 = myhash(1,TAMPATRON,acum2,v1.ficha);
    unsigned long long index2 = myhash(1,TAMPATRON,acum2,v2.ficha);
    unsigned long long index3 = myhash(1,TAMPATRON2,acum1,v3.ficha);
    
     
    ret =0;
    cout << index1 << endl;
    ret+=pdb15_663_1[index1];
    ret+=pdb15_663_2[index2];
    ret+=pdb15_663_3[index3];
    cout << ret<<ret<< endl;
    return 14;
  }


#endif
