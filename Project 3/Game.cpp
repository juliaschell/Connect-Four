// Game.cpp

#include "provided.h"
#include "support.h"
#include <queue>
#include <iostream>
using namespace std;

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black); 
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checkerAt(int c, int r) const;
private:
    Scaffold* board;
    int goalNum;
    Player * mR;
    Player * mB;
    int currTurn = RED;
    
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    board = new Scaffold(nColumns, nLevels);
    goalNum = N;
    mR = red;
    mB = black;
}




bool GameImpl::completed(int& winner) const
{
    if (checkWinner(*board, goalNum)==RED){
        winner = RED;
        return true;
    }
    else if(checkWinner(*board, goalNum)==BLACK){
        winner = BLACK;
        return true;
    }
    else if(checkWinner(*board, goalNum)==TIE_GAME){
        winner = TIE_GAME;
        return true;
    }


    return false;
    
}

bool GameImpl::takeTurn()
{
    int winner;
    if (completed(winner))
        return false;
    if (currTurn == RED){
        board->makeMove(mR->chooseMove(*board, goalNum, RED), RED);
        currTurn = BLACK;
        board->display();
        if (mR->isInteractive() && !mB->isInteractive())
            cout << "Our turn! Please wait" << endl;
        return true;}
    if (currTurn == BLACK){
        board->makeMove(mB->chooseMove(*board, goalNum, BLACK), BLACK);
        currTurn = RED;
        board->display();
        if (mB->isInteractive() && !mR->isInteractive())
            cout << "Our turn! Please wait" << endl;
        return true;
    }
    
    return false;  //  This is not always correct; it's just here to compile
}

void GameImpl::play()
{
    int winner;
    do {
        takeTurn();
        if (!mR->isInteractive() && !mB->isInteractive() ){
            cout << "Press enter to continue to next move" << endl;
            cin.get();
        }
    } while (!completed(winner));
        
    completed(winner);
    if (winner == RED)
        cout << "Team red has  won!";
    else if (winner == BLACK)
        cout << "Team black has won!";
    else if (winner == TIE_GAME)
        cout << "It was a tie!";
    
}

int GameImpl::checkerAt(int c, int r) const
{
    
    return board->checkerAt(c,r);  //  This is not always correct; it's just here to compile
} 

//******************** Game functions *******************************

// These functions simply delegate to GameImpl's functions.
// You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
