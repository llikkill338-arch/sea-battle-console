// ============================================================================
// Cell.cpp - v7.0 PIRATE - Wooden deck planks
// ============================================================================

#include "Cell.hpp"
#include "Constants.hpp"

using namespace Colors;

Cell::Cell() : state(CellState::Empty), hover(false) {}

CellState Cell::getState() const { return state; }
void Cell::setState(CellState s) { state = s; }
void Cell::setHover(bool h) { hover = h; }
bool Cell::isHovered() const { return hover; }

void Cell::draw(sf::RenderWindow& window, float x, float y, float size,
                bool showShip, bool isCursor) {

    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(x, y);

    sf::Color fillColor;

    switch (state) {
        case CellState::Empty:
            // Дощатый настил палубы - шахматный узор
            fillColor = DECK;
            break;
        case CellState::Ship:
            fillColor = showShip ? SHIP : DECK;
            break;
        case CellState::Hit:
            fillColor = HIT;
            break;
        case CellState::Miss:
            fillColor = MISS;
            break;
    }

    if (isCursor) {
        fillColor = CURSOR;
    }

    shape.setFillColor(fillColor);

    // Деревянная рамка между досками
    sf::Color outlineColor = isCursor ? sf::Color(255, 200, 100) : GRID_LINE;
    float outlineThickness = isCursor ? 3.0f : 1.0f;
    shape.setOutlineColor(outlineColor);
    shape.setOutlineThickness(outlineThickness);

    window.draw(shape);

    // Шахматный узор доски - лёгкие линии для текстуры дерева
    if (state == CellState::Empty || (state == CellState::Ship && !showShip)) {
        sf::RectangleShape grain(sf::Vector2f(size * 0.6f, 1));
        grain.setFillColor(DECK_DARK);
        grain.setPosition(x + size * 0.2f, y + size * 0.3f);
        window.draw(grain);
        grain.setPosition(x + size * 0.15f, y + size * 0.7f);
        window.draw(grain);
    }

    // Крест попадания - старая кость
    if (state == CellState::Hit) {
        sf::RectangleShape line1(sf::Vector2f(size * 0.55f, 3));
        line1.setOrigin(line1.getSize() / 2.f);
        line1.setPosition(x + size / 2, y + size / 2);
        line1.setRotation(45);
        line1.setFillColor(HIT_CROSS);

        sf::RectangleShape line2(sf::Vector2f(size * 0.55f, 3));
        line2.setOrigin(line2.getSize() / 2.f);
        line2.setPosition(x + size / 2, y + size / 2);
        line2.setRotation(-45);
        line2.setFillColor(HIT_CROSS);

        window.draw(line1);
        window.draw(line2);
    }
    // Промах - старая пуля (круг)
    else if (state == CellState::Miss) {
        sf::CircleShape circle;
        circle.setRadius(size * 0.12f);
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setPosition(x + size / 2, y + size / 2);
        circle.setFillColor(MISS_DOT);
        window.draw(circle);
    }
}
