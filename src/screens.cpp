// ============================================================================
// screens.cpp — Реализация экранов и игровых режимов
// ============================================================================

#include "screens.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

// --- Вспомогательные функции ---

/** Центрированный вывод текста */
static void printCentered(const std::string& text, int y, Color color) {
    int x = (SCREEN_WIDTH - (int)text.length()) / 2;
    if (x < 0) x = 0;
    setCursor(x, y);
    setColor(color, black);
    std::cout << text;
}

/** Стирает строку пробелами */
static void clearRow(int y) {
    setCursor(0, y);
    setColor(black, black);
    for (int i = 0; i < SCREEN_WIDTH; i++) std::cout << " ";
}

/** Проверка, все ли корабли уничтожены (нет CELL_SHIP) */
static bool allShipsDestroyed(int field[R][R]) {
    return !checkAlive(field);
}

/** Отрисовка поля боя (туман войны) */
static void drawBattleField(int field[R][R], int fog[R][R], int cursorY, int cursorX,
    bool showShips, bool showCrosshair, int offsetX, int offsetY) {
    int display[R][R];
    for (int y = 0; y < R; y++) {
        for (int x = 0; x < R; x++) {
            if (fog[y][x] == CELL_MISS || fog[y][x] == CELL_HIT) {
                display[y][x] = fog[y][x];
            } else if (showShips && field[y][x] == CELL_SHIP) {
                display[y][x] = CELL_SHIP;
            } else {
                display[y][x] = CELL_WATER;
            }
        }
    }
    drawSingleGrid(display, cursorY, cursorX, true, false, 0, true, true, showCrosshair, offsetX, offsetY);
}

// --- Заставка ---

void showLogo() {
    system("cls");

    const char* logo[] = {
        "     __  __  ____  ____  ____  _  _  __   __ _    ____  _  _    ",
        "    |  \\/  ||  _ \\|  _ \\|  _ \\| || ||  | |  | ||  | |  _ \\| || |   ",
        "    | |\\/| || |_) | |_) | |_) | || ||  |_|  | ||  | | | | || || |_  ",
        "    | |  | ||  _ <|  _ <|  _ <| || ||  _   _  | ||  | | |_| ||__   _| ",
        "    |_|  |_||_| \\ \\|_| \\ \\|_| \\ \\|_||_||_| |_| |_||____/|____/   |_|   "
    };

    drawBox(8, 2, 52, 7, lightcyan);
    setColor(lightcyan, black);
    for (int i = 0; i < 5; i++) {
        setCursor(10, 4 + i);
        std::cout << logo[i];
    }

    setColor(yellow, black);
    setCursor(20, 10);
    std::cout << "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB";
    setCursor(20, 11);
    std::cout << "\xBA     \xCA \xCF \xCE \xD3 \xCF \xCB \xDC \xCA   \xC1 \xCF \xCA       \xBA";
    setCursor(20, 12);
    std::cout << "\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC";

    setColor(darkgray, black);
    setCursor(18, 16);
    std::cout << "\xC7\xE0\xE3\xF0\xE7\xEA\xE0 \xF1\xE8\xF1\xF2\xE5\xEC\xFB...";

    drawBox(18, 18, 40, 1, green);
    setColor(lightgreen, black);
    for (int i = 0; i < 40; i++) {
        setCursor(19 + i, 19);
        std::cout << "\xDB";
        Sleep(30);
    }

    setColor(lightgreen, black);
    setCursor(18, 21);
    std::cout << "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB";
    setCursor(18, 22);
    std::cout << "\xBA       \xD1\xC8\xD3\xD2\xC5\xCC\xC0 \xC3\xCF\xD4\xCF\xD7\xC0       \xBA";
    setCursor(18, 23);
    std::cout << "\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC";

    Sleep(500);
}

// --- Главное меню ---

