//
//  support.h
//  Project 3
//
//  Created by Julia Schell on 5/20/16.
//  Copyright (c) 2016 Julia Schell. All rights reserved.
//

#ifndef __Project_3__support__
#define __Project_3__support__

#include <stdio.h>
#include "provided.h"

bool checkVert(const Scaffold& s, int N, int color);
bool checkHorz(const Scaffold& s, int N, int color);
bool checkDiagUp(const Scaffold& s, int N, int color);
bool checkDiagDown(const Scaffold& s, int N, int color);
int checkWinner(const Scaffold& s, int N);

#endif /* defined(__Project_3__support__) */
