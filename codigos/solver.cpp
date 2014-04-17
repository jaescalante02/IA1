#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

unsigned long int goal;

bool isSolvable(char state[]){

  int i=0, j=0;
  int res = 0;
  
  for(i=0;i<16;i++){
  
    if(state[i]==0){
      res+=i/4;
      continue;
    }
  
    for(j = i+1;j<16; j++){ 
  
      if(state[i]>state[j]) res++;
      if(state[j]==0) res--;
    }   
  
  }


  return !(res%2);


}

int main(int argc, char *argv[]){


  char initstate[16];

	precalcManhattan(4);
	makeGoal();

  for(int i=0;i<16;i++){

    scanf("%d",&initstate[i]);
    if(initstate[i]==16) return 1;

  }

  isSolvable(initstate);

  //initstate to unsigned longlong int

}



