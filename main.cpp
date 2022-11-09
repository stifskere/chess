#include "eventHandler.h"
#include "position.h"
#include "piece.h"

#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

eventHandler<void(const sf::Event &)> onEvent;

std::mutex globalMutex;

int main() {
    sf::RenderWindow window{{800, 800}, "Chess"};
    window.setFramerateLimit(60);
    sf::Vector2f current_windowSize = (sf::Vector2f)window.getSize();

    tex_pieces.loadPieces();

    sf::Event ev{};

    std::vector<position> positions{};
    std::vector<piece> pieces{};
    enums::color current_color = enums::color::black;

    for (int i = 0; i < 8; i++) {
        pieces.emplace_back(enums::pawn, enums::white, window, sf::Vector2i{i, 6});
        pieces.emplace_back(enums::pawn, enums::black, window, sf::Vector2i{i, 1});
    }

    for (int i = 0; i < 8; i+=7){
        pieces.emplace_back(enums::tower, enums::white, window, sf::Vector2i{i, 7});
        pieces.emplace_back(enums::tower, enums::black, window, sf::Vector2i{i, 0});
    }

    for (int i = 1; i < 8; i+=5){
        pieces.emplace_back(enums::horse, enums::white, window, sf::Vector2i{i, 7});
        pieces.emplace_back(enums::horse, enums::black, window, sf::Vector2i{i, 0});
    }

    for (int i = 2; i < 8; i+=3){
        pieces.emplace_back(enums::bishop, enums::white, window, sf::Vector2i{i, 7});
        pieces.emplace_back(enums::bishop, enums::black, window, sf::Vector2i{i, 0});
    }

    pieces.emplace_back(enums::queen, enums::white, window, sf::Vector2i{3, 7});
    pieces.emplace_back(enums::queen, enums::black, window, sf::Vector2i{3, 0});
    pieces.emplace_back(enums::king, enums::white, window, sf::Vector2i{4, 7});
    pieces.emplace_back(enums::king, enums::black, window, sf::Vector2i{4, 0});

    for (int i = 0; i < 8; i++) {
        for (int l = 0; l < 8; l++) {
            positions.emplace_back(
                current_color,
                sf::Vector2i{l, i},
                window
            );

            enums::invert_color(current_color);
        }
        enums::invert_color(current_color);
    }

    onEvent += [&window, &current_windowSize](const sf::Event &event) -> void {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::Resized) current_windowSize = {(float)event.size.width, (float)event.size.height};
    };

    std::thread draw_thread{[&current_windowSize, &window, &positions, &pieces](){
        while (window.isOpen()) {
            globalMutex.lock();
            window.setActive(true);

            window.clear(sf::Color(0x422601ff));

            for (position x : positions) {
                x.shapeUpdate();
                window.draw(x);
            }

            for (piece p : pieces){
                p.updatePiece();
                window.draw(p);
            }

            window.setView(sf::View(sf::FloatRect{{0, 0}, {current_windowSize}}));
            window.display();
            window.setActive(false);
            globalMutex.unlock();
        }
    }};

    draw_thread.detach();

    window.setActive(false);

    while (window.isOpen())
        while (window.pollEvent(ev))
            onEvent(ev);
}