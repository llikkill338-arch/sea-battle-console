// ============================================================================
// game_logic.cpp — Реализация логики игры
// ============================================================================

#include "game_logic.h"
#include "graphics.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

void clearField(int grid[R][R]) {
    for (int y = 0; y < R; y++) {
        for (int x = 0; x < R; x++) {
            grid[y][x] = CELL_WATER;
        }
    }
}

bool canPlace(int grid[R][R], int y, int x, int size, bool horizontal) {
    if (horizontal) {
        if (x < 0 || x + size > R || y < 0 || y >= R) return false;
    } else {
        if (y < 0 || y + size > R || x < 0 || x >= R) return false;
    }

    for (int dy = -1; dy <= (horizontal ? 1 : size); dy++) {
        for (int dx = -1; dx <= (horizontal ? size : 1); dx++) {
            int cy = y + dy;
            int cx = x + dx;
            if (cy >= 0 && cy < R && cx >= 0 && cx < R) {
                if (dy >= 0 && dy < (horizontal ? 1 : size) &&
                    dx >= 0 && dx < (horizontal ? size : 1)) {
                    if (grid[cy][cx] != CELL_WATER) return false;
                } else {
                    if (grid[cy][cx] == CELL_SHIP) return false;
                }
            }
        }
    }
    return true;
}

void placeShip(int grid[R][R], int y, int x, int size, bool horizontal) {
    for (int i = 0; i < size; i++) {
        if (horizontal) {
            grid[y][x + i] = CELL_SHIP;
        } else {
            grid[y + i][x] = CELL_SHIP;
        }
    }
}

bool checkAlive(int grid[R][R]) {
    for (int y = 0; y < R; y++) {
        for (int x = 0; x < R; x++) {
            if (grid[y][x] == CELL_SHIP) return true;
        }
    }
    return false;
}

void autoPlace(int grid[R][R]) {
    clearField(grid);
    for (int i = 0; i < FLEET_SIZE; i++) {
        int size = FLEET[i];
        bool placed = false;
        int attempts = 0;
        while (!placed && attempts < 1000) {
            int y = rand() % R;
            int x = rand() % R;
            bool horizontal = (rand() % 2) == 0;
            if (canPlace(grid, y, x, size, horizontal)) {
                placeShip(grid, y, x, size, horizontal);
                placed = true;
            }
            attempts++;
        }
    }
}

void stavlyusam(int field[R][R], const std::string& playerName) {
    clearField(field);
    int fleetIdx = 0;
    int cursorY = 4, cursorX = 4;
    bool horizontal = true;

    while (fleetIdx < FLEET_SIZE) {
        int shipSize = FLEET[fleetIdx];
        bool valid = canPlace(field, cursorY, cursorX, shipSize, horizontal);

        system("cls");
        setColor(yellow, black);
        setCursor(2, 0);
        std::cout << "=== \xD0\xC0\xD1\xD1\xD2\xC0\xCD\xCE\xC2\xCA\xC0 \xCA\xCE\xD0\xC0\xC1\xCB\xC5\xC9 ===  " << playerName;
        setColor(white, black);
        setCursor(2, 1);
        std::cout << "\xCA\xEE\xF0\xE0\xE1\xEB\xFC: " << shipSize << "-\xEF\xE0\xEB\xF3\xE1\xED\xFB\xE9 (" << (fleetIdx + 1) << "/" << FLEET_SIZE << ")";
        setCursor(2, 23);
        std::cout << "\xD1\xF2\xF0\xE5\xEB\xEA\xE8 - \xE4\xE2\xE8\xE6\xE5\xED\xE8\xE5 | \xCF\xD0\xCE\xC1\xC5\xCB - \xEF\xEE\xE2\xEE\xF0\xEE\xF2 | ENTER - \xF3\xF1\xF2\xE0\xED\xEE\xE2\xE8\xF2\xFC | ESC - \xE2\xFB\xF5\xEE\xE4";

        drawSingleGrid(field, cursorY, cursorX, true, true, shipSize, horizontal, valid, true, 2, 3);

        int key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: if (cursorY > 0) cursorY--; break;
                case 80: if (cursorY < R - 1) cursorY++; break;
                case 75: if (cursorX > 0) cursorX--; break;
                case 77: if (cursorX < R - 1) cursorX++; break;
            }
        } else if (key == 32) {
            horizontal = !horizontal;
            playSound(600, 50);
        } else if (key == 13) {
            if (valid) {
                placeShip(field, cursorY, cursorX, shipSize, horizontal);
                playSound(800, 80);
                playSound(1000, 80);
                fleetIdx++;
            } else {
                playSound(200, 400);
                setColor(lightred, black);
                setCursor(2, 22);
                std::cout << "\xCD\xE5\xE2\xEE\xE7\xEC\xEE\xE6\xED\xEE \xF0\xE0\xE7\xEC\xE5\xF1\xF2\xE8\xF2\xFC \xEA\xEE\xF0\xE0\xE1\xEB\xFC \xE7\xE4\xE5\xF1\xFC!";
                Sleep(800);
            }
        } else if (key == 27) {
            return;
        }
    }

    system("cls");
    setColor(lightgreen, black);
    setCursor(2, 0);
    std::cout << "=== \xC2\xD1\xC5 \xCA\xCE\xD0\xC0\xC1\xCB\xC8 \xD0\xC0\xD1\xD1\xD2\xC0\xC2\xCB\xC5\xCD\xDB ===  " << playerName;
    drawSingleGrid(field, -1, -1, true, true, 0, true, true, false, 2, 3);
    setColor(white, black);
    setCursor(2, 23);
    std::cout << "\xCD\xE0\xE6\xEC\xE8\xF2\xE5 \xEB\xFE\xE1\xF3\xFE \xEA\xEB\xE0\xE2\xE8\xF8\xF3 \xE4\xEB\xFF \xEF\xF0\xEE\xE4\xEE\xEB\xE6\xE5\xED\xE8\xFF...";
    _getch();
}
