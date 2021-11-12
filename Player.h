#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
private:
    string name;
    int score;
    char color;
    int* scorePtr = &score;
public:
    explicit Player(string Name){
        name = Name;
        score = 0;
        color = ' ';
    }
    Player(string Name, int Score){
        name = Name;
        score = Score;
        color = ' ';
    }
    string getName();
    int getScore();
    void setScore(int newScore);
    char getColor();
    void setColor(char colorSet);
    int* getScorePtr();
};

#endif