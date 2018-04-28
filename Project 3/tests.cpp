//
//  tests.cpp
//  Project 3
//
//  Created by Julia Schell on 4/28/18.
//  Copyright © 2018 Julia Schell. All rights reserved.
//

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void doScaffoldTests()
{
    Scaffold s(3, 2);
    //creates new empty board of appropriate size
    assert(s.cols() == 3  &&  s.levels() == 2  &&
           s.numberEmpty() == 6);
    //move in empty spots return true
    assert(s.makeMove(1, RED));
    assert(s.makeMove(1, BLACK));
    //move in filled spot returns false
    assert(!s.makeMove(1, RED));
    //keeps proper track of filled spaces
    assert(s.numberEmpty() == 4);
    //keeps proper track of checker in each space
    assert(s.checkerAt(1, 1) == RED  &&  s.checkerAt(1, 2) == BLACK);
    //undo move removes last checker
    s.undoMove();
    assert(s.checkerAt(1, 2) == VACANT);
    //prints correct board
    s.display();
}

void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Scaffold s(3, 2);
    s.makeMove(1, RED);
    s.makeMove(1, BLACK);
    cout << "=========" << endl;
    int n = hp.chooseMove(s, 3, RED);
    cout << "=========" << endl;
    //won't let human insert in invalid column
    assert(n == 2  ||  n == 3);
    n = bp.chooseMove(s, 3, RED);
    //bad player inserts in valid column
    assert(n == 2  ||  n == 3);
    //smart player insert in valid colum
    n = sp.chooseMove(s, 3, RED);
    assert(n == 2  ||  n == 3);
}

void doGameTests()
{
    SmartPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Game g(3, 2, 2, &bp2, &bp1);
    int winner;
    //new game isn't complete
    assert(!g.completed(winner));
    g.takeTurn();  // Red's first move
    //game can't be won without N moves for the color, plays checker on bottom row
    assert(!g.completed(winner)  &&
           (g.checkerAt(1, 1) == RED));
    g.takeTurn();  // Black's first move
    //still neither can win
    assert(!g.completed(winner));
    //smartplayer will try one of the ways to stop badplayer from winning
    assert(g.checkerAt(1,2) == RED || g.checkerAt(2,1) == RED);
    g.takeTurn();  // Red's second move; Red must win
    assert(g.completed(winner)  &&  winner == RED);
}
