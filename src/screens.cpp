// ============================================================================
// screens.cpp — Реализация экранов и игровых режимов
// ============================================================================

#include "screens.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

static void printCentered(const std::string& text, int y, Color color) {
    int x = (SCREEN_WIDTH - (int)text.length()) / 2;
    if (x < 0) x = 0;
    setCursor(x, y);
    setColor(color, black);
    std::cout << text;
}

static void clearRow(int y) {
    setCursor(0, y);
    setColor(black, black);
    for (int i = 0; i < SCREEN_WIDTH; i++) std::cout << " ";
}

static bool allShipsDestroyed(int field[R][R]) {
    return !checkAlive(field);
}

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
    std::cout << "+=====================================+";
    setCursor(20, 11);
    std::cout << "|     K O N S O LxNYJ   B O J       |";
    setCursor(20, 12);
    std::cout << "+=====================================+";

    setColor(darkgray, black);
    setCursor(18, 16);
    std::cout << "\x87\xA0\xA3\xE0\xE3\xA7\xAA\xA0 \xE1\xA8\xE1\xE2\xA5\xAC\xEB...";

    drawBox(18, 18, 40, 1, green);
    setColor(lightgreen, black);
    for (int i = 0; i < 40; i++) {
        setCursor(19 + i, 19);
        std::cout << "#";
        Sleep(30);
    }

    setColor(lightgreen, black);
    setCursor(18, 21);
    std::cout << "+=====================================+";
    setCursor(18, 22);
    std::cout << "|       \x91\x88\x91\x92\x85\x8C\x80 \x83\x8E\x92\x8E\x82\x80       |";
    setCursor(18, 23);
    std::cout << "+=====================================+";

    Sleep(500);
}

