/*
 *  Copyright (C) 2012 Universidad Simon Bolivar
 * 
 *  Permission is hereby granted to distribute this software for
 *  non-commercial research purposes, provided that this copyright
 *  notice is included with any such distribution.
 *  
 *  THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 *  EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 *  SOFTWARE IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU
 *  ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 *  
 *  Blai Bonet, bonet@ldc.usb.ve
 *
 *  Last revision: 11/08/2012
 *
 */

#include "othello_cut.h" // won't work correctly until .h is fixed!
#include "algorithms.h"
#include <iostream>

const int PASOS = 26; //Define el nivel desde las hojas de donde se 
					 //va a empezar a ejecutar los algoritmos
					  //Debe ser un numero par para que la proxima jugada sea
					  //de las fichas negras que es con respecto a quien se 
					  //calculan los algoritmos


int main(int argc, const char **argv) {
  
  int cnt = PASOS;
  int step;
  int adepth,result;
  clock_t time;
  
  //Console parameters.
  if (argc > 1){
    cnt = step = atoi(argv[1]);
    adepth = 33 - step;
    
  } else {
    
    step = cnt = PASOS;
    adepth = 33 - step;
  }
  
 
  state_t state,state2;
	
  cout << "Principal variation:" << endl;
	bool player,player2;
    for( int i = 0; PV[i] != -1; ++i ) {
        player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        cout << state;
        cout << (player ? "Black" : "White")
             << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
             << endl;
        state = state.move(player, pos);


        if(cnt ==0) break;
		    if(cnt-->0) state2=state2.move(player,pos);

         cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;
        }
        
        
	player2 = (33-step)%2!=0;
  cout << state;
  cout << "Value of the game = " << state.value() << endl;
  cout << "#bits per state = " << sizeof(state) * 8 << endl;
	cout << state2 << endl;
    
    
  cout << "Step :" << step << " Depth: " << adepth << endl; 
/*
  time = clock();
  cout << "Minimax value: " << minimax(state2,adepth,player2) << endl;
  time = clock() - time;
  cout << "Time :" << time/(double)CLOCKS_PER_SEC << "secs. ";
  cout << "Gen "<< gen() << " nodes ->"<< gen()/(time/(double)CLOCKS_PER_SEC)<<endl;
  genclean();
  
  time = clock();
  cout << "Negamax value: " << negamax(state2,adepth,player2) << endl;
  time = clock() - time;
  cout << "Time :" << time/(double)CLOCKS_PER_SEC << "secs. ";
  cout << "Gen "<< gen() << " nodes ->"<< gen()/(time/(double)CLOCKS_PER_SEC)<<endl;
  genclean();
 */ 

  time = clock();
	cout << "Alpha-Beta value: " << alphabeta(state2,adepth,player2) << endl;
	time = clock() - time;
  cout << "Time :" << time/(double)CLOCKS_PER_SEC << "secs. ";
  cout << "Gen "<< gen() << " nodes ->"<< gen()/(time/(double)CLOCKS_PER_SEC)<<endl;
  genclean();
  
  time = clock();
	cout << "Negamax with Alpha-Beta value: " << alphabeta(state2,adepth,player2) << endl;
	time = clock() - time;
  cout << "Time :" << time/(double)CLOCKS_PER_SEC << "secs. ";
  cout << "Gen "<< gen() << " nodes ->"<< gen()/(time/(double)CLOCKS_PER_SEC)<<endl;
  genclean();
 /* 
  time = clock();
	cout << "Scout value: " << scout(state2,adepth,player2) << endl;
	time = clock() - time;
  cout << "Time :" << time/(double)CLOCKS_PER_SEC << "secs. ";
  cout << "Gen "<< gen() << " nodes ->"<< gen()/(time/(double)CLOCKS_PER_SEC)<<endl;
  genclean();
*/
    return 0;
}