void showMainMenu(int& selected) {
    const char* menuItems[] = {
        "  \xC1\xEE\xE9 \xF1 \xE1\xEE\xF2\xEE\xEC                      ",
        "  \xC1\xEE\xE9 1 \xED\xE0 1 (\xEF\xEE \xEE\xF7\xE5\xF0\xE5\xE4\xE8)          ",
        "  \xC1\xEE\xE9 1 \xED\xE0 1 (\xF0\xE0\xE7\xE4\xE5\xEB\xB8\xED\xED\xFB\xE9 \xFD\xEA\xF0\xE0\xED)   ",
        "  \xCD\xE0\xF1\xF2\xF0\xEE\xE9\xEA\xE8 \xE7\xE2\xF3\xEA\xE0                  ",
        "  \xCE\xE1 \xE8\xE3\xF0\xE5                          ",
        "  \xC2\xFB\xF5\xEE\xE4                            "
    };
    const int menuCount = 6;

    while (true) {
        system("cls");

        setColor(lightcyan, black);
        setCursor(20, 1);
        std::cout << "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB";
        setCursor(20, 2);
        std::cout << "\xBA     \xCC \xCF \xD0 \xD1 \xCA \xCF \xCA   \xC1 \xCF \xCA       \xBA";
        setCursor(20, 3);
        std::cout << "\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC";

        drawBox(18, 6, 40, menuCount + 2, yellow);

        for (int i = 0; i < menuCount; i++) {
            setCursor(20, 8 + i);
            if (i == selected) {
                setColor(black, yellow);
                std::cout << "> " << menuItems[i];
            } else {
                setColor(white, black);
                std::cout << "  " << menuItems[i];
            }
        }

        setColor(darkgray, black);
        setCursor(2, 23);
        std::cout << "\xD1\xF2\xF0\xE5\xEB\xEA\xE8 \xC2\xC2\xC5\xD0\xD5/\xC2\xCD\xC8\xC7 - \xE2\xFB\xE1\xEE\xF0 | ENTER - \xEF\xEE\xE4\xF2\xE2\xE5\xF0\xE4\xE8\xF2\xFC | ESC - \xE2\xFB\xF5\xEE\xE4";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: selected = (selected - 1 + menuCount) % menuCount; break;
                case 80: selected = (selected + 1) % menuCount; break;
            }
        } else if (key == 13) {
            playSound(800, 80);
            return;
        } else if (key == 27) {
            if (confirmExit()) {
                selected = 5;
                return;
            }
        }
    }
}

// --- Другие экраны ---

