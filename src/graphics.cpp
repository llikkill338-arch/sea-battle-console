// ============================================================================
// graphics.cpp — Реализация графики и UI
// ============================================================================

#include "graphics.h"
#include <iostream>

void setColor(Color text, Color background) {
    SetConsoleTextAttribute(hstdout, text + background * 16);
}

void setCursor(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hstdout, coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 1;
    SetConsoleCursorInfo(hstdout, &info);
}

void drawBox(int x, int y, int w, int h, Color borderColor) {
    setColor(borderColor, black);
    setCursor(x, y);
    std::cout << "+";
    for (int i = 0; i < w; i++) std::cout << "=";
    std::cout << "+";
    for (int i = 0; i < h; i++) {
        setCursor(x, y + 1 + i);
        std::cout << "|";
        setCursor(x + w + 1, y + 1 + i);
        std::cout << "|";
    }
    setCursor(x, y + h + 1);
    std::cout << "+";
    for (int i = 0; i < w; i++) std::cout << "=";
    std::cout << "+";
}

void drawLine(int x, int y, int len, bool horizontal, Color color) {
    setColor(color, black);
    setCursor(x, y);
    if (horizontal) {
        for (int i = 0; i < len; i++) std::cout << "=";
    } else {
        for (int i = 0; i < len; i++) {
            setCursor(x, y + i);
            std::cout << "|";
        }
    }
}

void drawDivider() {
    setColor(lightgray, black);
    setCursor(DIVIDER_X, 0);
    std::cout << "+";
    for (int y = 1; y < SCREEN_HEIGHT - 1; y++) {
        setCursor(DIVIDER_X, y);
        std::cout << "|";
    }
    setCursor(DIVIDER_X, SCREEN_HEIGHT - 1);
    std::cout << "+";
}

static void getCellScreenPos(int y, int x, int offsetX, int offsetY, int& sx, int& sy) {
    sx = offsetX + 3 + x * 3;
    sy = offsetY + 2 + y;
}

static bool isGhostCell(int gy, int gx, int cursorY, int cursorX, int ghostSize, bool ghostDir) {
    if (ghostSize <= 0) return false;
    if (ghostDir) {
        return (gy == cursorY && gx >= cursorX && gx < cursorX + ghostSize);
    } else {
        return (gx == cursorX && gy >= cursorY && gy < cursorY + ghostSize);
    }
}

static void drawFleetInfo(int field[R][R], int offsetX, int offsetY) {
    setColor(white, black);
    setCursor(offsetX + 35, offsetY);
    std::cout << "+==========+";
    setCursor(offsetX + 35, offsetY + 1);
    std::cout << "| Fleet    |";

    int ships[5] = {0, 0, 0, 0, 0};
    bool used[R][R] = {false};

    for (int y = 0; y < R; y++) {
        for (int x = 0; x < R; x++) {
            if (field[y][x] == CELL_SHIP && !used[y][x]) {
                int size = 0;
                int dx = 0, dy = 0;
                if (x + 1 < R && field[y][x+1] == CELL_SHIP) dx = 1;
                else if (y + 1 < R && field[y+1][x] == CELL_SHIP) dy = 1;
                int cx = x, cy = y;
                while (cx < R && cy < R && field[cy][cx] == CELL_SHIP && !used[cy][cx]) {
                    used[cy][cx] = true;
                    size++;
                    cx += dx; cy += dy;
                }
                if (size >= 1 && size <= 4) ships[size]++;
            }
        }
    }

    int row = 2;
    for (int s = 4; s >= 1; s--) {
        setCursor(offsetX + 35, offsetY + row);
        std::cout << "| ";
        if (ships[s] > 0) setColor(lightgreen, black);
        else setColor(darkgray, black);
        std::cout << s << "x" << ships[s] << " ";
        for (int i = 0; i < s; i++) {
            if (ships[s] > 0) std::cout << "[S]";
            else std::cout << "[.]";
        }
        setColor(white, black);
        int printed = 3 + 3 * s;
        while (printed < 10) { std::cout << " "; printed++; }
        std::cout << "|";
        row++;
    }
    setCursor(offsetX + 35, offsetY + row);
    std::cout << "+==========+";
}

