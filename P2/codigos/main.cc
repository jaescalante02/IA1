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
#include "minimax.h"
#include <iostream>

const int PASOS = 10; //Define la cantidad de pasos a hacer por la variacion principal
					  //para luego empezar a ejecutrar los algoritmos
					  //Debe ser un numero par para que la proxima jugada sea
					  //de las fichas negras que es con respecto a quien se 
					  //calculan los algoritmos

using namespace std;

int main(int argc, const char **argv) {
    state_t state,state2;
	int cnt = PASOS;
    cout << "Principal variation:" << endl;
    for( int i = 0; PV[i] != -1; ++i ) {
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        cout << state;
        cout << (player ? "Black" : "White")
             << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
             << endl;
        state = state.move(player, pos);

		if(cnt-->0) state2=state2.move(player,pos);

        cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;
    }
    cout << state;
    cout << "Value of the game = " << state.value() << endl;
    cout << "#bits per state = " << sizeof(state) * 8 << endl;
	cout << state2 << endl;

    if( argc > 1 ) {
        int n = atoi(argv[1]);
        cout << endl << "Apply " << n << " random movements at empty board:";
        state = state_t();
        for( int i = 0; i < n; ++i ) {
            bool player = i % 2 == 0; // black moves first
            int pos = state.get_random_move(player);
            cout << endl << "Minimax value " << minimax(state,4,player);
            cout << " Negamax value " << negamax(state,4,player) << endl;
            cout << state << endl;
            state = state.move(player, pos);
            cout << " " << pos;
        }
        cout << endl << "Minimax value " << minimax(state,4,n%2==0);
        cout << " Negamax value " << negamax(state,4,n%2==0) << endl;
        cout << endl << state;
    }

    return 0;
}