void showRules() {
    system("cls");
    drawBox(2, 1, 74, 20, lightcyan);

    setColor(yellow, black);
    setCursor(28, 2);
    std::cout << "=== \xCE \xC1   \xC8 \xC3 \xD0 \xC5 ===";

    setColor(white, black);
    setCursor(6, 4);
    std::cout << "\xCD\xE0\xE7\xE2\xE0\xED\xE8\xE5: \xCC\xEE\xF0\xF1\xEA\xEE\xE9 \xE1\xEE\xE9 \xE8 \xCA\xEE\xED\xF1\xEE\xEB\xFC\xED\xFB\xE9 \xC1\xEE\xE9";
    setCursor(6, 5);
    std::cout << "\xC2\xE5\xF0\xF1\xE8\xFF: 1.0";
    setCursor(6, 6);
    std::cout << "\xD0\xE0\xE7\xF0\xE0\xE1\xEE\xF2\xE0\xED\xEE \xED\xE0: C++ / WinAPI";
    setCursor(6, 7);
    std::cout << "\xD1\xF2\xE8\xEB\xFC: \xD0\xE5\xF2\xF0\xEE 80-\xE5, \xEF\xE8\xEA\xF1\xE5\xEB\xFC-\xE0\xF0\xF2";

    setColor(lightcyan, black);
    setCursor(6, 9);
    std::cout << "=== \xD3\xCF\xD0\xC0\xC2\xCB\xC5\xCD\xC8\xC5 ===";

    setColor(white, black);
    setCursor(6, 10);
    std::cout << "\xC2 \xCC\xC5\xCD\xDE: \xD1\xF2\xF0\xE5\xEB\xEA\xE8 \x18\x19 - \xE2\xFB\xE1\xEE\xF0 | ENTER - \xEF\xEE\xE4\xF2\xE2\xE5\xF0\xE4\xE8\xF2\xFC | ESC - \xE2\xFB\xF5\xEE\xE4";
    setCursor(6, 11);
    std::cout << "\xD0\xC0\xD1\xD1\xD2\xC0\xCD\xCE\xC2\xCA\xC0: \xD1\xF2\xF0\xE5\xEB\xEA\xE8 - \xE4\xE2\xE8\xE6\xE5\xED\xE8\xE5 | \xCF\xD0\xCE\xC1\xC5\xCB - \xEF\xEE\xE2\xEE\xF0\xEE\xF2 | ENTER - \xF3\xF1\xF2\xE0\xED\xEE\xE2\xE8\xF2\xFC";
    setCursor(6, 12);
    std::cout << "\xC1\xCE\xC9: \xD1\xF2\xF0\xE5\xEB\xEA\xE8 - \xE4\xE2\xE8\xE6\xE5\xED\xE8\xE5 \xEF\xF0\xE8\xF6\xE5\xEB\xE0 | ENTER - \xE2\xFB\xF1\xF2\xF0\xE5\xEB | ESC - \xE2\xFB\xF5\xEE\xE4";
    setCursor(6, 13);
    std::cout << "\xD0\xC0\xC7\xC4\xC5\xCB\xB8\xCD\xCD\xDB\xC9: P1 - WASD+SHIFT | P2 - \xD1\xF2\xF0\xE5\xEB\xEA\xE8+ENTER | ESC - \xE2\xFB\xF5\xEE\xE4";

    setColor(lightcyan, black);
    setCursor(6, 15);
    std::cout << "=== \xCF\xD0\xC0\xC2\xC8\xCB\xC0 ===";

    setColor(white, black);
    setCursor(6, 16);
    std::cout << "\xC6\xE5\xEB\xFC: \xEF\xEE\xF2\xEE\xEF\xE8\xF2\xFC \xE2\xF1\xE5 \xEA\xEE\xF0\xE0\xE1\xEB\xE8 \xEF\xF0\xEE\xF2\xE8\xE2\xED\xE8\xEA\xE0";
    setCursor(6, 17);
    std::cout << "\xD4\xEB\xEE\xF2: 1\xD74\xEF\xE0\xEB, 2\xD73\xEF\xE0\xEB, 3\xD72\xEF\xE0\xEB, 4\xD71\xEF\xE0\xEB (10 \xEA\xEE\xF0\xE0\xE1\xEB\xE5\xE9)";
    setCursor(6, 18);
    std::cout << "\xCF\xF0\xE8 \xEF\xEE\xEF\xE0\xE4\xE0\xED\xE8\xE8 \xE4\xEE\xEF\xEE\xEB\xED\xE8\xF2\xE5\xEB\xFC\xED\xFB\xE9 \xF5\xEE\xE4. \xCA\xEE\xF0\xE0\xE1\xEB\xE8 \xED\xE5 \xE4\xEE\xEB\xE6\xED\xFB \xEA\xE0\xF1\xE0\xF2\xFC\xF1\xFF \xE4\xF0\xF3\xE3 \xE4\xF0\xF3\xE3\xE0";

    setColor(darkgray, black);
    setCursor(6, 22);
    std::cout << "\xCD\xE0\xE6\xEC\xE8\xF2\xE5 \xEB\xFE\xE1\xF3\xFE \xEA\xEB\xE0\xE2\xE8\xF8\xF3 \xE4\xEB\xFF \xE2\xEE\xE7\xE2\xF0\xE0\xF2\xE0 \xE2 \xEC\xE5\xED\xFE...";
    _getch();
}

