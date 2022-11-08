#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "enums.h"
#include "string_utilities.h"

#include <SFML/Graphics.hpp>


class piece : sf::Image {
public:
    piece(enums::piece_type piece, enums::color color) : sf::Image() {
        loadFromFile(string_utilities::format("./pieces/{0}_{1}", enums::color_map[color], enums::piece_type_map[piece]));
    }
};

#endif