void drawCell(int val, bool isCursor, bool showShips, bool isGhost, bool isValid) {
    if (isCursor) {
        setColor(yellow, black);
        std::cout << "[+]";
        return;
    }
    if (isGhost) {
        if (isValid) setColor(green, black);
        else setColor(red, black);
        std::cout << "[S]";
        return;
    }
    switch (val) {
        case CELL_WATER:
            setColor(lightcyan, black);
            std::cout << " ~ ";
            break;
        case CELL_SHIP:
            if (showShips) {
                setColor(lightgreen, black);
                std::cout << "[S]";
            } else {
                setColor(lightcyan, black);
                std::cout << " ~ ";
            }
            break;
        case CELL_MISS:
            setColor(darkgray, black);
            std::cout << " * ";
            break;
        case CELL_HIT:
            setColor(red, black);
            std::cout << "[X]";
            break;
        default:
            setColor(lightcyan, black);
            std::cout << " ~ ";
    }
}

void drawSingleGrid(int field[R][R], int cursorY, int cursorX, bool showShips,
    bool showFleet, int ghostSize, bool ghostDir, bool isValid,
    bool showCrosshair, int offsetX, int offsetY) {

    drawBox(offsetX, offsetY, 32, 11, white);

    setColor(white, black);
    setCursor(offsetX + 3, offsetY + 1);
    std::cout << "A  B  C  D  E  F  G  H  I  J";

    for (int y = 0; y < R; y++) {
        setColor(white, black);
        setCursor(offsetX + 1, offsetY + 2 + y);
        std::cout << y;

        for (int x = 0; x < R; x++) {
            int sx = offsetX + 3 + x * 3;
            int sy = offsetY + 2 + y;
            setCursor(sx, sy);
            bool isCursor = (showCrosshair && y == cursorY && x == cursorX);
            bool isGhost = isGhostCell(y, x, cursorY, cursorX, ghostSize, ghostDir);
            drawCell(field[y][x], isCursor, showShips, isGhost, isValid);
        }
    }

    if (showFleet) {
        drawFleetInfo(field, offsetX, offsetY);
    }
}

void flashHit(int hy, int hx, int offsetX, int offsetY) {
    int sx, sy;
    getCellScreenPos(hy, hx, offsetX, offsetY, sx, sy);

    setColor(yellow, black);
    setCursor(sx, sy);
    std::cout << "[!]";
    playSound(1200, 150);
    Sleep(100);

    setColor(lightred, black);
    setCursor(sx, sy);
    std::cout << "[X]";
    Sleep(100);

    setColor(red, black);
    setCursor(sx, sy);
    std::cout << "[X]";
    playSound(800, 100);
    Sleep(100);
}

void flashMiss(int my, int mx, int offsetX, int offsetY) {
    int sx, sy;
    getCellScreenPos(my, mx, offsetX, offsetY, sx, sy);

    setColor(lightcyan, black);
    setCursor(sx, sy);
    std::cout << " o ";
    Sleep(50);

    setColor(cyan, black);
    setCursor(sx, sy);
    std::cout << " * ";
    Sleep(50);

    setColor(darkgray, black);
    setCursor(sx, sy);
    std::cout << " . ";
    playSound(400, 300);
    Sleep(50);
}

void pulseWater(int offsetX, int offsetY) {
    static bool pulseState = false;
    Color waterColor = pulseState ? lightcyan : cyan;
    pulseState = !pulseState;

    for (int y = 0; y < R; y++) {
        for (int x = 0; x < R; x++) {
            int sx = offsetX + 3 + x * 3;
            int sy = offsetY + 2 + y;
            setCursor(sx, sy);
            setColor(waterColor, black);
            std::cout << " ~ ";
        }
    }
    Sleep(200);
}