void showSoundSettings() {
    const char* items[] = { "\xC3\xF0\xEE\xEC\xEA\xEE\xF1\xF2\xFC: ", "\xD2\xE5\xF1\xF2 \xE7\xE2\xF3\xEA\xE0  ", "\xCD\xE0\xE7\xE0\xE4       " };
    int sel = 0;
    bool localSound = soundEnabled;

    while (true) {
        system("cls");
        drawBox(20, 6, 36, 7, yellow);

        setColor(yellow, black);
        setCursor(26, 7);
        std::cout << "=== \xCD\xC0\xD1\xD2\xD0\xCE\xC9\xCA\xC8 \xC7\xC2\xD3\xCA\xC0 ===";

        for (int i = 0; i < 3; i++) {
            setCursor(22, 9 + i);
            if (i == sel) setColor(black, yellow);
            else setColor(white, black);
            std::cout << items[i];
            if (i == 0) std::cout << (localSound ? "[\xC2\xCA\xCB] " : "[\xC2\xDB\xCA\xCB]");
        }

        setColor(darkgray, black);
        setCursor(2, 23);
        std::cout << "\x18\x19 - \xE2\xFB\xE1\xEE\xF0 | \x1B\x1A - \xE8\xE7\xEC\xE5\xED\xE5\xED\xE8\xE5 | ENTER - \xF2\xE5\xF1\xF2/\xEF\xF0\xE8\xEC\xE5\xED\xE8\xF2\xFC | ESC - \xED\xE0\xE7\xE0\xE4";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: sel = (sel - 1 + 3) % 3; break;
                case 80: sel = (sel + 1) % 3; break;
                case 75: case 77: if (sel == 0) localSound = !localSound; break;
            }
        } else if (key == 13) {
            if (sel == 0) { soundEnabled = localSound; playSound(800, 100); }
            else if (sel == 1) {
                playSound(1200, 150); playSound(800, 100); Sleep(200);
                playSound(400, 300); Sleep(200);
                playSound(523, 200); playSound(659, 200); playSound(784, 200); playSound(1047, 400);
            } else if (sel == 2) { soundEnabled = localSound; return; }
        } else if (key == 27) { soundEnabled = localSound; return; }
    }
}

bool confirmExit() {
    setColor(yellow, black);
    setCursor(2, 24);
    std::cout << "\xC2\xFB \xF2\xEE\xF7\xED\xEE \xF5\xEE\xF2\xE8\xF2\xE5 \xE2\xFB\xE9\xF2\xE8? (Y/N): ";
    while (true) {
        int key = _getch();
        if (key == 'Y' || key == 'y') { clearRow(24); return true; }
        else if (key == 'N' || key == 'n' || key == 27) { clearRow(24); return false; }
    }
}

void switchScreenWithTimer(const std::string& nextPlayerName) {
    system("cls");
    drawBox(15, 6, 48, 10, yellow);

    setColor(yellow, black);
    setCursor(24, 8);
    std::cout << "=== \xCF \xC5 \xD0 \xC5 \xC4 \xC0 \xDE \xC0   \xC7 \xCE \xC4 \xC0 ===";

    setColor(white, black);
    setCursor(28, 10);
    std::cout << "\xCF\xEE\xEC\xE5\xED\xFF\xE9\xF2\xE5\xF1\xFC \xEC\xE5\xF1\xF2\xE0\xEC\xE8!";

    setColor(lightcyan, black);
    setCursor(22, 11);
    std::cout << ">>> " << nextPlayerName << " <<<";

    for (int i = 3; i >= 1; i--) {
        setColor(lightred, black); setCursor(38, 13); std::cout << i << " "; Sleep(500);
        setColor(red, black); setCursor(38, 13); std::cout << i << " "; Sleep(500);
    }
    system("cls");
}

void showMessage(const std::string& text, Color color, int row) {
    clearRow(row);
    printCentered(text, row, color);
}

void showVictoryScreen(const std::string& winner) {
    system("cls");
    drawBox(15, 6, 48, 7, lightgreen);

    setColor(lightgreen, black);
    setCursor(24, 9);
    std::cout << "=== " << winner << " \xCF \xCE \xC1 \xC5 \xC4 \xC8 \xCC ! ===";

    playSound(523, 200); playSound(659, 200); playSound(784, 200); playSound(1047, 400);

    setColor(darkgray, black);
    setCursor(10, 18);
    std::cout << "ENTER \xE8\xE3\xF0\xE0\xF2\xFC \xF1\xED\xEE\xE2\xE0 | ESC \xE2\xFB\xF5\xEE\xE4 \xE2 \xEC\xE5\xED\xFE";
}

void showDefeatScreen(const std::string& loser) {
    system("cls");
    drawBox(15, 6, 48, 7, lightred);

    setColor(lightred, black);
    setCursor(26, 9);
    std::cout << "=== " << loser << " \xCF \xD0 \xCE \xC8 \xC3 \xD0 \xC0 \xCC ===";

    playSound(400, 300); playSound(300, 300); playSound(200, 500);

    setColor(darkgray, black);
    setCursor(10, 18);
    std::cout << "ENTER \xE8\xE3\xF0\xE0\xF2\xFC \xF1\xED\xEE\xE2\xE0 | ESC \xE2\xFB\xF5\xEE\xE4 \xE2 \xEC\xE5\xED\xFE";
}

