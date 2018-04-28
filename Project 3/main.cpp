
// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int gameSetUp() {
    cout << "Let's play Connect Four!" << endl;
    //choose game mode
    cout << "Would you like to play in compter only, 1-player, or 2-player mode? Enter '0', '1', or '2' and press 'enter'" << endl;
    int mode;
    cin >> mode;
    while (mode != 0 && mode != 1 && mode != 2){
        cout << "Selection not valid. Please enter '0', '1', or '2' and press 'enter'." << endl;
        cin >> mode;
    }
    return mode;
}


int main()
{
    int mode = gameSetUp();
    
    // one player set-up
    //SmartPlayer bp1("Bart");
    //HumanPlayer bp2("Homer");
    
    Player* bp1;
    Player* bp2;
    
    // one player set-up
    if (mode == 1){
        bp1 = new HumanPlayer("Bart");
        bp2 = new SmartPlayer("Homer");
    }
    
    // two player set-up
    else if (mode == 2){
        bp1 = new HumanPlayer("Bart");
        bp2 = new HumanPlayer("Homer");
    }
    
    // computer only set-up
    else if (mode == 0){
        bp1 = new SmartPlayer("Bart");
        bp2 = new SmartPlayer("Homer");
    }
    
    else {
        cout << "Set-up error. Restart Program" << endl;
        exit;
    }
    
    //Play
    Game g(4, 4, 3, bp2, bp1);
    g.play();
    //doScaffoldTests();
    //doPlayerTests();
    //doGameTests();
    cout << "all tests passed" << endl;
}

