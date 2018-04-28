//
//  support.cpp
//  Project 3
//
//  Created by Julia Schell on 5/20/16.
//  Copyright (c) 2016 Julia Schell. All rights reserved.
//

#include "support.h"
#include "provided.h"

bool checkVert(const Scaffold& s, int N, int color){
    for (int j = 1; j <= s.cols(); j++){ //this loop checks each column on board
        int count = 0;
        for (int i = 1; i <= s.levels(); i++){ //counts number of the color, resetting count if streak is broken
            if (s.checkerAt(j, i)==color)
                count++;
            else if (s.checkerAt(j, i)== VACANT)
                break; //space means there are no more checkers in that col
            else
                count = 0;
        }
        if (count >= N)
            return true;
    }
    return false;
}

bool checkHorz(const Scaffold& s, int N, int color){
    for (int j = 1; j <= s.levels(); j++){
        int count = 0;
        for (int i = 1; i <= s.cols(); i++){
            if (s.checkerAt(i, j) == color)
                count++;
            else
                count = 0; //can still be horizontal streak after space
            if (count >= N)
                return true;
        }
    }
    return false;
}

bool checkDiagUp(const Scaffold& s, int N, int color){
    int count = 0;
    for (int startingCol = 1; startingCol <= s.cols(); startingCol++){ //checks diag starting from each column, bottom row
        for (int i = 1; startingCol + i < s.cols() && i <= s.levels(); i++){
            if (s.checkerAt(startingCol + i - 1, i) == color)
                count++;
            else
                count = 0;
        }
        if (count>=N)
            return true;
        else
            count = 0;
    }
    
    for (int startingLev = 1; startingLev <= s.levels(); startingLev++){ //checks diag starting from first colum, each row
        for (int i = 1; i <= s.cols() && startingLev + i < s.levels(); i++){
            if (s.checkerAt(i, startingLev + i - 1) == color)
                count++;
            else
                count = 0;
        }
        if (count>=N)
            return true;
        else
            count = 0;
    }
    return false;
}

bool checkDiagDown(const Scaffold& s, int N, int color){
    int count = 0;
    for (int startingCol = 1; startingCol <= s.cols(); startingCol++){ //checks diag starting from each column top row
        for (int i = 1; startingCol + i < s.cols() && (s.levels() - i + 1) > 0; i++){
            if (s.checkerAt(startingCol + i - 1,s.levels()-i+1) == color)
                count++;
            else
                count = 0;
        }
        if (count >= N)
            return true;
        else
            count = 0;
    }
    
    for (int startingLev = 1; startingLev <= s.levels(); startingLev++){ //checks diag starting from first column, each level
        for (int i = 1;  i <= s.cols() && (s.levels() - startingLev - i) > 0; i++){
            if (s.checkerAt(i,s.levels()-i-startingLev) == color)
                count++;
            else
                count = 0;
        }
        if (count >= N)
            return true;
        else
            count = 0;
    }
    return false;
}


int checkWinner(const Scaffold& s, int N){
    
    
    //check if red has N in a row
    if (checkVert(s, N, RED))
        return RED;
    else if (checkHorz(s, N, RED))
        return RED;
    else if (checkVert(s, N, BLACK))
        return BLACK;
    else if (checkHorz(s, N, BLACK))
        return BLACK;
    else if (checkDiagUp(s, N, RED))
        return RED;
    else if (checkDiagDown(s, N, RED))
        return RED;
    else if (checkDiagUp(s, N, BLACK))
        return BLACK;
    else if (checkDiagDown(s, N, BLACK))
        return BLACK;
    
    
    if (s.numberEmpty() == 0){ //if neither have won but the board is full
        return TIE_GAME;
    }
    return 2;
}