// --- \xD0\xC5\xD6\xC8\xCC "\xC1\xCE\xC9 \xD1 \xC1\xCE\xD2\xCE\xCC" ---

bool playBotMode(int field1[R][R], int field2[R][R], int botLevel, bool autoPlaceP1) {
    if (autoPlaceP1) {
        autoPlace(field1);
        setColor(white, black); setCursor(2, 23);
        std::cout << "\xC2\xE0\xF8\xE8 \xEA\xEE\xF0\xE0\xE1\xEB\xE8 \xF0\xE0\xF1\xF1\xF2\xE0\xE2\xEB\xE5\xED\xFB \xE0\xE2\xF2\xEE\xEC\xE0\xF2\xE8\xF7\xE5\xF1\xEA\xE8..."; Sleep(1000);
    } else { stavlyusam(field1, "\xC8\xC3\xD0\xCE\xCA 1"); }
    autoPlace(field2);

    int cursorY = 0, cursorX = 0;
    bool playerTurn = true;

    while (true) {
        system("cls");

        setColor(lightcyan, black); setCursor(2, 0);
        std::cout << "=== \xC1\xCE\xC9 \xD1 \xC1\xCE\xD2\xCE\xCC ===  ";
        std::cout << (botLevel == 0 ? "[\xCB\xB8\xC3\xCA\xC8\xC9]" : "[\xD1\xCB\xCE\xC6\xCD\xDB\xC9]");

        setColor(lightred, black); setCursor(2, 1);
        std::cout << "--- \xCF\xCE\xCB\xC5 \xCF\xD0\xCE\xD2\xC8\xC2\xCD\xC8\xCA\xC0 ---";
        drawSingleGrid(field2, cursorY, cursorX, false, false, 0, true, true, playerTurn, 2, 2);

        setColor(lightgreen, black); setCursor(2, 15);
        std::cout << "------ \xC2\xC0\xD8\xC5 \xCF\xCE\xCB\xC5 ------";
        drawSingleGrid(field1, -1, -1, true, false, 0, true, true, false, 2, 16);

        setColor(darkgray, black); setCursor(2, 23);
        std::cout << "\xD1\xF2\xF0\xE5\xEB\xEA\xE8 \xF0\xE8\xF6\xE5\xEB | ENTER \xE2\xFB\xF1\xF2\xF0\xE5\xEB | ESC \xE2\xFB\xF5\xEE\xE4             ";

        if (!playerTurn) {
            setColor(yellow, black); setCursor(45, 9); std::cout << "\xC1\xEE\xF2 \xE4\xF3\xEC\xE0\xE5\xF2..."; Sleep(800);

            int by, bx;
            if (botLevel == 0) botEasyMove(field1, by, bx); else botSmartMove(field1, by, bx);
            if (by < 0 || bx < 0) break;
            clearRow(9);

            if (field1[by][bx] == CELL_SHIP) {
                field1[by][bx] = CELL_HIT; flashHit(by, bx, 2, 16);
                setColor(lightred, black); setCursor(45, 9);
                std::cout << "\xC2\xC0\xD1 \xCF\xCE\xC4\xC1\xC8\xCB\xC8! (" << (char)('A'+bx) << by << ")";
                playSound(1200, 150); Sleep(500);
                if (allShipsDestroyed(field1)) { showDefeatScreen("\xC8\xC3\xD0\xCE\xCA 1"); _getch(); return false; }
                continue;
            } else {
                field1[by][bx] = CELL_MISS; flashMiss(by, bx, 2, 16);
                setColor(white, black); setCursor(45, 9);
                std::cout << "\xC1\xEE\xF2 \xEF\xF0\xEE\xEC\xE0\xF5\xED\xF3\xEB\xF1\xFF (" << (char)('A'+bx) << by << ")";
                playSound(400, 300); Sleep(500); playerTurn = true;
            }
        } else {
            int key = _getch();
            if (key == 224) {
                key = _getch();
                switch (key) {
                    case 72: if (cursorY > 0) cursorY--; break; case 80: if (cursorY < R - 1) cursorY++; break;
                    case 75: if (cursorX > 0) cursorX--; break; case 77: if (cursorX < R - 1) cursorX++; break;
                }
            } else if (key == 13) {
                if (field2[cursorY][cursorX] == CELL_HIT || field2[cursorY][cursorX] == CELL_MISS) {
                    showMessage("\xD1\xFE\xE4\xE0 \xF3\xE6\xE5 \xF1\xF2\xF0\xE5\xEB\xFF\xEB\xE8! \xC2\xFB\xE1\xE5\xF0\xE8\xF2\xE5 \xE4\xF0\xF3\xE3\xF3\xFE \xEA\xEB\xE5\xF2\xEA\xF3.", yellow, 22); Sleep(800); clearRow(22);
                } else if (field2[cursorY][cursorX] == CELL_SHIP) {
                    field2[cursorY][cursorX] = CELL_HIT; flashHit(cursorY, cursorX, 2, 2);
                    showMessage(">>> \xC1 \xC0 \xC1 \xC0 \xD5 !  \xCF \xCE \xCF \xC0 \xC4 \xC0 \xCD \xC8 \xC5 ! <<<", lightred, 22);
                    playSound(1200, 150); playSound(800, 100); Sleep(500); clearRow(22);
                    if (allShipsDestroyed(field2)) { showVictoryScreen("\xC8\xC3\xD0\xCE\xCA 1"); _getch(); return true; }
                } else {
                    field2[cursorY][cursorX] = CELL_MISS; flashMiss(cursorY, cursorX, 2, 2);
                    showMessage(">>> \xCC \xC8 \xCC \xCF . . . <<<", cyan, 22);
                    playSound(400, 300); Sleep(500); clearRow(22); playerTurn = false;
                }
            } else if (key == 27) { if (confirmExit()) return false; }
        }
    }
    return false;
}

