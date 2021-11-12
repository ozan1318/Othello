#include "Game.h"
#include <iostream>
#include <string>
using namespace std;

Game::Game(Player p1, Player p2){//constructor for new game
    board = new Board;
    p1ptr = new Player(p1.getName());
    p2ptr = new Player(p2.getName());
    currentPlayer = p1ptr;
    waitingPlayer = p2ptr;
    p1ptr->setColor('B');
    p2ptr->setColor('W');
}

Game::Game(Player p1, Player p2, int current) {//constructor for loading from a save
    board = new Board;
    p1ptr = new Player(p1.getName());
    int p1s = p1.getScore(), p2s = p2.getScore();
    p1ptr->setScore(p1s);
    p2ptr = new Player(p2.getName());
    p2ptr->setScore(p2s);
    currentPlayer = (current==1)? p1ptr : p2ptr;
    waitingPlayer = (current==1)? p2ptr : p1ptr;
    p1ptr->setColor('B');
    p2ptr->setColor('W');
    }

Board* Game::getBoard() {
    return board;
}

Game* Game::start() {
    string p1n, p2n; // input strings for player names
    cout << "Please enter player 1's name" << endl;
    cin >> p1n;
    cout << "Please enter player 2's name" << endl;
    cin >> p2n;
    Player p1(p1n); // create players
    Player p2(p2n);
    char answer;
    int answer2, error = 0, error2 = 0;
    cout << "\nWould you like to start a game with the standard positions or with non-standard positions? (y/n)\n";
    do {//check for incorrect input
        cin >> answer;
        if (answer != 'y' && answer != 'n'){
            cout << "\nIncorrect input! This must be 'y' or 'n'. Please try again.\n";
        }
        else {
            error++;
        }
    } while (error == 0);
    string fileName;
    switch (answer){
        case 'y':{
            cout << endl << "Staring game with standard initial positions" << endl;
            fileName = "Regular.txt";
            break;
        }
        case 'n':{
            cout << endl << "Which of the non-standard positions would you like? Choose from 1-4." << endl;
            do{
                cin >> answer2;
                if (answer2 != 1 && answer2 != 2 && answer2 != 3 && answer2 != 4){
                    cout << "\nIncorrect input! This must be a number between 1 and 4.\n";
                }
                else{
                    error2++;
                }
            } while (error2 == 0);
            fileName = "NS-";
            fileName += to_string(answer2);
            fileName += ".txt";
            cout << endl << "Staring game with non-standard position set " << answer2 << "." << endl;
            break;
        }
        default: {
            cout << "\nCongrats! I don't know how you broke it this bad.\n";
        }
    }
    Game* current = new Game(p1, p2); // construct new game with players
    string gameSave; // create string to save savegame file data
    fstream inFile; // create savegame fstream object
    inFile.open(fileName.c_str());
    getline(inFile, gameSave); // get data from savegame file
    current->board->loadFromSave(current->board, gameSave); // load save data to game board
    inFile.close(); // close savegame file
    return current;
}

Game* Game::load() {
    string saveName; // create string to find savegame file
    cout << "Enter savegame number" << endl;
    cin >> saveName; // determine desired save file
    saveName += ".txt";
    string gameSave, p1n, p2n, temp, current;
    int p1s=0, p2s=0, i=0;
    fstream inFile; // create fstream object
    inFile.open(saveName, ios::in); // open savegame file
    Game* game = nullptr;
    while(getline(inFile, gameSave)){
        switch (i){
            case 0: {//get save file info for player 1
                int z = 0;
                temp = "";
                while (gameSave[z] != ' ') {
                    p1n += gameSave[z];
                    z++;
                }
                z = gameSave.length();
                while (gameSave[z-1] != ' ') {
                    temp += gameSave[z-1];
                    z--;
                }
                p1s = stoi(temp);
                break;
            }
            case 1: {//get save file info for player 2
                int z = 0;
                temp = "";
                while (gameSave[z] != ' ') {
                    p2n += gameSave[z];
                    z++;
                }
                z = gameSave.length();
                while (gameSave[z-1] != ' ') {
                    temp += gameSave[z-1];
                    z--;
                }
                p2s = stoi(temp);
                break;
            }
            case 2:{//determine current player from save file
                current = gameSave;
                break;
            }
            case 3:{//construct the players and the game from the info from the save file
                Player p1(p1n, p1s);
                Player p2(p2n, p2s);
                int currentInt = stoi(current);
                game = new Game(p1, p2, currentInt);
                game->getBoard()->loadFromSave(game->getBoard(),gameSave);
                break;
            }
            default:{
                cout << "\nCongrats! I don't know how you broke it this bad. Please check the savegame file you entered to ensure everything is right.\n";
            }
        }
        i++;
    }
    inFile.close(); // close savegame file
    return game;
}

Player* Game::getCurrentPlayer() {
    return currentPlayer;
}