void showMainMenu(int& selected) {
    const char* menuItems[] = {
        "  \x81\xAE\xA9 \xE1 \xA1\xAE\xE2\xAE\xAC                      ",
        "  \x81\xAE\xA9 1 \xAD\xA0 1 (\xAF\xAE \xAE\xE7\xA5\xE0\xA5\xA4\xA8)          ",
        "  \x81\xAE\xA9 1 \xAD\xA0 1 (\xE0\xA0\xA7\xA4\xA5\xAB\xF1\xAD\xAD\xEB\xA9 \xED\xAA\xE0\xA0\xAD)   ",
        "  \x8D\xA0\xE1\xE2\xE0\xAE\xA9\xAA\xA8 \xA7\xA2\xE3\xAA\xA0                  ",
        "  \x8E\xA1 \xA8\xA3\xE0\xA5                          ",
        "  \x82\xEB\xE5\xAE\xA4                            "
    };
    const int menuCount = 6;

    while (true) {
        system("cls");

        setColor(lightcyan, black);
        setCursor(20, 1);
        std::cout << "+=====================================+";
        setCursor(20, 2);
        std::cout << "|     M O R S K O J   B O J         |";
        setCursor(20, 3);
        std::cout << "+=====================================+";

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
        std::cout << "\xE1\xE2\xE0\xA5\xAB\xAA\xA8 ^/v - \xA2\xEB\xA1\xAE\xE0 | ENTER - \xAF\xAE\xA4\xE2\xA2\xA5\xE0\xA4\xA8\xE2\xEC | ESC - \xA2\xEB\xE5\xAE\xA4";

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

void showRules() {
    system("cls");
    drawBox(2, 1, 74, 20, lightcyan);

    setColor(yellow, black);
    setCursor(28, 2);
    std::cout << "=== O B   I G R E ===";

    setColor(white, black);
    setCursor(6, 4);
    std::cout << "\x8D\xA0\xA7\xA2\xA0\xAD\xA8\xA5: Morskoj Boj";
    setCursor(6, 5);
    std::cout << "\x82\xA5\xE0\xE1\xA8\xEF: 1.0";
    setCursor(6, 6);
    std::cout << "\x90\xA0\xA7\xE0\xA0\xA1\xAE\xE2\xA0\xAD\xAE \xAD\xA0: C++ / WinAPI";
    setCursor(6, 7);
    std::cout << "\x91\xE2\xA8\xAB\xEC: Retro 80-x";

    setColor(lightcyan, black);
    setCursor(6, 9);
    std::cout << "=== UPRAWLENIE ===";

    setColor(white, black);
    setCursor(6, 10);
    std::cout << "V MENU: Strelki ^/v - vybor | ENTER - podtverditx | ESC - vyhod";
    setCursor(6, 11);
    std::cout << "RASSTANOWKA: Strelki - dvizhenie | PROBEL - povorot | ENTER - ustanovitx";
    setCursor(6, 12);
    std::cout << "BOJ: Strelki - dvizhenie price|a | ENTER - vystrel | ESC - vyhod";
    setCursor(6, 13);
    std::cout << "PAZDELxNNYJ: P1 - WASD+SHIFT | P2 - Strelki+ENTER | ESC - vyhod";

    setColor(lightcyan, black);
    setCursor(6, 15);
    std::cout << "=== PRAWILA ===";

    setColor(white, black);
    setCursor(6, 16);
    std::cout << "Celx: potopitx vse korabli protivnika";
    setCursor(6, 17);
    std::cout << "Flot: 1x4pal, 2x3pal, 3x2pal, 4x1pal (10 korabl\xA5\xA9)";
    setCursor(6, 18);
    std::cout << "Pri popadanii - dopolnitelxnyj hod. Korabli ne dolzhny kasatxsja";

    setColor(darkgray, black);
    setCursor(6, 22);
    std::cout << "Nazhmite ljubuju klavishu dlja vozvrata v menju...";
    _getch();
}

void showSoundSettings() {
    const char* items[] = { "Gromkostx: ", "Test zvuka  ", "Nazad       " };
    int sel = 0;
    bool localSound = soundEnabled;

    while (true) {
        system("cls");
        drawBox(20, 6, 36, 7, yellow);

        setColor(yellow, black);
        setCursor(26, 7);
        std::cout << "=== NASTROJKI ZWUKA ===";

        for (int i = 0; i < 3; i++) {
            setCursor(22, 9 + i);
            if (i == sel) setColor(black, yellow);
            else setColor(white, black);
            std::cout << items[i];
            if (i == 0) std::cout << (localSound ? "[WKL] " : "[WYK\x8B]");
        }

        setColor(darkgray, black);
        setCursor(2, 23);
        std::cout << "^/v - vybor | </> - izmenenie | ENTER - test/primenitx | ESC - nazad";

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
    std::cout << "Wy tochno hotite wyjti? (Y/N): ";
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
    std::cout << "=== PEREDA^A HODA ===";

    setColor(white, black);
    setCursor(28, 10);
    std::cout << "Pomenjajtesx mestami!";

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
    std::cout << "=== " << winner << " P O B E D I L ! ===";

    playSound(523, 200); playSound(659, 200); playSound(784, 200); playSound(1047, 400);

    setColor(darkgray, black);
    setCursor(10, 18);
    std::cout << "ENTER - igratx snova | ESC - vyhod v menju";
}

void showDefeatScreen(const std::string& loser) {
    system("cls");
    drawBox(15, 6, 48, 7, lightred);

    setColor(lightred, black);
    setCursor(26, 9);
    std::cout << "=== " << loser << " P R O I G R A L ===";

    playSound(400, 300); playSound(300, 300); playSound(200, 500);

    setColor(darkgray, black);
    setCursor(10, 18);
    std::cout << "ENTER - igratx snova | ESC - vyhod v menju";
}

bool playBotMode(int field1[R][R], int field2[R][R], int botLevel, bool autoPlaceP1) {
    if (autoPlaceP1) {
        autoPlace(field1);
        setColor(white, black); setCursor(2, 23);
        std::cout << "\x82\xA0\xE8\xA8 \xAA\xAE\xE0\xA0\xA1\xAB\xA8 \xE0\xA0\xE1\xE1\xE2\xA0\xA2\xAB\xA5\xAD\xEB \xA0\xA2\xE2\xAE\xAC\xA0\xE2\xA8\xE7\xA5\xE1\xAA\xA8..."; Sleep(1000);
    } else { stavlyusam(field1, "IGROK 1"); }
    autoPlace(field2);

    int cursorY = 0, cursorX = 0;
    bool playerTurn = true;

    while (true) {
        system("cls");

        setColor(lightcyan, black); setCursor(2, 0);
        std::cout << "=== BOJ S BOTOM ===  ";
        std::cout << (botLevel == 0 ? "[LxGKIJ]" : "[SLOZhNYJ]");

        setColor(lightred, black); setCursor(2, 1);
        std::cout << "--- POLE PROTIBNIKA ---";
        drawSingleGrid(field2, cursorY, cursorX, false, false, 0, true, true, playerTurn, 2, 2);

        setColor(lightgreen, black); setCursor(2, 15);
        std::cout << "------ WASxE POLE ------";
        drawSingleGrid(field1, -1, -1, true, false, 0, true, true, false, 2, 16);

        setColor(darkgray, black); setCursor(2, 23);
        std::cout << "Strelki - price| | ENTER - vystrel | ESC - vyhod             ";

        if (!playerTurn) {
            setColor(yellow, black); setCursor(45, 9); std::cout << "Bot dumaet..."; Sleep(800);

            int by, bx;
            if (botLevel == 0) botEasyMove(field1, by, bx); else botSmartMove(field1, by, bx);
            if (by < 0 || bx < 0) break;
            clearRow(9);

            if (field1[by][bx] == CELL_SHIP) {
                field1[by][bx] = CELL_HIT; flashHit(by, bx, 2, 16);
                setColor(lightred, black); setCursor(45, 9);
                std::cout << "WAS PODBILI! (" << (char)('A'+bx) << by << ")";
                playSound(1200, 150); Sleep(500);
                if (allShipsDestroyed(field1)) { showDefeatScreen("IGROK 1"); _getch(); return false; }
                continue;
            } else {
                field1[by][bx] = CELL_MISS; flashMiss(by, bx, 2, 16);
                setColor(white, black); setCursor(45, 9);
                std::cout << "Bot promahnulsja (" << (char)('A'+bx) << by << ")";
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
                    showMessage("Sjuda uzhe streljli!", yellow, 22); Sleep(800); clearRow(22);
                } else if (field2[cursorY][cursorX] == CELL_SHIP) {
                    field2[cursorY][cursorX] = CELL_HIT; flashHit(cursorY, cursorX, 2, 2);
                    showMessage(">>> POPADANIE! <<<", lightred, 22);
                    playSound(1200, 150); playSound(800, 100); Sleep(500); clearRow(22);
                    if (allShipsDestroyed(field2)) { showVictoryScreen("IGROK 1"); _getch(); return true; }
                } else {
                    field2[cursorY][cursorX] = CELL_MISS; flashMiss(cursorY, cursorX, 2, 2);
                    showMessage(">>> MIMO... <<<", cyan, 22);
                    playSound(400, 300); Sleep(500); clearRow(22); playerTurn = false;
                }
            } else if (key == 27) { if (confirmExit()) return false; }
        }
    }
    return false;
}

bool playPVP_TurnMode(int p1Field[R][R], int p2Field[R][R], int p1Fog[R][R], int p2Fog[R][R]) {
    stavlyusam(p1Field, "IGROK 1");
    switchScreenWithTimer("IGROK 2");
    stavlyusam(p2Field, "IGROK 2");
    switchScreenWithTimer("IGROK 1");

    int cursorY = 0, cursorX = 0;
    int currentPlayer = 1;

    while (true) {
        system("cls");

        int (*myField)[R] = (currentPlayer == 1) ? p1Field : p2Field;
        int (*enemyField)[R] = (currentPlayer == 1) ? p2Field : p1Field;
        int (*enemyFog)[R] = (currentPlayer == 1) ? p2Fog : p1Fog;

        setColor(lightcyan, black); setCursor(2, 0);
        std::cout << "=== HOD IGROKA " << currentPlayer << " ===";

        setColor(lightred, black); setCursor(2, 1);
        std::cout << "--- POLE PROTIBNIKA ---";
        drawSingleGrid(enemyField, cursorY, cursorX, false, false, 0, true, true, true, 2, 2);

        setColor(lightgreen, black); setCursor(2, 15);
        std::cout << "------ WASxE POLE ------";
        drawSingleGrid(myField, -1, -1, true, false, 0, true, true, false, 2, 16);

        setColor(darkgray, black); setCursor(2, 23);
        std::cout << "Strelki - price| | ENTER - vystrel | ESC - vyhod";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: if (cursorY > 0) cursorY--; break; case 80: if (cursorY < R - 1) cursorY++; break;
                case 75: if (cursorX > 0) cursorX--; break; case 77: if (cursorX < R - 1) cursorX++; break;
            }
        } else if (key == 13) {
            if (enemyFog[cursorY][cursorX] == CELL_HIT || enemyFog[cursorY][cursorX] == CELL_MISS) {
                showMessage("Sjuda uzhe streljli!", yellow, 22); Sleep(800); clearRow(22);
            } else if (enemyField[cursorY][cursorX] == CELL_SHIP) {
                enemyField[cursorY][cursorX] = CELL_HIT; enemyFog[cursorY][cursorX] = CELL_HIT;
                flashHit(cursorY, cursorX, 2, 2);
                showMessage(">>> POPADANIE! <<<", lightred, 22);
                playSound(1200, 150); playSound(800, 100); Sleep(500); clearRow(22);
                if (allShipsDestroyed(enemyField)) {
                    std::string winner = (currentPlayer == 1) ? "IGROK 1" : "IGROK 2";
                    showVictoryScreen(winner); _getch(); return (currentPlayer == 1);
                }
            } else {
                enemyField[cursorY][cursorX] = CELL_MISS; enemyFog[cursorY][cursorX] = CELL_MISS;
                flashMiss(cursorY, cursorX, 2, 2);
                showMessage(">>> MIMO... <<<", cyan, 22);
                playSound(400, 300); Sleep(500); clearRow(22);
                std::string nextPlayer = (currentPlayer == 1) ? "IGROK 2" : "IGROK 1";
                switchScreenWithTimer(nextPlayer);
                currentPlayer = (currentPlayer == 1) ? 2 : 1; cursorY = 0; cursorX = 0;
            }
        } else if (key == 27) { if (confirmExit()) return false; }
    }
}

