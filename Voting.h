
/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunVoting3.c++ -o RunVoting3.c++.app
    % valgrind RunVoting3.c++.app < RunVoting.in >& RunVoting.out

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
#include <vector>
#include <iostream> 
#include <cstdlib>
//#include "Voting.h"
#include <cassert>  
#include <iostream> 
#include <string>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <sstream>
#include <iterator>


//has functions
//
void voting_eval (std::istream& r, std::ostream& w);
int  checkWinner(std::vector<std::vector<std::vector<int> > >& voteList, int candidates, int voteCounter, std::vector<std::string> candidateList);
int  checkTie(std::vector<std::vector<std::vector<int> > >& voteList, int candidates, int voteCounter,std::vector<std::string> candidateList);
void checkLosers (std::vector<std::vector<std::vector<int> > >& voteList, int voteCounter, int candidates, int& loserCounter, std::vector<int>& loserList);
void revote(std::vector<std::vector<std::vector<int> > >& voteList, int voteCounter, int& candidates, int& loserCounter, std::vector<int>& loserList);

// ------------
// voting_eval
// ------------
void voting_eval (std::istream& r, std::ostream& w)
{
    using namespace std;
    //get number of candidates
    int candidates;
    string newLine;
    getline(r,newLine);
    candidates = atoi(newLine.c_str());
    std::vector<std::string> candidateList;
    //fill list of candidates
    string newestLine;
    for (int i=0; i<candidates; i++)
    {
        getline(r,newestLine);
        candidateList.push_back(newestLine);
    }
    //read and fill first round of votes
    std::vector<std::vector<std::vector<int> > > voteList;
    unsigned int newSize = (unsigned int)candidates;
    voteList.resize(newSize);
    std::vector<int> vote;
    int whiteLine = 0;
    int voteCounter = 0; 
    while (whiteLine == 0)
    {
        string tempVote;
        getline(r,tempVote);
        if (tempVote.size() == 0)
        {
            whiteLine = 1;
        }
        else
        {
            int rank;
            istringstream iss(tempVote);
            vector<string> tokens;
            copy(istream_iterator<string>(iss),
                 istream_iterator<string>(),
                 back_inserter<vector<string> >(tokens));

            for (int k=0; k < (int) tokens.size(); k++)
            {
		rank = atoi(tokens[k].c_str());
		vote.push_back(rank);
            }
            int place = vote.front()-1;
            vote.erase(vote.begin());
            assert(place >= 0);
            assert(place < (int)voteList.size());
            voteList[place].push_back(vote);
            voteCounter++;
            vote.clear();
        }
    } 
    int loserCounter = 0;
    std::vector<int> loserList;
    
    while (!(checkWinner(voteList,candidates,voteCounter,candidateList)==0) && !(checkTie(voteList,candidates,voteCounter, candidateList)== 0))
    {
       
      

        checkLosers(voteList,voteCounter,candidates,loserCounter,loserList);
        revote(voteList, voteCounter, candidates, loserCounter, loserList);
        
        
        
    }

}
// -------------
// checkWinner
// -------------

int checkWinner(std::vector<std::vector<std::vector<int> > >& voteList, int candidates, int voteCounter, std::vector<std::string> candidateList)
{
    using namespace std;
   
    int votesNeeded;
    if ((voteCounter % 2) == 0)
    {
        
        votesNeeded = voteCounter/2 + 1;
    }
    else
    {
        votesNeeded = (voteCounter+1)/2;
    }
    
    int votes;
    
    for (int i=0; i<candidates; i++)
    {
        votes = voteList[i].size();
	
        if (votes>= votesNeeded)
        {
            for (int j = 0; j < (int)candidateList[i].length(); j++)
            {
                cout << candidateList[i][j];
            }
            cout << endl;
            return 0;
        }
       
    }
    return -1;
}
// -------------
// checkTie
// -------------
           
int checkTie(std::vector<std::vector<std::vector<int> > >& voteList, int candidates, int voteCounter,std::vector<std::string> candidateList)
{
    using namespace std;
   
    int isTie = 1;
    int tiedVoteNumber;
    for (int n = 0; n < candidates; n++)
    {
    if (voteList[n].size()>0)
    {
        tiedVoteNumber = voteList[n].size();
    }
    }

    for (int i = 0; i<candidates; i++)
    {
        
        if ((int)voteList[i].size()!=tiedVoteNumber && (int)voteList[i].size() > 0)
        {
           
            isTie = 0;
            return -1;
        }
    }
   
    for (int j = 0; j < candidates; j++)
    {
         if((int)voteList[j].size() > 0)
         {
                cout << candidateList[j] << endl;
         }
        
    }
    return 0;
    
    
    
}
// -------------
// checkLosers
// -------------
void checkLosers (std::vector<std::vector<std::vector<int> > >& voteList, int voteCounter, int candidates, int& loserCounter, std::vector<int>& loserList)
{    
    using namespace std;
    
    int minVote = 1000;
    for (int i=0; i<candidates; i++)
    {
	
        if ((int)voteList[i].size() <= minVote && (int)voteList[i].size() > 0)
        {

            minVote = voteList[i].size();
        }
	
    }
    for (int j=0; j<candidates; j++)
    {
	
        if ((int)voteList[j].size() == minVote && (int)voteList[j].size() > 0)
        {
	
            loserList.push_back(j);
            loserCounter++;
        }
    }
}
// -------------
// revote
// -------------
void revote(std::vector<std::vector<std::vector<int> > >& voteList, int voteCounter, int& candidates, int& loserCounter, std::vector<int>& loserList)
{
    using namespace std;
   
    // go through all losers in loserList
    for (int i = 0; i< loserCounter; i++)
    {
        int currentLoser = loserList[i];
        // go through all votes of current loser
        for (int j = 0; j< (int)voteList[currentLoser].size(); j++)
        {
            //make sure the first rank of vote is not for another loser
            int validRank = 0;
            int firstRank = voteList[currentLoser].front().front() -1;
            while (validRank ==0)
            {
                int returnVal = 1;
                for (int p = 0; p < loserCounter; p++)
                {
                    int tempVal = loserList[p];
                    if (firstRank == tempVal)
                    {
                        returnVal = 0;
                    }
                }
                if (returnVal == 1)
                {
                    validRank = 1;
                }
                else
                {
                    //erase the first rank of vote
                    voteList[currentLoser].front().erase(voteList[currentLoser].front().begin());
                    //update first rank
                    firstRank = voteList[currentLoser].front().front()-1;
                }
            }
            // erases first rank of vote being treated
            voteList[currentLoser].front().erase(voteList[currentLoser].front().begin());
            // adds vote to firstRank
            voteList[firstRank].push_back(voteList[currentLoser].front());
            // erases vote from currentLoser
            voteList[currentLoser].erase(voteList[currentLoser].begin());
            
        }
    }
}