void Game::switchPlayer() {
    Player* temp = currentPlayer; // save current player temporarily
    currentPlayer = waitingPlayer; // set other player as current
    waitingPlayer = temp; // set current as waiting
}

void Game::TakeTurn(Game* gamePoint) {
    Board *temp = new Board; // create temp board
    gamePoint->getBoard()->copyBoard(temp);
    int playable, ctr = 0;
    playable = gamePoint->getBoard()->playables(temp,
                                                gamePoint->getCurrentPlayer()); // manipulate temp to return a board with playable positions shown
    if (playable != 0) { // check if player has moves, switch players if not.
        temp->DrawBoard(temp); // draw the temp board
        char colStr;
        int line, colInt = -1;
        string flips;
        do {//checking correct inputs
            cout << "Please enter the position you would like to play (example: a 1):" << endl;
            cin >> colStr; // take position inputs from the player
            cin >> line;
            switch (colStr) { // translate string input to coordinate number
                case 'a': {
                    colInt = 0;
                    break;
                }
                case 'b': {
                    colInt = 1;
                    break;
                }
                case 'c': {
                    colInt = 2;
                    break;
                }
                case 'd': {
                    colInt = 3;
                    break;
                }
                case 'e': {
                    colInt = 4;
                    break;
                }
                case 'f': {
                    colInt = 5;
                    break;
                }
                case 'g': {
                    colInt = 6;
                    break;
                }
                case 'h': {
                    colInt = 7;
                    break;
                }
                default: {
                    cout << "\nIncorrect column input! Column must be a letter between a-h. Please try again.\n";
                }
            }
            if ((0 <= colInt) && (colInt <= 7) && (1 <= line) && (line <= 8)) {
                ctr++;
            } else {
                cout << "\nIncorrect line input! Line must be a number between 1-8. Please try again.\n";
            }
        } while (ctr == 0);
        line--;
        if (temp->BoardArray[line][colInt].getPiece() == '*') { // check if the position is playable
            gamePoint->getBoard()->BoardArray[line][colInt].setPiece(
                    gamePoint->currentPlayer->getColor()); // play position
            flips = temp->checkerFlips(colInt, line, temp,
                                       gamePoint->currentPlayer); // take position coordinates for flipping
            if (flips.length() != 0) { // check if checker returned flipping positions
                /* The flipper returns a string of coordinates, with each pair being a coordinate (i.e. in 2734,
                 * the coordinates are [2][7] and [3][4]). These coordinates are the pieces that are at the edge
                 * of the line that will be flipped by the move. The for loop below looks for the first two numbers,
                 * turns them to ints and uses these ints to find the board position. Then it calculates the
                 * relative position of the coordinate returned to the coordinate that was played. It then uses
                 * the result to find which pieces are to be flipped as a result of the move.
                 */
                for (int k = 0; k < flips.length(); k += 2) {//take positions from checker and flip
                    string strc(1, flips[k]); // take positions,
                    int c = stoi(strc); // and turn to ints.
                    string strl(1, flips[k + 1]);
                    int l = stoi(strl);
                    if (abs(colInt - c) == 0 && abs(line - l) != 0) {
                        /* the above statement checks if the returned coordinate is on the same column as the played piece.
                         * If it is, then the appropriate pieces on the line are flipped.*/
                        if (l > line) { // check which coordinate is bigger
                            for (int i = line + 1; i < l; i++) {
                                gamePoint->getBoard()->BoardArray[i][colInt].setPiece(currentPlayer->getColor());
                            }
                        } else if (line > l) {
                            for (int i = l + 1; i < line; i++) {
                                gamePoint->getBoard()->BoardArray[i][colInt].setPiece(currentPlayer->getColor());
                            }
                        }
                    } else if (abs(colInt - c) != 0 && abs(line - l) == 0) {
                        /* the above statement checks if the returned coordinate is on the same line as the played piece.
                         * If it is, then the appropriate pieces on the line are flipped.*/
                        if (colInt > c) {
                            for (int i = c + 1; i <= colInt; i++) {
                                gamePoint->getBoard()->BoardArray[line][i].setPiece(currentPlayer->getColor());
                            }
                        } else if (c > colInt) {
                            for (int i = colInt + 1; i <= c; i++) {
                                gamePoint->getBoard()->BoardArray[line][i].setPiece(currentPlayer->getColor());
                            }
                        }
                    } else if (abs(colInt - c) != 0 && abs(line - l) != 0) {
                        /* If neither the same column nor line, then the piece is on the diagonal.
                         * The statements below flips the diagonal*/
                        if (l > line) {
                            if (colInt > c) {
                                for (int i = line + 1, j = c + 1; i < l && j < colInt; i++, j++) {
                                    gamePoint->getBoard()->BoardArray[i][j].setPiece(currentPlayer->getColor());
                                }
                            } else if (c > colInt) {
                                for (int i = line + 1, j = colInt + 1; i < l && j < c; i++, j++) {
                                    gamePoint->getBoard()->BoardArray[i][j].setPiece(currentPlayer->getColor());
                                }
                            }
                        } else if (line > l) {
                            if (colInt > c) {
                                for (int i = l + 1, j = c + 1; i < line && j < colInt; i++, j++) {
                                    gamePoint->getBoard()->BoardArray[i][j].setPiece(currentPlayer->getColor());
                                }
                            } else if (c > colInt) {
                                for (int i = l + 1, j = colInt + 1; i < line && j < c; i++, j++) {
                                    gamePoint->getBoard()->BoardArray[i][j].setPiece(currentPlayer->getColor());
                                }
                            }
                        }
                    }
                }
            }
        }
        gamePoint->getBoard()->DrawBoard(); // the board is drawn again to show the board state after the move
        gamePoint->currentPlayer->setScore(
                gamePoint->getBoard()->countPoints(gamePoint->getBoard(), gamePoint->currentPlayer));
        gamePoint->waitingPlayer->setScore(
                gamePoint->getBoard()->countPoints(gamePoint->getBoard(), gamePoint->waitingPlayer));
        cout << endl << "Your turn is over." << endl;
        gamePoint->switchPlayer();
        delete temp;
    } else { // if player doesn't have a move, turn is over
        delete temp; // the temp board is deleted
        int *temp2 = gamePoint->getEndGamePtr(); // increments counter under the game object that determines when a game is over
        *temp2 = 1 + *temp2;
        int choice, error = 0;
        cout << endl << "No valid moves! Please choose one of the following options. (1,2,3)\n\n1. End turn\n\n2. End game\n\n3. Save game" << endl;
        cin >> choice;
        do {
            switch (choice) {
                case 1: {
                    gamePoint->switchPlayer(); // the players are switched
                    gamePoint->play(gamePoint);
                    error++;
                    break;
                }
                case 2: {
                    int *eGP;
                    eGP = gamePoint->getEndGamePtr();
                    *eGP += 1;
                    error++;
                    break;
                }
                case 3: {
                    save(gamePoint);
                    break;
                }
                default:{
                    cout << "\nIncorrect input! Please enter a number between 1 and 3." << endl;
                }
            }
        } while (error == 0);
    }
}

