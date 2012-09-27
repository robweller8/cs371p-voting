

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunVoting.c++ -o RunVoting.c++.app
    % valgrind RunVoting.c++.app < RunVoting.in >& RunVoting.out

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

#include "Voting.h"

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
void voting_solve (std::istream& r, std::ostream& w,){
    int candidates;
    char line[];
    getline(r,line,char delim);
    candidates = atoi(line);
    std::vector<string> candidateList;
    
    //fill list of candidates
    
    for (int i=0; i<candidates; i++) {
        getline(r,line,char delim);
        candidateList.push_back(line);
    }
    
    //read and fill first round of votes
    std::vector<std::vector<std::vector<int>>> voteList;
    std::vector<int> vote;
    int whiteLine = 0;
    int voteCounter;
    while (whiteLine == 0) {
        char tempVote [candidates];
        getline(r,tempVote,char delim);
        if (strcmp(tempVote,"")==0) {
            whiteLine = 1;
        }
        else{
            int rank;
            for (int j=0; j<candidates; j++) {
                rank = atoi(tempVote[j]);
                vote.push_back(rank);
            }
            int place = vote.front();
            vote.erase(vote.begin());
            voteList[place].push_back(vote);
            voteCounter++;
        }
    }
    int isTied = 0;
    // loop while there is no winner
    while (checkWinner(voteList,candidates,voteCounter,candidateList)<0 || isTied == 0) {
        if (check_tied() != 0) {
            isTied = 1
        }
        else{
            int loserCounter;
            std::vector<int> loserList;
            checkLosers(voteList,voteCounter,candidates,loserCounter,loserList);
            revote();
        }
        
        
    }
    if(isTied == 1){
        printTiedCandidates   
    }
    else
        printWinner

}
// -------------
// checkWinner
// -------------

int checkWinner(std::vector<std::vector<std::vector<int>>>& voteList, int candidates, int voteCounter,vector<string> candidateList){
    int votesNeeded;
    if (voteCounter % 2 == 0) {
        votesNeeded = voteCounter/2;
    }
    else{
        votesNeeded = (voteCounter+1)/2;
    }
    int votes;
    for (int i=0; i<candidates; i++) {
        votes = voteList[i].size();
        if (votes>= votesNeeded) {
            for (int j = 0; j < candidateList[i].length(); j++) {
                cout << candidateList[i][j];
            }
            cout << endl;
        }
        else{
            return -1;
        }
    }
}
// -------------
// checkLosers
// -------------
void checkLosers (std::vector<std::vector<std::vector<int>>>& voteList, int voteCounter, int candidates, int& loserCounter, std::vector<int>& loserList){
    int minVote = 1000;
    for (int i=0; i<=candidates; i++) {
        if (voteList[i].size() <= minVote) {
            minVote = voteList[i].size();
        }
    }
    for (int j=0; j<candidates; j++) {
        if (voteList[j].size() == minVote) {
            loserList.push_back(j)
            loserCounter++;
        }
    }
}
// -------------
// revote
// -------------
void revote(std::vector<std::vector<std::vector<int>>>& voteList, int voteCounter, int candidates, int& loserCounter, std::vector<int>& loserList){
    loserList.push_back(-1);
    for (i = 0; i< loserCounter; i++) {
        int currentLoser = LoserList[i];
        for (int j = 0; j< voteList[currentLoser].size(); j++) {
            int validRank = 0;
            int firstRank = voteList[currentLoser].front().front();
            while (validRank ==0) {
                if (find(loserList.begin(),loserList.end(),firstRank) == -1) {
                    validRank = 1;
                }
                else{
                    voteList[currentLoser].front().erase(voteList[currentLoser].front().begin()];
                    firstRank = voteList[currentLoser].front().front();
                }
            }
            voteList[currentLoser].front().erase(voteList[currentLoser].front().begin());
            voteList[firstRank].push_back(voteList[CurrentLoser].front());
            voteList[currentLoser].erase(voteList[currentLolser].begin();
            
        }
    }
}

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
// voting_solve
// -------------

/**
 * @param r a std::istream
 * @param w a std::ostream
 */
void voting_solve (std::istream& r, std::ostream& w) {
    int testNumber;
    char line[];
    getline(r,line,char delim);
    testNumber = atoi(line);
    char winner[];
    int i;
    getline(r,line,char delim);
    for (int i=0; i<testNumber; i++) {
        voting_eval(r,w);
    }
