#ifndef CHESS_ENUMS_H
#define CHESS_ENUMS_H
#include <iostream>
#include <map>
#include "SFML/Graphics/Texture.hpp"

namespace enums {
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
        black,
        possible
    };

    static void invert_color(color& col) {
        col = col == enums::black ? enums::white : enums::black;
    }

    static color invert_color_return(color col) {
        invert_color(col);
        return col;
    }

    static inline std::map<color, std::string> color_map{
            {white, "w"},
            {black, "b"},
            {possible, "p"}
    };
};

class pieces {
    class sub_pieces {
    public:
        std::map<enums::piece_type, sf::Texture> pieces{};

        sf::Texture &operator[](enums::piece_type type){
            return pieces[type];
        }
    };
    std::map<enums::color, sub_pieces> pieces;

    void loadPieces(){
        pieces[enums::black][enums::pawn].loadFromFile("./pieces/b_pawn.png");
        pieces[enums::white][enums::pawn].loadFromFile("./pieces/w_pawn.png");
        pieces[enums::black][enums::bishop].loadFromFile("./pieces/b_bishop.png");
        pieces[enums::white][enums::bishop].loadFromFile("./pieces/w_bishop.png");
        pieces[enums::black][enums::tower].loadFromFile("./pieces/b_tower.png");
        pieces[enums::white][enums::tower].loadFromFile("./pieces/w_tower.png");
        pieces[enums::black][enums::king].loadFromFile("./pieces/b_king.png");
        pieces[enums::white][enums::king].loadFromFile("./pieces/w_king.png");
        pieces[enums::black][enums::horse].loadFromFile("./pieces/b_horse.png");
        pieces[enums::white][enums::horse].loadFromFile("./pieces/w_horse.png");
        pieces[enums::black][enums::queen].loadFromFile("./pieces/b_queen.png");
        pieces[enums::white][enums::queen].loadFromFile("./pieces/w_queen.png");
    }

    friend int main();

public:
    sub_pieces &operator[](enums::color color){
        return pieces[color];
    }
} tex_pieces;

#endif