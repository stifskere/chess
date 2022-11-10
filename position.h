#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H
#include "enums.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

template <typename T>
T lerp(T a, T b, float t){
    return (b - a) * t + a;
}

class position : public sf::RectangleShape {
private:
    sf::RenderWindow& w;
    bool possible = false;
    uint32_t fillColor;
    friend int main();
public:
    sf::Vector2i pos;
    explicit position(enums::color color, sf::Vector2i position, sf::RenderWindow& window) :
    sf::RectangleShape((sf::Vector2f)(window.getSize() / 8u)),
    w(window),
    pos(position) {
        fillColor = (uint32_t)color == enums::color::black ? 0x673314ff : 0xf9ac71ff;
        setFillColor(sf::Color(fillColor));
    }

    void shapeUpdate(){
        sf::Vector2u wSize = w.getSize();
        uint32_t smallest = std::min(wSize.x, wSize.y);
        if (possible) setFillColor(sf::Color(lerp<uint8_t>(0xff, (fillColor >> 24 & 0xff), 0.5f), lerp<uint8_t>(0xff, (fillColor >> 16 & 0xff), 0.5f), lerp<uint8_t>(0x00, (fillColor >> 8 & 0xff), 0.5f), lerp<uint8_t>(0xff, fillColor & 0xff, 0.5f)));
        else setFillColor(sf::Color(fillColor));
        setSize(sf::Vector2f{(float)smallest, (float)smallest} / 8.f);
        if (wSize.x != smallest) {
            setPosition((sf::Vector2f) (pos * (int) smallest) / 8.f + sf::Vector2f{(float)(wSize.x - wSize.y) / 2.f, 0});
        }else{
            setPosition((sf::Vector2f) (pos * (int) smallest) / 8.f + sf::Vector2f{0, (float)(wSize.y - wSize.x) / 2.f});
        }
    }
};

#endif