// ============================================================================
// graphics.cpp - Графика и UI (с псевдографикой)
// ============================================================================

#include "graphics.h"
#include <iostream>

using namespace std;

void setColor(Color text, Color background) {
    SetConsoleTextAttribute(hstdout, (WORD)((background << 4) | text));
}

void setCursor(int x, int y) {
    COORD coord = { (short)x, (short)y };
    SetConsoleCursorPosition(hstdout, coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO info = { 1, 0 };
    SetConsoleCursorInfo(hstdout, &info);
}

// --- Рамки с настоящей псевдографикой ---

void drawBox(int x, int y, int w, int h, Color borderColor) {
    setColor(borderColor, black);
    setCursor(x, y);
    cout << char(201);
    for (int i = 0; i < w - 2; i++) cout << char(205);
    cout << char(187);
    for (int i = 1; i < h - 1; i++) {
        setCursor(x, y + i);
        cout << char(186);
        setCursor(x + w - 1, y + i);
        cout << char(186);
    }
    setCursor(x, y + h - 1);
    cout << char(200);
    for (int i = 0; i < w - 2; i++) cout << char(205);
    cout << char(188);
    setColor(white, black);
}

void drawLine(int x, int y, int len, bool horizontal, Color color) {
    setColor(color, black);
    setCursor(x, y);
    if (horizontal) {
        for (int i = 0; i < len; i++) cout << char(196);
    } else {
        for (int i = 0; i < len; i++) {
            setCursor(x, y + i);
            cout << char(179);
        }
    }
    setColor(white, black);
}

void drawDivider() {
    setColor(yellow, black);
    for (int i = 0; i < 25; i++) {
        setCursor(DIVIDER_X, i);
        if (i == 0)       cout << char(203);
        else if (i == 24) cout << char(202);
        else if (i == 12) cout << char(206);
        else              cout << char(186);
    }
    setColor(white, black);
}

// --- Отрисовка клеток ---

void drawCell(int val, bool isCursor, bool showShips, bool isGhost, bool isValid) {
    if (isGhost) {
        if (isValid) setColor(green, black);
        else setColor(red, black);
        cout << "[ ]";
        setColor(white, black);
    }
    else if (isCursor) {
        setColor(yellow, black);
        cout << "[";
        setColor(red, black);
        cout << "+";
        setColor(yellow, black);
        cout << "]";
        setColor(white, black);
    }
    else if (val == CELL_SHIP) {
        if (showShips) {
            setColor(lightgreen, black);
            cout << " S ";
        } else {
            setColor(cyan, black);
            cout << " ~ ";
        }
        setColor(white, black);
    }
    else if (val == CELL_HIT) {
        setColor(lightred, black);
        cout << " X ";
        setColor(white, black);
    }
    else if (val == CELL_MISS) {
        setColor(darkgray, black);
        cout << " * ";
        setColor(white, black);
    }
    else {
        setColor(cyan, black);
        cout << " ~ ";
        setColor(white, black);
    }
}

// --- Вспомогательные функции ---

static bool isGhostCell(int gy, int gx, int cursorY, int cursorX, int ghostSize, bool ghostDir) {
    if (ghostSize <= 0) return false;
    if (ghostDir) return (gy == cursorY && gx >= cursorX && gx < cursorX + ghostSize);
    else          return (gx == cursorX && gy >= cursorY && gy < cursorY + ghostSize);
}

// --- Отрисовка поля 10x10 ---

void drawSingleGrid(int field[R][R], int cursorY, int cursorX, bool showShips,
    bool showFleet, int ghostSize, bool ghostDir, bool isValid,
    bool showCrosshair, int offsetX, int offsetY) {

    // Координаты сверху (1-10)
    setCursor(offsetX + 3, offsetY);
    setColor(yellow, black);
    for (int j = 1; j <= R; j++) {
        if (j < 10) cout << " " << j << " ";
        else cout << j << " ";
    }
    setColor(white, black);

    // Строки поля
    for (int i = 0; i < R; i++) {
        setCursor(offsetX, offsetY + 1 + i);
        setColor(yellow, black);
        if (i + 1 < 10) cout << " " << i + 1 << " ";
        else cout << i + 1 << " ";
        setColor(white, black);

        for (int j = 0; j < R; j++) {
            bool isCursor = (i == cursorY && j == cursorX && showCrosshair);
            bool isGhost = showFleet && isGhostCell(i, j, cursorY, cursorX, ghostSize, ghostDir);
            drawCell(field[i][j], isCursor, showShips, isGhost, isValid);
        }
    }
}

// --- Анимации ---

void flashHit(int hy, int hx, int offsetX, int offsetY) {
    for (int i = 0; i < 6; i++) {
        setCursor(offsetX + hx * 3 + 3, offsetY + 1 + hy);
        if (i % 2 == 0) {
            setColor(yellow, black);
            cout << "X";
            setColor(white, black);
            cout << " ";
            playSound(1000 + i * 100, 50);
        } else {
            setColor(lightred, black);
            cout << "X";
            setColor(white, black);
            cout << " ";
        }
        Sleep(100);
    }
}

void flashMiss(int my, int mx, int offsetX, int offsetY) {
    setCursor(offsetX + mx * 3 + 3, offsetY + 1 + my);
    setColor(cyan, black);
    cout << " o ";
    Sleep(150);
    setCursor(offsetX + mx * 3 + 3, offsetY + 1 + my);
    setColor(darkgray, black);
    cout << " * ";
    playSound(400, 200);
    Sleep(100);
}
