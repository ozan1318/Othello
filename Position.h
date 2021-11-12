#ifndef POSITION_H
#define POSITION_H

#include <iostream>
using namespace std;

class Position {
private:
    char piece;
public:
    Position();
    explicit Position(char pos){
        piece = pos;
    }
    virtual bool canPlay();
    static const char EMPTY = ' ';
    static const char WHITE = 'W';
    static const char BLACK = 'B';

    void setPiece(char in);
    char getPiece();
};

class Unplayable_Position: public Position {
public:
    Unplayable_Position(){
        piece = UNPLAYABLE;
    };
    static const char UNPLAYABLE = ' ';
    bool canPlay(){
        return false;
    };
private:
    char piece = UNPLAYABLE;
};

class Playable_Position: public Position {
public:
    Playable_Position(){
        piece = PLAYABLE;
    }
    static const char PLAYABLE = '*';
    bool canPlay(){
        return true;
    };
private:
    char piece = PLAYABLE;
};

#endif