#include<iostream>
#include<cmath>
#include<set>
//#include"nodoDef.hpp"
using namespace std;

#ifndef IA_PDB5554
  #include"pdb24-55554.h"
  #define IA_PDB5554
  #define TAMPATRON 6 //5 + cero
  #define MULTINDEX 21
  #define TAMPATRON2 5//4 + cero
  #define MULTINDEX2 22  
  struct NODO2 {
  
  unsigned char ficha[TAMPATRON];
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
  
  
  unsigned long long myhash(int begin,int tam,unsigned long long acum[], unsigned char arg[]){
    unsigned long long index=0ULL;
    for(int i=begin;i<tam;i++)
      index += (arg[i]-k(begin,arg,i))*acum[i];
  
    return index;
  }

  
  
  int hashpdb(NODO n,NODO n2, int mk){
    NODO2 v1,v2,v3,v4,v5;
 
    int c1,c2,c3;
    
    
    int ret =0;
    for(int i=0;i<25;i++){
 
      unsigned long long tmp = valPos(n,i);
      
      switch(tmp){
	case 0ULL: 
		  v1.ficha[0]=v2.ficha[0]=v3.ficha[0]=v4.ficha[i]=v5.ficha[0]=i;
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
		  v2.ficha[2]=i;
		  break;
	case 5ULL:
		  v1.ficha[3]=i;
		  break;
	case 6ULL:
		  v1.ficha[4]=i;
		  break;
	case 7ULL:
		  v1.ficha[5]=i;
		  break;
	case 8ULL:
		  v2.ficha[3]=i;
		  break;
	case 9ULL:
		  v2.ficha[4]=i;
		  break;
	case 10ULL:
		  v3.ficha[1]=i;
		  break;
	case 11ULL:
		  v3.ficha[2]=i;
		  break;
	case 12ULL:
		  v4.ficha[1]=i;
		  break;
	case 13ULL:
		  v2.ficha[5]=i;
		  break;
	case 14ULL:
		  v5.ficha[1]=i;
		  break;
	case 15ULL:
		  v3.ficha[3]=i;
		  break;
	case 16ULL:
		  v3.ficha[4]=i;
		  break;
	case 17ULL:
		  v4.ficha[2]=i;
		  break;
	case 18ULL:
		  v5.ficha[2]=i;
		  break;
	case 19ULL:
		  v5.ficha[3]=i;
		  break;
	case 20ULL:
		  v3.ficha[5]=i;
		  break;
	case 21ULL:
		  v4.ficha[3]=i;
		  break;
	case 22ULL:
		  v4.ficha[4]=i;
		  break;
	case 23ULL:
		  v5.ficha[4]=i;
		  break;
	default:
		  v5.ficha[5]=i;
		  break;
      }
    }
    
    
    unsigned long long index1 = myhash(1,TAMPATRON,acum2,v1.ficha);
    unsigned long long index2 = myhash(1,TAMPATRON,acum2,v2.ficha);
    unsigned long long index3 = myhash(1,TAMPATRON,acum2,v3.ficha);
    unsigned long long index4 = myhash(1,TAMPATRON2,acum1,v4.ficha);
    unsigned long long index5 = myhash(1,TAMPATRON,acum2,v5.ficha);
    
    
    ret =0;
    //cout << index1 << endl;
    ret+=pdb24_1[index1];
    ret+=pdb24_2[index2];
    ret+=pdb24_3[index3];
    ret+=pdb24_4[index4];
    ret+=pdb24_5[index5];
    //cout << ret << endl;
    return ret;
  }


#endif
