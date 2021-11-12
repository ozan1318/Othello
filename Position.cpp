#include "Position.h"

bool Position::canPlay() {
    if (piece==EMPTY)
        return true;
    else
        return false;
}

Position::Position(){
    piece = ' ';
}

void Position::setPiece(char in) {
    piece = in;
}

char Position::getPiece() {
    return piece;
}
