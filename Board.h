#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include "Position.h"
#include <fstream>
#include <string>

using namespace std;

class Board {
private:

public:
    Board() = default;
    Position BoardArray[8][8];
    void loadFromSave(Board* board, string gameSave);
    int playables(Board* temp, Player* currentPlayer);
    void DrawBoard(Board* temp);
    void DrawBoard();
    string checkerPlayables(int i, int j, Board* temp, Player* currentPlayer);
    string checkerFlips(int i, int j, Board* temp, Player* currentPlayer);
    int countPoints(Board* board, Player* player);
    string getBoardData(Board* board);
    void copyBoard(Board* board);
};

#endif