// --- \xD0\xC5\xD6\xC8\xCC "1 \xCD\xC0 1 \xCF\xCE \xCE\xD7\xC5\xD0\xC5\xC4\xC8" ---

bool playPVP_TurnMode(int p1Field[R][R], int p2Field[R][R], int p1Fog[R][R], int p2Fog[R][R]) {
    stavlyusam(p1Field, "\xC8\xC3\xD0\xCE\xCA 1");
    switchScreenWithTimer("\xC8\xC3\xD0\xCE\xCA 2");
    stavlyusam(p2Field, "\xC8\xC3\xD0\xCE\xCA 2");
    switchScreenWithTimer("\xC8\xC3\xD0\xCE\xCA 1");

    int cursorY = 0, cursorX = 0;
    int currentPlayer = 1;

    while (true) {
        system("cls");

        int (*myField)[R] = (currentPlayer == 1) ? p1Field : p2Field;
        int (*enemyField)[R] = (currentPlayer == 1) ? p2Field : p1Field;
        int (*enemyFog)[R] = (currentPlayer == 1) ? p2Fog : p1Fog;

        setColor(lightcyan, black); setCursor(2, 0);
        std::cout << "=== \xC7\xCE\xC4 \xC8\xC3\xD0\xCE\xCA\xC0 " << currentPlayer << " ===";

        setColor(lightred, black); setCursor(2, 1);
        std::cout << "--- \xCF\xCE\xCB\xC5 \xCF\xD0\xCE\xD2\xC8\xC2\xCD\xC8\xCA\xC0 ---";
        drawSingleGrid(enemyField, cursorY, cursorX, false, false, 0, true, true, true, 2, 2);

        setColor(lightgreen, black); setCursor(2, 15);
        std::cout << "------ \xC2\xC0\xD8\xC5 \xCF\xCE\xCB\xC5 ------";
        drawSingleGrid(myField, -1, -1, true, false, 0, true, true, false, 2, 16);

        setColor(darkgray, black); setCursor(2, 23);
        std::cout << "\xD1\xF2\xF0\xE5\xEB\xEA\xE8 \xF0\xE8\xF6\xE5\xEB | ENTER \xE2\xFB\xF1\xF2\xF0\xE5\xEB | ESC \xE2\xFB\xF5\xEE\xE4";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: if (cursorY > 0) cursorY--; break; case 80: if (cursorY < R - 1) cursorY++; break;
                case 75: if (cursorX > 0) cursorX--; break; case 77: if (cursorX < R - 1) cursorX++; break;
            }
        } else if (key == 13) {
            if (enemyFog[cursorY][cursorX] == CELL_HIT || enemyFog[cursorY][cursorX] == CELL_MISS) {
                showMessage("\xD1\xFE\xE4\xE0 \xF3\xE6\xE5 \xF1\xF2\xF0\xE5\xEB\xFF\xEB\xE8!", yellow, 22); Sleep(800); clearRow(22);
            } else if (enemyField[cursorY][cursorX] == CELL_SHIP) {
                enemyField[cursorY][cursorX] = CELL_HIT; enemyFog[cursorY][cursorX] = CELL_HIT;
                flashHit(cursorY, cursorX, 2, 2);
                showMessage(">>> \xCF \xCE \xCF \xC0 \xC4 \xC0 \xCD \xC8 \xC5 ! <<<", lightred, 22);
                playSound(1200, 150); playSound(800, 100); Sleep(500); clearRow(22);
                if (allShipsDestroyed(enemyField)) {
                    std::string winner = (currentPlayer == 1) ? "\xC8\xC3\xD0\xCE\xCA 1" : "\xC8\xC3\xD0\xCE\xCA 2";
                    showVictoryScreen(winner); _getch(); return (currentPlayer == 1);
                }
            } else {
                enemyField[cursorY][cursorX] = CELL_MISS; enemyFog[cursorY][cursorX] = CELL_MISS;
                flashMiss(cursorY, cursorX, 2, 2);
                showMessage(">>> \xCC \xC8 \xCC \xCE . . . <<<", cyan, 22);
                playSound(400, 300); Sleep(500); clearRow(22);
                std::string nextPlayer = (currentPlayer == 1) ? "\xC8\xC3\xD0\xCE\xCA 2" : "\xC8\xC3\xD0\xCE\xCA 1";
                switchScreenWithTimer(nextPlayer);
                currentPlayer = (currentPlayer == 1) ? 2 : 1; cursorY = 0; cursorX = 0;
            }
        } else if (key == 27) { if (confirmExit()) return false; }
    }
}

