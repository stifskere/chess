#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H
#include "enums.h"

class position : sf::RectangleShape {
private:
    sf::RenderWindow& w;

public:
    explicit position(color color, sf::Vector2f position, sf::RenderWindow& window) :
    sf::RectangleShape({(float)window.getSize().x / 64, (float)window.getSize().y / 64}),
    w(window) {
        setFillColor(sf::Color(color == color::b ? 0x673314 : 0xa07c5e));
        setPosition(position);
    }

    void size_update(){
        setSize({(float)w.getSize().x / 64, (float)w.getSize().y / 64});
    }
};

#endif