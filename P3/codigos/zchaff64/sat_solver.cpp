/* =========FOR INTERNAL USE ONLY. NO DISTRIBUTION PLEASE ========== */

/*********************************************************************
 Copyright 2000-2004, Princeton University.  All rights reserved. 
 By using this software the USER indicates that he or she has read, 
 understood and will comply with the following:

 --- Princeton University hereby grants USER nonexclusive permission 
 to use, copy and/or modify this software for internal, noncommercial,
 research purposes only. Any distribution, including commercial sale 
 or license, of this software, copies of the software, its associated 
 documentation and/or modifications of either is strictly prohibited 
 without the prior consent of Princeton University.  Title to copyright
 to this software and its associated documentation shall at all times 
 remain with Princeton University.  Appropriate copyright notice shall 
 be placed on all software copies, and a complete copy of this notice 
 shall be included in all copies of the associated documentation.  
 No right is  granted to use in advertising, publicity or otherwise 
 any trademark,  service mark, or the name of Princeton University. 


 --- This software and any associated documentation is provided "as is" 

 PRINCETON UNIVERSITY MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS 
 OR IMPLIED, INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A 
 PARTICULAR PURPOSE, OR THAT  USE OF THE SOFTWARE, MODIFICATIONS, OR 
 ASSOCIATED DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, 
 TRADEMARKS OR OTHER INTELLECTUAL PROPERTY RIGHTS OF A THIRD PARTY.  

 Princeton University shall not be liable under any circumstances for 
 any direct, indirect, special, incidental, or consequential damages 
 with respect to any claim by USER or any third party on account of 
 or arising from the use, or inability to use, this software or its 
 associated documentation, even if Princeton University has been advised
 of the possibility of those damages.
*********************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

#include <set>
#include <vector>
#include <cstring>
#include <dirent.h>
#include "SAT.h"

using namespace std;

const int MAX_LINE_LENGTH       = 65536;
const int MAX_WORD_LENGTH       = 64;

//This cnf parser function is based on the GRASP code by Joao Marques Silva
void read_cnf(SAT_Manager mng, char * filename )
{
//    cout <<"read cnf "<<endl;
    char line_buffer[MAX_LINE_LENGTH];
    char word_buffer[MAX_WORD_LENGTH];
    set<int> clause_vars;
    set<int> clause_lits;
    int line_num = 0;
    
    if(opendir(filename)){
        cerr << "Can't open input file, it's a directory" << endl;
        exit(1);
    }
    
    ifstream inp (filename, ios::in);
    if (!inp) {
        cerr << "Can't open input file" << endl;
        exit(1);
    }
    while (inp.getline(line_buffer, MAX_LINE_LENGTH)) {
        ++ line_num;
        if (line_buffer[0] == 'c') { 
            continue; 
        }
        else if (line_buffer[0] == 'p') {
            int var_num;
            int cl_num;

            int arg = sscanf (line_buffer, "p cnf %d %d", &var_num, &cl_num);
            if( arg < 2 ) {
                cerr << "Unable to read number of variables and clauses"
                     << "at line " << line_num << endl;
                exit(3);
            }
            SAT_SetNumVariables(mng, var_num); //first element not used.
        }
        else {                             // Clause definition or continuation
            char *lp = line_buffer;
            do {
                char *wp = word_buffer;
                while (*lp && ((*lp == ' ') || (*lp == '\t'))) {
                    lp++;
                }
                while (*lp && (*lp != ' ') && (*lp != '\t') && (*lp != '\n')) {
                    *(wp++) = *(lp++);
                }
                *wp = '\0';                                 // terminate string

                if (strlen(word_buffer) != 0) {     // check if number is there
                    int var_idx = atoi (word_buffer);
                    int sign = 0;

                    if( var_idx != 0) {
                        if( var_idx < 0)  { var_idx = -var_idx; sign = 1; }
                        clause_vars.insert(var_idx);
                        clause_lits.insert( (var_idx << 1) + sign);
                    }         
                    else {
                        //add this clause
                        if (clause_vars.size() != 0 && (clause_vars.size() == clause_lits.size())) { //yeah, can add this clause
                            vector <int> temp;
                            for (set<int>::iterator itr = clause_lits.begin();
                                 itr != clause_lits.end(); ++itr)
                                temp.push_back (*itr);
                            SAT_AddClause(mng, & temp.begin()[0], temp.size() );
                        }
                        else {} //it contain var of both polarity, so is automatically satisfied, just skip it
                        clause_lits.clear();
                        clause_vars.clear();
                    }
                }
            }
            while (*lp);
        }
    }
    if (!inp.eof()) {
        cerr << "Input line " << line_num <<  " too long. Unable to continue..." << endl;
        exit(2);
    }
//    assert (clause_vars.size() == 0);         //some benchmark has no 0 in the last clause
    if (clause_lits.size() && clause_vars.size()==clause_lits.size() ) {
        vector <int> temp;
        for (set<int>::iterator itr = clause_lits.begin();
             itr != clause_lits.end(); ++itr)
            temp.push_back (*itr);
        SAT_AddClause(mng, & temp.begin()[0], temp.size() );
    }
    clause_lits.clear();
    clause_vars.clear();
//    cout <<"done read cnf"<<endl;
}


void handle_result(SAT_Manager mng, int outcome, char * filename )
{
    char * result = "UNKNOWN";
    switch (outcome) {
    case SATISFIABLE:
        cout << "Instance Satisfiable" << endl;
//following lines will print out a solution if a solution exist
        for (int i=1, sz = SAT_NumVariables(mng); i<= sz; ++i) {
            switch(SAT_GetVarAsgnment(mng, i)) {
            case -1:        
                cout <<"("<< i<<")"; break;
            case 0:
                cout << "-" << i; break;
            case 1:
                cout << i ; break;
            default:
                cerr << "Unknown variable value state"<< endl;
                exit(4);
            }
            cout << " ";
        }
        result  = "SAT";
        break;
    case UNSATISFIABLE:
        result  = "UNSAT";
        cout << "Instance Unsatisfiable" << endl;
        break; 
    case TIME_OUT:
        result  = "ABORT : TIME OUT"; 
        cout << "Time out, unable to determine the satisfiability of the instance"<<endl;
        break;
    case MEM_OUT:
        result  = "ABORT : MEM OUT"; 
        cout << "Memory out, unable to determine the satisfiability of the instance"<<endl;
        break;
    default:
        cerr << "Unknown outcome" << endl;
    }
    cout << "Random Seed Used\t\t\t\t" << SAT_Random_Seed(mng) << endl;
    cout << "Max Decision Level\t\t\t\t" << SAT_MaxDLevel(mng) << endl;
    cout << "Num. of Decisions\t\t\t\t" << SAT_NumDecisions(mng)<< endl;
    cout << "( Stack + Vsids + Shrinking Decisions )\t\t" <<SAT_NumDecisionsStackConf(mng);
    cout << " + " <<SAT_NumDecisionsVsids(mng)<<" + "<<SAT_NumDecisionsShrinking(mng)<<endl;
    cout << "Original Num Variables\t\t\t\t" << SAT_NumVariables(mng) << endl;
    cout << "Original Num Clauses\t\t\t\t" << SAT_InitNumClauses(mng) << endl;
    cout << "Original Num Literals\t\t\t\t" << SAT_InitNumLiterals(mng) << endl;
    cout << "Added Conflict Clauses\t\t\t\t" << SAT_NumAddedClauses(mng)- SAT_InitNumClauses(mng)<< endl;
    cout << "Num of Shrinkings\t\t\t\t" << SAT_NumShrinkings(mng)<< endl;
    cout << "Deleted Conflict Clauses\t\t\t" << SAT_NumDeletedClauses(mng)-SAT_NumDelOrigCls(mng) <<endl;
    cout << "Deleted Clauses\t\t\t\t\t" << SAT_NumDeletedClauses(mng) <<endl;
    cout << "Added Conflict Literals\t\t\t\t" << SAT_NumAddedLiterals(mng) - SAT_InitNumLiterals(mng) << endl;
    cout << "Deleted (Total) Literals\t\t\t" << SAT_NumDeletedLiterals(mng) <<endl;
    cout << "Number of Implication\t\t\t\t" << SAT_NumImplications(mng)<< endl;
    //other statistics comes here
    cout << "Total Run Time\t\t\t\t\t" << SAT_GetCPUTime(mng) << endl;
//    cout << "RESULT:\t" << filename << " " << result << " RunTime: " << SAT_GetCPUTime(mng)<< endl;
    cout  << "RESULT:\t"<<result << endl;


}

void output_status(SAT_Manager mng)
{
    cout << "Dec: " << SAT_NumDecisions(mng)<< "\t ";
    cout << "AddCl: " << SAT_NumAddedClauses(mng) <<"\t";
    cout << "AddLit: " << SAT_NumAddedLiterals(mng)<<"\t";
    cout << "DelCl: " << SAT_NumDeletedClauses(mng) <<"\t";
    cout << "DelLit: " << SAT_NumDeletedLiterals(mng)<<"\t";
    cout << "NumImp: " << SAT_NumImplications(mng) <<"\t";
    cout << "AveBubbleMove: " << SAT_AverageBubbleMove(mng) <<"\t";
    //other statistics comes here
    cout << "RunTime:" << SAT_GetElapsedCPUTime(mng) << endl;
}

void verify_solution(SAT_Manager mng)
{
    int num_verified = 0;
    for ( int cl_idx = SAT_GetFirstClause (mng); cl_idx >= 0; 
          cl_idx = SAT_GetNextClause(mng, cl_idx)) {
        int len = SAT_GetClauseNumLits(mng, cl_idx);
        int * lits = new int[len+1];
        SAT_GetClauseLits( mng, cl_idx, lits);
        int i;
        for (i=0; i< len; ++i) {
            int v_idx = lits[i] >> 1;
            int sign = lits[i] & 0x1;
            int var_value = SAT_GetVarAsgnment( mng, v_idx);
            if( (var_value == 1 && sign == 0) ||
                (var_value == 0 && sign == 1) ) break;
        }
        if (i >= len) {
            cerr << "Verify Satisfiable solution failed, please file a bug report, thanks. " << endl;
            exit(6);
        }
        delete [] lits;
        ++ num_verified;
    }
    cout <<"c "<< num_verified << " Clauses are true, Verify Solution successful."<<endl;;
}

int main(int argc, char ** argv)
{
    SAT_Manager mng = SAT_InitManager();
    if (argc < 2) {
        cerr << "Z-Chaff: Accelerated SAT Solver from Princeton. " << endl;
        cerr << "Copyright 2000-2004, Princeton University." << endl << endl;;
        cerr << "Usage: "<< argv[0] << " cnf_file [time_limit]" << endl;
        return 2;
    }
    cout << "Z-Chaff Version: " << SAT_Version(mng) << endl;
    cout << "Solving " << argv[1] << " ......" << endl;
    if (argc == 2) {
        read_cnf (mng, argv[1] );
    }
    else {
        read_cnf (mng, argv[1] );
        SAT_SetTimeLimit(mng, atoi(argv[2]));
    }

/* if you want some statistics during the solving, uncomment following line */
//    SAT_AddHookFun(mng,output_status, 5000);

/* you can set all your parameters here, following values are the defaults*/ 
//    SAT_SetMaxUnrelevance(mng, 20);
//    SAT_SetMinClsLenForDelete(mng, 100);
//    SAT_SetMaxConfClsLenAllowed(mng, 5000);

/* randomness may help sometimes, by default, there is no randomness */
//    SAT_SetRandomness (mng, 10);
//    SAT_SetRandSeed (mng, -1);
    int result = SAT_Solve(mng);
    if (result == SATISFIABLE) 
        verify_solution(mng);
    handle_result (mng, result,  argv[1]);
    return 0;
}
