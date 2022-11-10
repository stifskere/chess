#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "enums.h"
#include "string_utilities.h"

#include <SFML/Graphics.hpp>

class piece : public sf::Sprite {
private:
    sf::RenderWindow &w;
    sf::Vector2i pos;
    enums::piece_type p;
    enums::color c;
    bool hasMoved = false;
    friend int main();
public:
    piece(enums::piece_type piece, enums::color color, sf::RenderWindow &window, sf::Vector2i position) : sf::Sprite(), w(window) {
        setTexture(tex_pieces[color][piece]);
        pos = position;
        p = piece;
        c = color;
    }

    void updatePiece(){
        sf::Vector2u wSize = w.getSize();
        uint32_t smallest = std::min(wSize.x, wSize.y);
        setScale(sf::Vector2f{(float)smallest, (float)smallest} / 60.0f / 8.0f);
        if (wSize.x != smallest) {
            setPosition((sf::Vector2f) (pos * (int) smallest) / 8.f + sf::Vector2f{(float)(wSize.x - wSize.y) / 2.f, 0});
        }else{
            setPosition((sf::Vector2f) (pos * (int) smallest) / 8.f + sf::Vector2f{0, (float)(wSize.y - wSize.x) / 2.f});
        }
    }
};

#endif
