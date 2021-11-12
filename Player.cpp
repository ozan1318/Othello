#include "Player.h"

string Player::getName() {
    return name;
}

int Player::getScore(){
    return score;
}

char Player::getColor() {
    return color;
}

void Player::setColor(char colorSet) {
    color = colorSet;
}

void Player::setScore(int newScore) {
    score = newScore;
}

int* Player::getScorePtr() {
    return scorePtr;
}