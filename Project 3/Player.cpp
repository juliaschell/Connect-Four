// Player.cpp

#include "provided.h"
#include "support.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int determineBestCompMove(Scaffold& s, int N, int depth, int & mRate, int color);
    int chooseMove(const Scaffold& s, int N, int color);
    virtual bool isInteractive() const {return true;};
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
        return -1;
    int col;
    cout << "Your move! enter the column number to place a checker: " << endl;
    cin >> col;
    // col number must be between 0 and the number of columns on the board, and it must have at least one empty space
    while (col <= 0 || col > s.cols() || s.checkerAt(col, s.levels())!= -1){
        cout << "Invalid move. Please try again: " << endl;
        cin >> col;
    }
    return col;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
        return -1;
    int c = s.cols();
    int r = s.levels();
    for (int i = 1; i <= c; i++)
            if (s.checkerAt(i,r) == VACANT) // if column has at least one empty space, insert there
                return i;
    
    return -1;  //  This is not always correct; it's just here to compile
}


int rate(const Scaffold& s, int N, int color){
    if (checkWinner(s,N) == color)
        return 1;
    if (checkWinner(s,N) == TIE_GAME)
        return 0;
    else
        return -1;
}


int SmartPlayerImpl::determineBestCompMove(Scaffold& s, int N, int depth, int & mRate, int color){
    //store the output of each possible moves
    int ratings[s.cols()];
    for (int i = 1; i<= s.cols(); i++){
        bool mm = s.makeMove(i, color);
        if (mm == false)
            ratings[i-1] = -2;
        else{
            int r = rate(s, N, color);
            if(r == 1 || r == 0)
                ratings[i-1] = r * (10000 - depth);
            else {
                int nRate;
                determineBestCompMove(s, N, depth + 1, nRate, abs(color-1));
                ratings[i-1] = (-1) * nRate;
            }
        s.undoMove();    
        }
        
    }
    
    int returnCol = 0;
    for (int i = 0; i < s.cols(); i++){
        if (ratings[i] == 1){
            returnCol = i;
            break;}
    }
    for (int i = 0; i < s.cols(); i++){
        if (ratings[i] > ratings[returnCol])
            returnCol = i;
    }
    mRate = ratings[returnCol];
    return returnCol+1;
}



int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    Scaffold temp(s);
    int rating, colChoice;
    colChoice = determineBestCompMove(temp, N, 0, rating, color);
    return colChoice;
  //  This is not always correct; it's just here to compile
}

//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