bool playPVP_SplitMode(int p1Field[R][R], int p2Field[R][R], int p1Fog[R][R], int p2Fog[R][R]) {
    stavlyusam(p1Field, "IGROK 1");
    system("cls"); setColor(white, black); setCursor(15, 12);
    std::cout << "Nazhmite ljubuju klavishu, kogda budete gotowy (Igrok 2)..."; _getch();
    stavlyusam(p2Field, "IGROK 2");

    int p1CursorY = 0, p1CursorX = 0;
    int p2CursorY = 0, p2CursorX = 0;
    int currentPlayer = 1;

    while (true) {
        system("cls");

        setColor(currentPlayer == 1 ? lightgreen : darkgray, black); setCursor(2, 0);
        std::cout << (currentPlayer == 1 ? ">>> IGROK 1 (WASx HOD) <<<" : "    IGROK 1 (OZhIDAET)    ");
        drawSingleGrid(p1Field, p1CursorY, p1CursorX, true, false, 0, true, true, currentPlayer == 1, 0, 1);

        drawDivider();

        setColor(currentPlayer == 2 ? lightred : darkgray, black); setCursor(42, 0);
        std::cout << (currentPlayer == 2 ? ">>> IGROK 2 (WASx HOD) <<<" : "    IGROK 2 (OZhIDAET)    ");
        drawSingleGrid(p2Field, p2CursorY, p2CursorX, true, false, 0, true, true, currentPlayer == 2, 41, 1);

        setColor(darkgray, black); setCursor(2, 23);
        std::cout << "P1: WASD+SHIFT | P2: Strelki+ENTER | ESC - vyhod";

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
                    showMessage("Uzhe streljli!", yellow, 22); Sleep(800); clearRow(22);
                } else if (p2Field[ey][ex] == CELL_SHIP) {
                    p2Field[ey][ex] = CELL_HIT; flashHit(ey, ex, 41, 1);
                    showMessage("IGROK 1 - POPADANIE!", lightgreen, 22);
                    playSound(1200, 150); Sleep(500); clearRow(22);
                    if (allShipsDestroyed(p2Field)) { showVictoryScreen("IGROK 1"); _getch(); return true; }
                } else {
                    p2Field[ey][ex] = CELL_MISS; flashMiss(ey, ex, 41, 1);
                    showMessage("IGROK 1 - MIMO...", cyan, 22);
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
                    showMessage("Uzhe streljli!", yellow, 22); Sleep(800); clearRow(22);
                } else if (p1Field[ey][ex] == CELL_SHIP) {
                    p1Field[ey][ex] = CELL_HIT; flashHit(ey, ex, 0, 1);
                    showMessage("IGROK 2 - POPADANIE!", lightred, 22);
                    playSound(1200, 150); Sleep(500); clearRow(22);
                    if (allShipsDestroyed(p1Field)) { showVictoryScreen("IGROK 2"); _getch(); return false; }
                } else {
                    p1Field[ey][ex] = CELL_MISS; flashMiss(ey, ex, 0, 1);
                    showMessage("IGROK 2 - MIMO...", cyan, 22);
                    playSound(400, 300); Sleep(500); clearRow(22); currentPlayer = 1;
                }
            }
        }
    }
}