void Game::play(Game* gamePoint) {
    int choice, error=0;
    cout << "Player " << gamePoint->getCurrentPlayer()->getName() << "'s turn.\n" <<"\nWhat would you like to do? (1,2,3)\n\n1. Make a move\n\n2. End game\n\n3. Save game" << endl;
    cin >> choice;
    do{
        switch (choice) {
            case 1:{
                gamePoint->TakeTurn(gamePoint);
                error++;
                break;
            }
            case 2:{
                int* tempPtr;
                tempPtr = gamePoint->getEndGamePtr();
                *tempPtr = 3;
                error++;
                break;
            }
            case 3:{
                save(gamePoint);
                error++;
                break;
            }
            default: {
                cout << "\nIncorrect input! Please enter a number between 1 and 3." << endl;
            }
        }
    } while(error == 0);
}

void Game::save(Game *gamePoint) {
    string counterStr;
    int counter;

    ifstream saveGameCounter;
    saveGameCounter.open("saveGameCounter.txt", ios::in);
    getline(saveGameCounter, counterStr);
    counter = stoi(counterStr);
    saveGameCounter.close();
    remove("saveGameCounter.txt");

    counter++;

    ofstream newSaveGameCounter;
    newSaveGameCounter.open("saveGameCounter.txt", ios::out);
    newSaveGameCounter << counter;
    newSaveGameCounter.close();

    counterStr += ".txt";
    ofstream outFile;
    outFile.open(counterStr, ios::out);
    string p1data = gamePoint->getPlayer1Ptr()->getName() + " " + to_string(gamePoint->getPlayer1Ptr()->getScore()) + "\n";
    string p2data = gamePoint->getPlayer2Ptr()->getName() + " " + to_string(gamePoint->getPlayer2Ptr()->getScore()) + "\n";
    string currentPlayerData;
    if (gamePoint->currentPlayer == gamePoint->getPlayer1Ptr()){
        currentPlayerData = "1\n";
    }
    else if (gamePoint->currentPlayer == gamePoint->getPlayer2Ptr()){
        currentPlayerData = "2\n";
    }
    string boardData = gamePoint->getBoard()->getBoardData(gamePoint->getBoard());
    outFile << p1data;
    outFile << p2data;
    outFile << currentPlayerData;
    outFile << boardData;
    outFile.close();
}

Player* Game::getPlayer1Ptr() {
    return p1ptr;
}

Player* Game::getPlayer2Ptr() {
    return p2ptr;
}

int* Game::getEndGamePtr(){
    return endGamePtr;
}