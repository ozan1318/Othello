#include "Board.h"
#include <iostream>

void Board::loadFromSave(Board* board, string gameSave) {
    int temp = 0;
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (gameSave[temp] == '0') {
                board->BoardArray[i][j].setPiece(' ');
            }
            else if (gameSave[temp] == '1'){
                board->BoardArray[i][j].setPiece('W');
            }
            else if (gameSave[temp] == '2'){
                board->BoardArray[i][j].setPiece('B');
            }
            temp += 1;
        }
    }
}

string Board::checkerPlayables(int i, int j, Board* temp, Player* currentPlayer) {
    int posC = j, posL = i;
    char opposite;
    if (currentPlayer->getColor() == 'W'){opposite = 'B';}
    else {opposite = 'W';}
    string* returns;
    returns = new string;
    //looking left for playable positions
    posC = j;
    posL = i;
    if (posC > 1){
        posC--;
        if (temp->BoardArray[posL][posC].getPiece() == opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece()== opposite){
                    posC--;
                }
                else if (temp->BoardArray[posL][posC].getPiece()== ' '){
                    *returns += to_string(posC);
                    *returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posC>=0);
        }
    }

    //looking up for playable positions
    posC = j;
    posL = i;
    if (posL > 1){
        posL--;
        if (temp->BoardArray[posL][posC].getPiece()== opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece()== opposite){
                    posL--;
                }
                else if (temp->BoardArray[posL][posC].getPiece()== ' '){
                    *returns += to_string(posC);
                    *returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posL>=0);
        }
    }

    //looking right for playable positions
    posC = j;
    posL = i;
    if (posC < 6){
        posC++;
        if (temp->BoardArray[posL][posC].getPiece()== opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece()== opposite){
                    posC++;
                }
                else if (temp->BoardArray[posL][posC].getPiece()== ' '){
                    *returns += to_string(posC);
                    *returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posC<=7);
        }
    }

    //looking down for playable positions
    posC = j;
    posL = i;
    if (posL < 6){
        posL++;
        if (temp->BoardArray[posL][posC].getPiece()== opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece()== opposite){
                    posL++;
                }
                else if (temp->BoardArray[posL][posC].getPiece()== ' '){
                    *returns += to_string(posC);
                    *returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posL<=7);
        }
    }

    // looking up-left for playable positions
    posC = j;
    posL = i;
    if (posC > 1 && posL > 1){
        posC--;
        posL--;
        if (temp->BoardArray[posL][posC].getPiece() == opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece() == opposite){
                    posC--;
                    posL--;
                }
                else if (temp->BoardArray[posL][posC].getPiece() == ' '){
                    *returns += to_string(posC);
                    *returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posC>=0 && posL>=0);
        }
    }
    // looking down-right for playable positions
    posC = j;
    posL = i;
    if (posC < 6 && posL < 6) {
        posC++;
        posL++;
        if (temp->BoardArray[posL][posC].getPiece() == opposite) {
            do {
                if (temp->BoardArray[posL][posC].getPiece() == opposite) {
                    posC++;
                    posL++;
                } else if (temp->BoardArray[posL][posC].getPiece() == ' ') {
                    *returns += to_string(posC);
                    *returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            } while (posC <= 7 && posL <= 7);
        }
    }

    // looking up-right for playable positions
    posC = j;
    posL = i;
    if (posC < 6 && posL > 1){
        posC++;
        posL--;
        if (temp->BoardArray[posL][posC].getPiece() == opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece() == opposite){
                    posC++;
                    posL--;
                }
                else if (temp->BoardArray[posL][posC].getPiece() == ' '){
                    *returns += to_string(posC);
                    *returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posC<=7 && posL>=0);
        }
    }

    // looking down-left for playable positions
    posC = j;
    posL = i;
    if (posC > 1 && posL < 6) {
        posC--;
        posL++;
        if (temp->BoardArray[posL][posC].getPiece() == opposite) {
            do {
                if (temp->BoardArray[posL][posC].getPiece() == opposite) {
                    posC--;
                    posL++;
                } else if (temp->BoardArray[posL][posC].getPiece() == ' ') {
                    *returns += to_string(posC);
                    *returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            } while (posC >= 0 && posL <= 7);
        }
    }
    string returnString = *returns;
    return returnString;
}

void Board::copyBoard(Board* temp) {
    for (int i = 0; i <=7 ; i++){
        for (int j = 0; j <= 7; j++){
            temp->BoardArray[i][j].setPiece(BoardArray[i][j].getPiece());
        }
    }
}

int Board::playables(Board* temp, Player* currentPlayer) {
    int counter = 0;
    string playables;
    for (int i = 0; i <= 7; i++){ // loop through lines
        for (int j = 0; j <= 7; j++){ // loop through columns
            if (temp->BoardArray[i][j].getPiece() == currentPlayer->getColor()){ // check if position is current player's piece
                playables = checkerPlayables(i, j, temp, currentPlayer); // run checker to find playable positions from the piece
                if (playables.length() != 0) { // check if checker returned playable positions
                    for (int k = 0; k < playables.length(); k += 2) {//take positions from checker and insert playability markers
                        string strc(1, playables[k]);
                        int c = stoi(strc);
                        string strl(1, playables[k+1]);
                        int l = stoi(strl);
                        temp->BoardArray[l][c].setPiece('*');
                        counter++;
                    }
                }
            }
        }
    }
    return counter;
}

