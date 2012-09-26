// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2012
// Glenn P. Downing
// -------------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunVoting.c++ -o RunVoting.c++.app
    % valgrind RunCollatz.c++.app < RunVoting.in >& RunVoting.out

To configure Doxygen:
    % doxygen -g
That creates the file "Doxyfile".
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile
*/

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout, ios_base

#include "Collatz.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    voting_solve(cin, cout);
    return 0;}

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream


// ------------
// voting_eval
// ------------





// -------------
// voting_print
// -------------

/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param i the string with name of winner
 */
void voting_print (std::ostream& w, int i, int j, int v) {
    assert(strcmp(i,"")!=0);
    w << i << std::endl;}

// -------------
// collatz_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void collatz_solve (std::istream& r, std::ostream& w) {
    int testNumber;
    
    
    
        collatz_print(w, winnerNAme);
