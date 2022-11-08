#include <iostream>
#include "eventHandler.h"
#include <SFML/Graphics.hpp>

#include "position.h"
#include "piece.h"

eventHandler<void(const sf::Event &)> onEvent;

int main() {

    sf::RenderWindow window{{800, 600}, "Chess"};
    sf::Event ev{};

    onEvent += [&window](const sf::Event &e){if (e.type == sf::Event::Closed) window.close();};

    while (window.isOpen()){
        while (window.pollEvent(ev)){
            onEvent(ev);
        }

    }
}
