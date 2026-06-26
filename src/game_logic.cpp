// ============================================================================
// game_logic.cpp - Логика игры и расстановка с подсказками
// ============================================================================

#include "game_logic.h"
#include "graphics.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

vector<int> fleet = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
int currentShipIndex = 0;

void clearField(int grid[R][R]) {
    for (int i = 0; i < R; i++)
        for (int j = 0; j < R; j++)
            grid[i][j] = CELL_WATER;
}

bool canPlace(int grid[R][R], int y, int x, int size, bool horizontal) {
    if (horizontal) { if (x + size > R) return false; }
    else            { if (y + size > R) return false; }

    int minY = max(0, y - 1);
    int maxY = min(R - 1, (horizontal ? y : y + size - 1) + 1);
    int minX = max(0, x - 1);
    int maxX = min(R - 1, (horizontal ? x + size - 1 : x) + 1);

    for (int yy = minY; yy <= maxY; yy++)
        for (int xx = minX; xx <= maxX; xx++)
            if (grid[yy][xx] != CELL_WATER) return false;
    return true;
}

void placeShip(int grid[R][R], int y, int x, int size, bool horizontal) {
    if (horizontal) for (int i = 0; i < size; i++) grid[y][x + i] = CELL_SHIP;
    else            for (int i = 0; i < size; i++) grid[y + i][x] = CELL_SHIP;
}

bool checkAlive(int grid[R][R]) {
    for (int i = 0; i < R; i++)
        for (int j = 0; j < R; j++)
            if (grid[i][j] == CELL_SHIP) return true;
    return false;
}

void autoPlace(int grid[R][R]) {
    clearField(grid);
    for (int size : fleet) {
        bool placed = false;
        while (!placed) {
            int vy = rand() % R, vx = rand() % R;
            bool horizontal = rand() % 2;
            if (canPlace(grid, vy, vx, size, horizontal)) {
                placeShip(grid, vy, vx, size, horizontal);
                placed = true;
            }
        }
    }
}

// --- Ручная расстановка С ПОДСКАЗКАМИ ---

void stavlyusam(int field[R][R], const string& playerName) {
    clearField(field);
    bool horizontal = true;
    currentShipIndex = 0;
    int curX = 0, curY = 0;

    while (currentShipIndex < (int)fleet.size()) {
        int currentSize = fleet[currentShipIndex];
        bool valid = canPlace(field, curY, curX, currentSize, horizontal);

        system("cls");

        // Рамка и поле
        drawBox(0, 0, 38, 14, cyan);
        drawSingleGrid(field, curY, curX, true, true, currentSize, horizontal, valid, true, 1, 1);

        // Панель подсказок справа
        setCursor(42, 1);
        setColor(yellow, black);
        cout << "=== РАССТАНОВКА ===";
        setCursor(42, 3);
        setColor(white, black);
        cout << "Игрок: " << playerName;
        setCursor(42, 5);
        setColor(lightcyan, black);
        cout << "Корабль: " << currentSize << "-палубный";
        setCursor(42, 7);
        if (horizontal) cout << ">>> ГОРИЗОНТАЛЬНО";
        else            cout << "vvv ВЕРТИКАЛЬНО";

        // Статус валидности
        setCursor(42, 9);
        if (valid) {
            setColor(lightgreen, black);
            cout << "[OK] Можно ставить";
        } else {
            setColor(lightred, black);
            cout << "[X]  Место занято!";
        }

        // Управление
        setCursor(42, 11);
        setColor(darkgray, black);
        cout << "Управление:";
        setCursor(42, 12);
        cout << "Стрелки - движение";
        setCursor(42, 13);
        cout << "ПРОБЕЛ - поворот";
        setCursor(42, 14);
        cout << "ENTER - поставить";
        setCursor(42, 15);
        cout << "ESC - выход";

        // Оставшиеся корабли
        setCursor(42, 17);
        setColor(yellow, black);
        cout << "Осталось расставить:";
        for (int i = currentShipIndex; i < (int)fleet.size(); i++) {
            setCursor(42, 18 + (i - currentShipIndex));
            setColor(lightblue, black);
            cout << "  [";
            for (int k = 0; k < fleet[i]; k++) cout << "=";
            cout << "]";
        }
        setColor(white, black);

        // Ввод
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72 && curY > 0) curY--;
            if (key == 80 && curY < R - 1) curY++;
            if (key == 75 && curX > 0) curX--;
            if (key == 77 && curX < R - 1) curX++;
        }
        else if (key == 32) {
            horizontal = !horizontal;
            if (horizontal) { if (curX + currentSize > R) curX = R - currentSize; }
            else            { if (curY + currentSize > R) curY = R - currentSize; }
        }
        else if (key == 13 && valid) {
            placeShip(field, curY, curX, currentSize, horizontal);
            currentShipIndex++;
            curX = 0; curY = 0;
        }
        else if (key == 27) return;
    }
}