// --- \xD0\xC5\xD6\xC8\xCD "1 \xCD\xC0 1 \xD0\xC0\xC7\xC4\xC5\xCB\xB8\xCD\xCD\xDB\xC9 \xDD\xCB\xD0\xC0\xCD" ---

bool playPVP_SplitMode(int p1Field[R][R], int p2Field[R][R], int p1Fog[R][R], int p2Fog[R][R]) {
    stavlyusam(p1Field, "\xC8\xC3\xD0\xCE\xCA 1");
    system("cls"); setColor(white, black); setCursor(15, 12);
    std::cout << "\xCD\xE0\xE6\xEC\xE8\xF2\xE5 \xEB\xFE\xE1\xF3\xFE \xEA\xEB\xE0\xE2\xE8\xF8\xF3, \xEA\xEE\xE3\xE4\xE0 \xE1\xF3\xE4\xE5\xF2\xE5 \xE3\xEE\xF2\xEE\xE2\xFB (\xC8\xE3\xF0\xEE\xEA 2)..."; _getch();
    stavlyusam(p2Field, "\xC8\xC3\xD0\xCE\xCA 2");

    int p1CursorY = 0, p1CursorX = 0;
    int p2CursorY = 0, p2CursorX = 0;
    int currentPlayer = 1;

    while (true) {
        system("cls");

        setColor(currentPlayer == 1 ? lightgreen : darkgray, black); setCursor(2, 0);
        std::cout << (currentPlayer == 1 ? ">>> \xC8\xC3\xD0\xCE\xCA 1 (\xC2\xC0\xD8 \xC7\xCE\xC4) <<<" : "    \xC8\xC3\xD0\xCE\xCA 1 (\xCE\xC6\xC8\xC4\xC0\xC5\xD2)    ");
        drawSingleGrid(p1Field, p1CursorY, p1CursorX, true, false, 0, true, true, currentPlayer == 1, 0, 1);

        drawDivider();

        setColor(currentPlayer == 2 ? lightred : darkgray, black); setCursor(42, 0);
        std::cout << (currentPlayer == 2 ? ">>> \xC8\xC3\xD0\xCE\xCA 2 (\xC2\xC0\xD8 \xC7\xCE\xC4) <<<" : "    \xC8\xC3\xD0\xCE\xCA 2 (\xCE\xC6\xC8\xC4\xC0\xC5\xD2)    ");
        drawSingleGrid(p2Field, p2CursorY, p2CursorX, true, false, 0, true, true, currentPlayer == 2, 41, 1);

        setColor(darkgray, black); setCursor(2, 23);
        std::cout << "P1: WASD+SHIFT | P2: \xD1\xF2\xF0\xE5\xEB\xEA\xE8+ENTER | ESC \xE2\xFB\xF5\xEE\xE4";

        int key = _getch();

        if (key == 27) { if (confirmExit()) return false; }
        else if (currentPlayer == 1) {
            bool shoot = false;
            switch (key) {
                case 'w': case 'W': if (p1CursorY > 0) p1CursorY--; break;
                case 's': case 'S': if (p1CursorY < R - 1) p1CursorY++; break;
                case 'a': case 'A': if (p1CursorX > 0) p1CursorX--; break;
                case 'd': case 'D': if (p1CursorX < R - 1) p1CursorX++; break;
                case 0: key = _getch(); if (key == 42 || key == 54) shoot = true; break;
            }
            if (shoot) {
                int ey = p1CursorY, ex = p1CursorX;
                if (p2Field[ey][ex] == CELL_HIT || p2Field[ey][ex] == CELL_MISS) {
                    showMessage("\xD3\xE6\xE5 \xF1\xF2\xF0\xE5\xEB\xFF\xEB\xE8!", yellow, 22); Sleep(800); clearRow(22);
                } else if (p2Field[ey][ex] == CELL_SHIP) {
                    p2Field[ey][ex] = CELL_HIT; flashHit(ey, ex, 41, 1);
                    showMessage("\xC8\xC3\xD0\xCE\xCA 1 \xE2\xF0\xE8\xEB!", lightgreen, 22);
                    playSound(1200, 150); Sleep(500); clearRow(22);
                    if (allShipsDestroyed(p2Field)) { showVictoryScreen("\xC8\xC3\xD0\xCE\xCA 1"); _getch(); return true; }
                } else {
                    p2Field[ey][ex] = CELL_MISS; flashMiss(ey, ex, 41, 1);
                    showMessage("\xC8\xC3\xD0\xCE\xCA 1 \xF2\xF0\xE8\xF2!", cyan, 22);
                    playSound(400, 300); Sleep(500); clearRow(22); currentPlayer = 2;
                }
            }
        } else {
            if (key == 224) {
                key = _getch();
                switch (key) {
                    case 72: if (p2CursorY > 0) p2CursorY--; break; case 80: if (p2CursorY < R - 1) p2CursorY++; break;
                    case 75: if (p2CursorX > 0) p2CursorX--; break; case 77: if (p2CursorX < R - 1) p2CursorX++; break;
                }
            } else if (key == 13) {
                int ey = p2CursorY, ex = p2CursorX;
                if (p1Field[ey][ex] == CELL_HIT || p1Field[ey][ex] == CELL_MISS) {
                    showMessage("\xD3\xE6\xE5 \xF1\xF2\xF0\xE5\xEB\xFF\xEB\xE8!", yellow, 22); Sleep(800); clearRow(22);
                } else if (p1Field[ey][ex] == CELL_SHIP) {
                    p1Field[ey][ex] = CELL_HIT; flashHit(ey, ex, 0, 1);
                    showMessage("\xC8\xC3\xD0\xCE\xCA 2 \xE2\xF0\xE8\xEB!", lightred, 22);
                    playSound(1200, 150); Sleep(500); clearRow(22);
                    if (allShipsDestroyed(p1Field)) { showVictoryScreen("\xC8\xC3\xD0\xCE\xCA 2"); _getch(); return false; }
                } else {
                    p1Field[ey][ex] = CELL_MISS; flashMiss(ey, ex, 0, 1);
                    showMessage("\xC8\xC3\xD0\xCE\xCA 2 \xF2\xF0\xE8\xF2!", cyan, 22);
                    playSound(400, 300); Sleep(500); clearRow(22); currentPlayer = 1;
                }
            }
        }
    }
}
