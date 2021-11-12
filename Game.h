#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Position.h"
#include "Board.h"


class Game {
public:
    Game() = default;
    Game(Player p1, Player p2);
    Game(Player p1, Player p2, int current);
    Game* start();
    static Game* load();
    void play(Game* gamePoint);
    Board* getBoard();
    Player* getCurrentPlayer();
    void switchPlayer();
    void TakeTurn(Game* gamePoint);
    Player* getPlayer1Ptr();
    Player* getPlayer2Ptr();
    int* getEndGamePtr();
private:
    void save(Game* gamePoint);
    Board* board;
    Player* p1ptr;
    Player* p2ptr;
    Player* currentPlayer;
    Player* waitingPlayer;
    int endGame = 0;
    int* endGamePtr = &endGame;
};

#endif