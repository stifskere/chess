#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "enums.h"
#include "string_utilities.h"

#include <SFML/Graphics.hpp>

class piece : public sf::Sprite {
private:
    static inline sf::RenderWindow* w = nullptr;
    enums::piece_type p;
    bool hasMoved = false;
    friend int main();
public:
    piece(enums::piece_type piece, enums::color color, sf::Vector2i position) : sf::Sprite() {
        setTexture(tex_pieces[color][piece]);
        pos = position;
        p = piece;
        c = color;
    }

    void updateTexture(){
        setTexture(tex_pieces[c][p]);
    }

    void updatePiece(){
        sf::Vector2u wSize = piece::w->getSize();
        uint32_t smallest = std::min(wSize.x, wSize.y);
        setScale(sf::Vector2f{(float)smallest, (float)smallest} / 60.0f / 8.0f);
        if (wSize.x != smallest) {
            setPosition((sf::Vector2f) (pos * (int) smallest) / 8.f + sf::Vector2f{(float)(wSize.x - wSize.y) / 2.f, 0});
        }else{
            setPosition((sf::Vector2f) (pos * (int) smallest) / 8.f + sf::Vector2f{0, (float)(wSize.y - wSize.x) / 2.f});
        }
    }

    sf::Vector2i pos;
    enums::color c;
};

#endif
