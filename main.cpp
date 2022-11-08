#include <SFML/Graphics.hpp>

#include "eventHandler.h"
#include "position.h"

eventHandler<void(const sf::Event &)> onEvent;

int main() {
    sf::RenderWindow window{{800, 600}, "Chess"};
    window.setFramerateLimit(60);
    sf::Vector2f current_windowSize = (sf::Vector2f)window.getSize();

    sf::RectangleShape background{current_windowSize};
    background.setFillColor(sf::Color(0x422601ff));

    sf::Event ev{};

    std::vector<std::vector<position>> positions{};
    enums::color current_color = enums::color::black;
    sf::Vector2f current_position{0, 0};

    for (int i = 0; i < 8; i++) {
        std::vector<position> p{};
        for (int l = 0; l < 8; l++) {
            p.emplace_back(
                current_color,
                current_position,
                window
            );

            enums::invert_color(current_color);
            current_position.x += (float)current_windowSize.x / 8;
        }
        positions.emplace_back(p);
        enums::invert_color(current_color);
        current_position.x = 0;
        current_position.y += (float)current_windowSize.y / 8;
    }

    onEvent += [&window](const sf::Event &event) -> void {
        if (event.type == sf::Event::Closed) window.close();
    };

    while (window.isOpen()){
        while (window.pollEvent(ev)){
            onEvent(ev);
        }
        window.clear();

        window.draw(background);

        for (const std::vector<position>& y : positions) for (const position& x : y) {
            window.draw(x);
        }

        window.display();
    }
}
