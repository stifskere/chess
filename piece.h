#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "enums.h"
#include "string_utilities.h"

class piece : sf::Image {
public:
    piece(piece_type piece, color color){
        loadFromFile(string_utilities::format("./pieces/{0}_{1}", color, piece));
    }
};

#endif
