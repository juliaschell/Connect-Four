// Scaffold.cpp

#include <vector>
#include <iostream>
#include "provided.h"
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels); 
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove();
private:
    int mCol, mLev;
    int gWidth, gHeight;
    vector<vector<char>> grid;
    vector<int> moves;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns < 0 || nLevels < 0){
        cerr << "Scaffold not valid.";
        exit(0);
    }
    mCol = nColumns;
    mLev = nLevels;
    gWidth = 2*mCol + 1;
    gHeight = mLev + 1;
    
    grid.resize(gHeight);  // specified levels + bottom level
    for (int i = 0; i < gHeight; i++){
        grid[i].resize(gWidth);// specified empty columns + border cols
        for (int j = 0; j < gWidth; j++){
        if (j%2 == 0){ //even indexes are the boarder columns
            if (i == mLev)
                grid[i][j] = '+'; //for bottom row
            else
                grid[i][j] = '|';}
        else{
            if (i == mLev)
                grid[i][j] = '-'; //for bottom row
            else
                grid[i][j] = char(32);}}
    }
    
    
    
    
}

int ScaffoldImpl::cols() const
{
    return mCol;  //  This is not always correct; it's just here to compile
}

int ScaffoldImpl::levels() const
{
    return mLev;  //  This is not always correct; it's just here to compile
}

int ScaffoldImpl::numberEmpty() const
{
    int contains = 0;
    for (int i = 0; i < gHeight; i++){
        for (int j = 0; j < gWidth; j++){
            if (grid[i][j] == ' ')
                contains++;
        }
    }
    
    return contains;  //  This is not always correct; it's just here to compile
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (grid[gHeight - level - 1][column*2 - 1] == 'R')
        return RED;
    else if (grid[gHeight - level - 1][column*2 - 1] == 'B')
        return BLACK;
    return VACANT;  //  This is not always correct; it's just here to compile
}

void ScaffoldImpl::display() const
{
    for (int i = 0; i < gHeight; i++){
        for (int j = 0; j < gWidth; j++)
            cout << grid[i][j];
        cout << endl;
    }
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    int i = 0;
    //set i to first row with checker/bottom row
    for (i = 0; grid[i][2*column - 1] == ' '; i++);
    if (i == 0)
        return false; //that column is full
    
    if (color == RED)
        grid[i-1][2*column - 1] = 'R';
    else if (color == BLACK)
        grid[i-1][2*column - 1] = 'B';
    else
        return false; //color was not red or black
    
    moves.push_back(column*2 - 1); //add column  of most recent move
    return true;
}

int ScaffoldImpl::undoMove()
{
    int i = 0;
    if (moves.empty()) //if the grid is empty
        return 0;
    
    for (i = 0; grid[i][moves.back()] == ' '; i++);
    grid[i][moves.back()] = ' ';
    i = moves.back();
    moves.pop_back(); //remove this move from vector
    return i;  //  This is not always correct; it's just here to compile
}

//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
