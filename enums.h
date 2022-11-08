#ifndef CHESS_ENUMS_H
#define CHESS_ENUMS_H
#include <iostream>
#include <map>

class enums {
public:
    enum piece_type {
        bishop,
        horse,
        king,
        pawn,
        queen,
        tower
    };

    static inline std::map<piece_type, std::string> piece_type_map{
        {piece_type::bishop, "bishop"},
        {piece_type::horse, "horse"},
        {piece_type::king, "king"},
        {piece_type::pawn, "pawn"},
        {piece_type::queen, "queen"},
        {piece_type::tower, "tower"}
    };

    enum color {
        white,
        black
    };

    static void invert_color(color& col) {
        col = col == enums::color::black ? enums::color::white : enums::color::black;
    }

    static inline std::map<color, std::string> color_map{
            {color::white, "white"},
            {color::black, "black"}
    };
};

#endif