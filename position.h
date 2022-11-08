#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H
#include "enums.h"

class position : public sf::RectangleShape {
private:
    sf::RenderWindow& w;

public:
    explicit position(enums::color color, sf::Vector2f position, sf::RenderWindow& window) :
    sf::RectangleShape({(float)window.getSize().x / 8, (float)window.getSize().y / 8}),
    w(window) {
        setFillColor(sf::Color((uint32_t)color == enums::color::black ? 0x673314ff : 0xf9ac71ff));
        setPosition(position);
    }
};

#endif