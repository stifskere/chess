#include "eventHandler.h"
#include "position.h"
#include "piece.h"

#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

eventHandler<void(const sf::Event &)> onEvent;

std::mutex globalMutex;

void move(std::vector<position> &positions, std::vector<piece> &pieces, piece p, int ax, int ay, int d = 8){
    for (int i = 0, x = 0, y = 0; i < d; i++, x+=ax, y+=ay) {
        auto it = std::find_if(positions.begin(), positions.end(),
                               [x, y, &p](const position &pos) { return pos.pos == sf::Vector2i{x, y} + p.pos; });
        if (it != positions.end()) {
            auto pc = std::find_if(pieces.begin(), pieces.end(),
                                   [x, y, &p](const piece &piece) { return piece.pos == sf::Vector2i{x, y} + p.pos; });
            if (pc == pieces.end() || pc->pos == p.pos) it->possible = true;
            else {
                it->possible = pc->c != p.c;
                break;
            }
        }
    }
}

bool hasMouseBounds(const sf::Sprite& drawable, const sf::Window& window){
    return drawable.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window));
}

int main() {
    sf::RenderWindow window{{800, 800}, "Chess"};
    window.setFramerateLimit(60);
    sf::Vector2f current_windowSize = (sf::Vector2f)window.getSize();
    piece::w = &window;

    sf::Image img;
    img.loadFromFile("./pieces/chessIcon.png");

    window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());

    tex_pieces.loadPieces();

    sf::Event ev{};

    std::vector<position> positions{};
    std::vector<piece> pieces{};
    enums::color current_color = enums::color::black;
    piece* touchedPiece = nullptr;
    sf::Vector2i savedPosition;
    enums::color current_team = enums::white;

    bool selectPieceMenu = false;
    enums::color selectPieceMenuColor = enums::white;
    piece* pieceToChange = nullptr;

    sf::Sprite sel_queen, sel_horse, sel_tower, sel_bishop;

    for (int i = 0; i < 8; i++) {
        pieces.emplace_back(enums::pawn, enums::white, sf::Vector2i{i, 6});
        pieces.emplace_back(enums::pawn, enums::black, sf::Vector2i{i, 1});
    }

    for (int i = 0; i < 8; i+=7){
        pieces.emplace_back(enums::tower, enums::white,  sf::Vector2i{i, 7});
        pieces.emplace_back(enums::tower, enums::black,  sf::Vector2i{i, 0});
    }

    for (int i = 1; i < 8; i+=5){
        pieces.emplace_back(enums::horse, enums::white,  sf::Vector2i{i, 7});
        pieces.emplace_back(enums::horse, enums::black,  sf::Vector2i{i, 0});
    }

    for (int i = 2; i < 8; i+=3){
        pieces.emplace_back(enums::bishop, enums::white,  sf::Vector2i{i, 7});
        pieces.emplace_back(enums::bishop, enums::black,  sf::Vector2i{i, 0});
    }

    pieces.emplace_back(enums::queen, enums::white, sf::Vector2i{3, 7});
    pieces.emplace_back(enums::queen, enums::black, sf::Vector2i{3, 0});
    pieces.emplace_back(enums::king, enums::white, sf::Vector2i{4, 7});
    pieces.emplace_back(enums::king, enums::black, sf::Vector2i{4, 0});

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

    onEvent += [&window, &current_windowSize, &pieces, &touchedPiece, &positions, &savedPosition, &current_team, &selectPieceMenu, &selectPieceMenuColor, &pieceToChange, &sel_tower, &sel_queen, &sel_horse, &sel_bishop](const sf::Event &event) -> void {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::Resized) current_windowSize = {(float)event.size.width, (float)event.size.height};
        if (event.type == sf::Event::MouseButtonPressed) {
            if (selectPieceMenu) {
                if (hasMouseBounds(sel_tower, window)) {
                    selectPieceMenu = false;
                    pieceToChange->p = enums::tower;
                    pieceToChange->updateTexture();
                    pieceToChange = nullptr;
                } else if (hasMouseBounds(sel_bishop, window)) {
                    selectPieceMenu = false;
                    pieceToChange->p = enums::bishop;
                    pieceToChange->updateTexture();
                    pieceToChange = nullptr;
                } else if (hasMouseBounds(sel_horse, window)) {
                    selectPieceMenu = false;
                    pieceToChange->p = enums::horse;
                    pieceToChange->updateTexture();
                    pieceToChange = nullptr;
                } else if (hasMouseBounds(sel_queen, window)) {
                    selectPieceMenu = false;
                    pieceToChange->p = enums::queen;
                    pieceToChange->updateTexture();
                    pieceToChange = nullptr;
                }
                return;
            }
            for (piece& p : pieces) {
                p.updatePiece();
                if (hasMouseBounds(p, window)) {
                    if (p.c != current_team) return;
                    touchedPiece = &p;
                    switch (p.p){
                        case enums::bishop:
                            move(positions, pieces, p, 1, 1);
                            move(positions, pieces, p, -1, 1);
                            move(positions, pieces, p, 1, -1);
                            move(positions, pieces, p, -1, -1);
                            break;
                        case enums::horse:
                            for (position &pos : positions) {
                                sf::Vector2i diff = pos.pos - p.pos;
                                if (pos.pos == p.pos) pos.possible = true;
                                if (std::abs(diff.x) + std::abs(diff.y) != 3 || pos.pos.x == p.pos.x || pos.pos.y == p.pos.y) continue;
                                sf::Vector2i mv = pos.pos;
                                pos.possible = std::find_if(pieces.begin(), pieces.end(), [&mv, &p](const piece &pc) { return pc.pos == mv && p.c == pc.c; }) == pieces.end();
                            }
                            break;
                        case enums::king:
                            for (position &pos : positions) {
                                sf::Vector2i diff = pos.pos - p.pos;
                                if (diff.y > 1 || diff.x > 1 || diff.x < -1 || diff.y < -1) continue;
                                sf::Vector2i mv = pos.pos;
                                pos.possible = std::find_if(pieces.begin(), pieces.end(), [&mv, &p](const piece &pc) { return pc.pos == mv && p.c == pc.c; }) == pieces.end() || pos.pos == p.pos;
                            }
                            break;
                        case enums::pawn:
                            if (std::find_if(pieces.begin(), pieces.end(), [&p](const piece& piece) -> bool{
                                return p.pos + sf::Vector2i{0, p.c == enums::white ? -1 : 1} == piece.pos;
                            }) == pieces.end()) {
                                move(positions, pieces, p, 0, p.c == enums::white ? -1 : 1, p.hasMoved ? 2 : 3);
                            }else{
                                move(positions, pieces, p, 0, 1, 1);
                            }

                            if (std::find_if(pieces.begin(), pieces.end(), [&p](const piece& piece) -> bool{
                                return p.pos + sf::Vector2i{1, p.c == enums::white ? -1 : 1} == piece.pos;
                            }) != pieces.end()) {
                                move(positions, pieces, p, 1, p.c == enums::white ? -1 : 1, 2);
                            }

                            if (std::find_if(pieces.begin(), pieces.end(), [&p](const piece& piece) -> bool{
                                return p.pos + sf::Vector2i{-1, p.c == enums::white ? -1 : 1} == piece.pos;
                            }) != pieces.end()) {
                                move(positions, pieces, p, -1, p.c == enums::white ? -1 : 1, 2);
                            }
                            break;
                        case enums::queen:
                            move(positions, pieces, p, 1, 1);
                            move(positions, pieces, p, -1, 1);
                            move(positions, pieces, p, 1, -1);
                            move(positions, pieces, p, -1, -1);
                            move(positions, pieces, p, 1, 0);
                            move(positions, pieces, p, -1, 0);
                            move(positions, pieces, p, 0, 1);
                            move(positions, pieces, p, 0, -1);
                            break;
                        case enums::tower:
                            move(positions, pieces, p, 1, 0);
                            move(positions, pieces, p, -1, 0);
                            move(positions, pieces, p, 0, 1);
                            move(positions, pieces, p, 0, -1);
                            break;
                    }
                    std::find_if(positions.begin(), positions.end(), [&p](const position &pos){return pos.pos == p.pos;})->origin = true;
                    savedPosition = p.pos;
                    break;
                }
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            for (position& pos : positions) {
                pos.possible = false;
                pos.origin = false;
            }
            if (!touchedPiece) return;
            if (touchedPiece->pos != savedPosition) {
                touchedPiece->hasMoved = true;
                enums::invert_color(current_team);
            }
            if (touchedPiece->p == enums::pawn && touchedPiece->pos.y == (touchedPiece->c == enums::black ? 7 : 0)) {
                selectPieceMenu = true;
                selectPieceMenuColor = touchedPiece->c;
                pieceToChange = touchedPiece;
            }
            auto commonPiece = std::find_if(pieces.begin(), pieces.end(), [&touchedPiece](const piece& p) -> bool {return p.pos == touchedPiece->pos && p.c != touchedPiece->c;});
            if (commonPiece != pieces.end()){
                pieces.erase(commonPiece);
            }
            touchedPiece = nullptr;
        }
        if (event.type == sf::Event::MouseMoved) {
            if (!touchedPiece) return;
            for (position& pos : positions){
                pos.shapeUpdate();
                if (pos.possible && pos.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)))
                    touchedPiece->pos = pos.pos;
            }
        }
    };

    std::thread draw_thread{[&current_windowSize, &window, &positions, &pieces, &selectPieceMenu, &selectPieceMenuColor, &sel_bishop, &sel_horse, &sel_queen, &sel_tower](){
        while (true) {
            globalMutex.lock();
            if (!window.isOpen()) return;
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

            if (selectPieceMenu){
                sf::RectangleShape obscure{current_windowSize};
                obscure.setFillColor(sf::Color(0x0000003F));
                window.draw(obscure);

                sf::RectangleShape shape{{current_windowSize.x - 8, current_windowSize.y / 4 - 4}};
                shape.setFillColor(sf::Color(0x422601ff));
                shape.setOutlineThickness(4);
                shape.setOutlineColor(sf::Color::Black);
                shape.setPosition(current_windowSize - sf::Vector2f{current_windowSize.x - 4, current_windowSize.y / 4});
                window.draw(shape);

                float min = std::min(current_windowSize.x, current_windowSize.y) / 4.25f;
                float margin_line = current_windowSize.x / 100.0f;
                float horizontal_margin = (current_windowSize.x - min * 4 - margin_line * 3) / 2.0f;

                sel_tower.setTexture(tex_pieces[selectPieceMenuColor][enums::tower]);
                sel_tower.setScale(sf::Vector2f{min, min} / 60.0f);
                sel_tower.setPosition(sf::Vector2f{horizontal_margin, current_windowSize.y - current_windowSize.y / 4});
                window.draw(sel_tower);

                sel_horse.setTexture(tex_pieces[selectPieceMenuColor][enums::horse]);
                sel_horse.setScale(sf::Vector2f{min, min} / 60.0f);
                sel_horse.setPosition(sf::Vector2f{min + margin_line + horizontal_margin, current_windowSize.y - current_windowSize.y / 4});
                window.draw(sel_horse);

                sel_bishop.setTexture(tex_pieces[selectPieceMenuColor][enums::bishop]);
                sel_bishop.setScale(sf::Vector2f{min, min} / 60.0f);
                sel_bishop.setPosition(sf::Vector2f{min * 2 + margin_line * 2 + horizontal_margin, current_windowSize.y - current_windowSize.y / 4});
                window.draw(sel_bishop);

                sel_queen.setTexture(tex_pieces[selectPieceMenuColor][enums::queen]);
                sel_queen.setScale(sf::Vector2f{min, min} / 60.0f);
                sel_queen.setPosition(sf::Vector2f{min * 3 + margin_line * 3 + horizontal_margin, current_windowSize.y - current_windowSize.y / 4});
                window.draw(sel_queen);
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