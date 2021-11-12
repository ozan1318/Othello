#include <iostream>
#include "Game.h"
using namespace std;

int main() {
    int menu, ec = 0, error = 0;
    int* endCheck = &ec;
    int* p1score;
    int* p2score;
    cout << "Welcome to Othello! Choose one of the menu options below. (1,2,3)\n\n1. Start a new game\n\n2. Quit\n\n3. Load from a save" << endl;
    do {
        cin >> menu;
        if (menu > 3 || menu < 1){
            cout << "\nIncorrect input! Please enter a number between 1 and 3." << endl;
        }
        else {
            error++;
        }
    } while(error == 0);
    Game* gamePointer = nullptr;
    switch (menu) {
        case 1:{
            gamePointer = gamePointer->start();
            endCheck = gamePointer->getEndGamePtr();
            p1score = gamePointer->getPlayer1Ptr()->getScorePtr();
            p2score = gamePointer->getPlayer2Ptr()->getScorePtr();
            break;
        }
        case 2:{
            *endCheck = 3;
            break;
        }
        case 3:{
            gamePointer = gamePointer->load();
            endCheck = gamePointer->getEndGamePtr();
            p1score = gamePointer->getPlayer1Ptr()->getScorePtr();
            p2score = gamePointer->getPlayer2Ptr()->getScorePtr();
            break;
        }
        default:{
            cout << "wrong input! game terminated.";
        }
    }
    do {
        gamePointer->play(gamePointer);
    } while (*endCheck < 2 && (*p1score + *p2score < 64) && *p1score != 0 && *p2score != 0);

    cout << "The scores are:\n" << gamePointer->getPlayer1Ptr()->getName() << ": " << *p1score << "\n" << gamePointer->getPlayer2Ptr()->getName() << ": " << *p2score << endl;

    if (*p1score > *p2score){
        cout << gamePointer->getPlayer1Ptr()->getName() << " won! Congrats!";
    }
    else if (*p1score < *p2score){
        cout << gamePointer->getPlayer2Ptr()->getName() << " won! Congrats!";
    }
    else if (*p1score = *p2score){
        cout << "Tie game!";
    }

    return 0;
}