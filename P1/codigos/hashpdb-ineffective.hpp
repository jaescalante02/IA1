#include<iostream>
#include<cmath>
#include<set>
//#include"nodoDef.hpp"
using namespace std;

#ifndef pdbhash
  #include"pdb15-555-ineffective.h"
  #define pdbhash
  #define TAMPATRON 6 //5 + cero
  #define TAMPDB 524160
  #define TOVISIT 5765760
  #define MODNUMBER 360360
  #define MULTINDEX 12
  
  struct NODO2 {
  
  unsigned char ficha[TAMPATRON];
  unsigned char costo;
  
  };
  
  unsigned char pdb15_5[TAMPDB];
  unsigned long long tovisit = TOVISIT;
  unsigned long long acum1[TAMPATRON];
  unsigned long long acum2[TAMPATRON];
  
  void acumulados(){
  
    acum1[TAMPATRON-1] = 1ULL;
  
    unsigned long long aux = MULTINDEX-1;
    
    for(int i=TAMPATRON-2;i>=0;i--){
    
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
  
  
  unsigned long long myhash(int begin, unsigned long long acum[], unsigned char arg[]){
    unsigned long long index=0ULL;
    for(int i=begin;i<TAMPATRON;i++)
      index += (arg[i]-k(begin,arg,i))*acum[i];
  
    return index;
  }

  
  
  int hashpdb555(NODO n,NODO n2, int mk){
    NODO2 v1,v2,v3;
    unsigned long long st = n.state;
    int c1,c2,c3;
    c1=c2=c3=0;
    set<unsigned long long> s1,s2,s3;
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
	case 6ULL:
		  v2.ficha[1]=i;
		  break;
	case 3ULL:
		  v1.ficha[3]=i;
		  break;
	case 4ULL:
		  v1.ficha[4]=i;
		  break;
	case 7ULL:
		  v2.ficha[2]=i;
		  break;
	case 8ULL:
		  v2.ficha[3]=i;
		  break;
	case 5ULL:
		  v1.ficha[5]=i;
		  break;
	case 11ULL:
		  v3.ficha[1]=i;
		  break;
	case 9ULL:
		  v2.ficha[4]=i;
		  break;
	case 10ULL:
		  v2.ficha[5]=i;
		  break;
	case 12ULL:
		  v3.ficha[2]=i;
		  break;
	case 13ULL:
		  v3.ficha[3]=i;
		  break;
	case 14ULL:
		  v3.ficha[4]=i;
		  break;
	default:
		  v3.ficha[5]=i;
		  break;
      }
    }
    
    
    unsigned long long index1 = myhash(1,acum2,v1.ficha);
    unsigned long long index2 = myhash(1,acum2,v2.ficha);
    unsigned long long index3 = myhash(1,acum2,v3.ficha);
    
    
    ret =0;
    //cout << index1 << endl;
    ret+=pdb15_555_1[index1];
    ret+=pdb15_555_2[index2];
    ret+=pdb15_555_3[index3];
    //cout << ret << endl;
    return ret;
  }


#endif