void Board::DrawBoard(Board* temp) {
    cout << endl << " |a|b|c|d|e|f|g|h|" << endl;
    for (int i = 0; i <= 7; i++) {
        cout << i+1 << "|";
        for (int j = 0; j <= 7; j++) {
            cout << temp->BoardArray[i][j].getPiece() << "|";
        }
        cout << i+1 << endl;
    }
    cout << " |a|b|c|d|e|f|g|h|" << endl;
}

void Board::DrawBoard() {
    cout << endl << " |a|b|c|d|e|f|g|h|" << endl;
    for (int i = 0; i <= 7; i++) {
        cout << i+1 << "|";
        for (int j = 0; j <= 7; j++) {
            cout << BoardArray[i][j].getPiece() << "|";
        }
        cout << i+1 << endl;
    }
    cout << " |a|b|c|d|e|f|g|h|" << endl;
}

string Board::checkerFlips(int i, int j, Board* temp, Player* currentPlayer) {
    int posC, posL;
    char player, opposite;
    player = currentPlayer->getColor();
    if (player == 'W'){opposite = 'B';}
    else {opposite = 'W';}
    string returns;

    //looking left for flips
    posC = i;
    posL = j;
    if (posC > 1){
        posC--;
        if (temp->BoardArray[posL][posC].getPiece() == opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece() == opposite){
                    posC--;
                }
                else if (temp->BoardArray[posL][posC].getPiece() == player){
                    returns += to_string(posC);
                    returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posC>=0);
        }
    }

    //looking up for flips
    posC = i;
    posL = j;
    if (posL > 1) {
        posL--;
        if (temp->BoardArray[posL][posC].getPiece() == opposite) {
            do {
                if (temp->BoardArray[posL][posC].getPiece() == opposite) {
                    posL--;
                } else if (temp->BoardArray[posL][posC].getPiece() == player) {
                    returns += to_string(posC);
                    returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            } while (posL >= 0);
        }
    }

    //looking right for flips
    posC = i;
    posL = j;
    if (posC < 6){
        posC++;
        if (temp->BoardArray[posL][posC].getPiece() == opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece() == opposite){
                    posC++;
                }
                else if (temp->BoardArray[posL][posC].getPiece() == player){
                    returns += to_string(posC);
                    returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posC<=7);
        }
    }

    //looking down for flips
    posC = i;
    posL = j;
    if (posL < 6){
        posL++;
        if (temp->BoardArray[posL][posC].getPiece() == opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece() == opposite){
                    posL++;
                }
                else if (temp->BoardArray[posL][posC].getPiece() == player){
                    returns += to_string(posC);
                    returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posL<=7);
        }
    }

    // looking up-left for flips
    posC = i;
    posL = j;
    if (posC > 1 && posL > 1){
        posC--;
        posL--;
        if (temp->BoardArray[posL][posC].getPiece() == opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece() == opposite){
                    posC--;
                    posL--;
                }
                else if (temp->BoardArray[posL][posC].getPiece() == player){
                    returns += to_string(posC);
                    returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posC>=0 && posL>=0);
        }
    }

    // looking down-right for flips
    posC = i;
    posL = j;
    if (posC < 6 && posL < 6){
        posC++;
        posL++;
        if (temp->BoardArray[posL][posC].getPiece() == opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece() == opposite){
                    posC++;
                    posL++;
                }
                else if (temp->BoardArray[posL][posC].getPiece() == player){
                    returns += to_string(posC);
                    returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posC<=6 && posL<=6);
        }
    }

    // looking up-right for flips
    posC = i;
    posL = j;
    if (posC < 6 && posL > 1){
        posC++;
        posL--;
        if (temp->BoardArray[posL][posC].getPiece() == opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece() == opposite){
                    posC++;
                    posL--;
                }
                else if (temp->BoardArray[posL][posC].getPiece() == player){
                    returns += to_string(posC);
                    returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posC<=6 && posL>=0);
        }
    }

    // looking down-left for flips
    posC = i;
    posL = j;
    if (posC > 1 && posL < 6){
        posC--;
        posL++;
        if (temp->BoardArray[posL][posC].getPiece() == opposite){
            do{
                if (temp->BoardArray[posL][posC].getPiece() == opposite){
                    posC--;
                    posL++;
                }
                else if (temp->BoardArray[posL][posC].getPiece() == player){
                    returns += to_string(posC);
                    returns += to_string(posL);
                    break;
                }
                else {
                    break;
                }
            }while(posC>=0 && posL<=6);
        }
    }

    return returns;
}

int Board::countPoints(Board* board, Player* player) {
    int playerScore = 0;
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (board->BoardArray[i][j].getPiece() == player->getColor()){
                playerScore++;
            }
        }
    }
    return playerScore;
}

string Board::getBoardData(Board* board){
    string boardData = "";
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (board->BoardArray[i][j].getPiece() == ' '){
                boardData += "0";
            }
            else if (board->BoardArray[i][j].getPiece() == 'W') {
                boardData += "1";
            }
            else if (board->BoardArray[i][j].getPiece() == 'B') {
                boardData += "2";
            }
        }
    }
    return boardData;
}
