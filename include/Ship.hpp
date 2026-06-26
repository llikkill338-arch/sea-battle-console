// ============================================================================
// Ship.hpp - Корабль
// ============================================================================

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

enum class PartState {
    Intact,
    Damaged
};

struct ShipPart {
    int r, c;
    PartState state;
};

class Ship {
public:
    Ship(int startR, int startC, int size, bool horizontal);

    bool hunches(int r, int c) const;
    bool hitPart(int r, int c);  // marks part as Damaged, returns true if found
    bool isSunk() const;
    int getSize() const { return size; }
    bool isHorizontal() const { return horizontal; }
    const ShipPart& getPart(int idx) const;

    void draw(sf::RenderWindow& window, float offsetX, float offsetY, 
              float cellSize, bool showShips, bool isEnemy) const;

private:
    std::vector<ShipPart> parts;
    int size;
    bool horizontal;
};
