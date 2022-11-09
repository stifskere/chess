#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H
#include "enums.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class position : public sf::RectangleShape {
private:
    sf::RenderWindow& w;
    sf::Vector2i pos;

public:
    explicit position(enums::color color, sf::Vector2i position, sf::RenderWindow& window) :
    sf::RectangleShape((sf::Vector2f)(window.getSize() / 8u)),
    w(window),
    pos(position) {
        setFillColor(sf::Color((uint32_t)color == enums::color::black ? 0x673314ff : 0xf9ac71ff));
    }

    void shapeUpdate(){
        sf::Vector2u wSize = w.getSize();
        uint32_t smallest = std::min(wSize.x, wSize.y);
        setSize(sf::Vector2f{(float)smallest, (float)smallest} / 8.f);
        if (wSize.x != smallest) {
            setPosition((sf::Vector2f) (pos * (int) smallest) / 8.f + sf::Vector2f{(float)(wSize.x - wSize.y) / 2.f, 0});
        }else{
            setPosition((sf::Vector2f) (pos * (int) smallest) / 8.f + sf::Vector2f{0, (float)(wSize.y - wSize.x) / 2.f});
        }
    }
};

#endif