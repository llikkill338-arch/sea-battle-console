// ============================================================================
// screens.cpp - Все экраны и игровые режимы
// ============================================================================

#include "screens.h"
#include "bot_ai.h"
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

// --- Вспомогательные функции ---

static void showMessage(const string& text, Color color, int row) {
    setCursor(20, row);
    setColor(color, black);
    cout << " " << text << " ";
    setColor(white, black);
}

static void drawBattleScreen(int myField[R][R], int enemyField[R][R],
    int curY, int curX, const string& title, bool showMy) {

    system("cls");

    setCursor(28, 0);
    setColor(yellow, black);
    cout << "=== " << title << " ===";
    setColor(white, black);
    drawLine(0, 1, 80, true, cyan);

    if (showMy) {
        setCursor(2, 2);
        setColor(lightgreen, black);
        cout << "<<< ВАШЕ ПОЛЕ >>>";
        setColor(white, black);
        drawBox(0, 3, 38, 14, lightgreen);
        drawSingleGrid(myField, -1, -1, true, false, 0, true, true, false, 1, 4);

        setCursor(42, 2);
        setColor(lightred, black);
        cout << "<<< ПОЛЕ ВРАГА >>>";
        setColor(white, black);
        drawBox(42, 3, 38, 14, lightred);
        drawSingleGrid(enemyField, curY, curX, false, false, 0, true, true, true, 43, 4);
    } else {
        setCursor(2, 2);
        setColor(lightred, black);
        cout << "<<< ПОЛЕ ПРОТИВНИКА >>>";
        setColor(white, black);
        drawBox(0, 3, 38, 14, lightred);
        drawSingleGrid(enemyField, curY, curX, false, false, 0, true, true, true, 1, 4);

        setCursor(42, 2);
        setColor(lightgreen, black);
        cout << "<<< ВАШЕ ПОЛЕ >>>";
        setColor(white, black);
        drawBox(42, 3, 38, 14, lightgreen);
        drawSingleGrid(myField, -1, -1, true, false, 0, true, true, false, 43, 4);
    }

    setCursor(0, 18);
    drawLine(0, 18, 80, true, darkgray);
    setCursor(2, 19);
    setColor(darkgray, black);
    cout << "Стрелки - движение | ENTER - выстрел | ESC - меню";
    setCursor(2, 20);
    cout << "Попадание = еще ход | Промах = передача";
    setColor(white, black);
}

// --- Заставка ---

void showLogo() {
    system("cls");
    hideCursor();

    setColor(cyan, black);
    setCursor(15, 3);
    cout << "     ___  ___  ___   _   _ _____ _____ _____ _____ ";
    setCursor(15, 4);
    cout << "    | _ )/ _ \\| _ \\ | | | |_   _|_   _| ____|_   _|";
    setCursor(15, 5);
    cout << "    | _ \\ (_) |   / | |_| | | |   | | |  _|   | |  ";
    setCursor(15, 6);
    cout << "    |___/\\___/|_|_\\  \\___/  |_|   |_| |_____| |_|  ";
    setCursor(15, 7);
    setColor(yellow, black);
    cout << "              К О Н С О Л Ь Н Ы Й   Б О Й";
    setColor(white, black);

    drawBox(10, 2, 60, 8, cyan);

    setCursor(25, 12);
    setColor(darkgray, black);
    cout << "Загрузка системы...";
    for (int i = 0; i < 30; i++) {
        setCursor(25 + i, 13);
        setColor(lightgreen, black);
        cout << char(219);
        Sleep(30);
    }
    setColor(white, black);
    Sleep(500);
}

// --- Главное меню ---

void showMainMenu(int& selected) {
    system("cls");
    hideCursor();

    setColor(cyan, black);
    setCursor(15, 1);
    cout << "     ___  ___  ___   _   _ _____ _____ _____ _____ ";
    setCursor(15, 2);
    cout << "    | _ )/ _ \\| _ \\ | | | |_   _|_   _| ____|_   _|";
    setCursor(15, 3);
    cout << "    | _ \\ (_) |   / | |_| | | |   | | |  _|   | |  ";
    setCursor(15, 4);
    cout << "    |___/\\___/|_|_\\  \\___/  |_|   |_| |_____| |_|  ";
    setCursor(15, 5);
    setColor(yellow, black);
    cout << "              К О Н С О Л Ь Н Ы Й   Б О Й";
    setColor(white, black);

    drawBox(10, 0, 60, 7, cyan);

    string items[] = {
        "1. Бой с ботом",
        "2. Бой 1 на 1 (по очереди)",
        "3. Бой 1 на 1 (разделенный экран)",
        "4. Правила игры",
        "5. Выход"
    };

    for (int i = 0; i < 5; i++) {
        setCursor(28, 10 + i * 2);
        if (i == selected) {
            setColor(black, yellow);
            cout << "  " << items[i] << "  ";
        } else {
            setColor(white, black);
            cout << "   " << items[i] << "   ";
        }
    }
    setColor(white, black);

    setCursor(15, 22);
    setColor(darkgray, black);
    cout << "Стрелки ВВЕРХ/ВНИЗ - выбор | ENTER - подтвердить | ESC - выход";
    setColor(white, black);
}

// --- Правила ---

void showRules() {
    system("cls");
    drawBox(5, 1, 70, 20, cyan);

    setCursor(30, 2);
    setColor(yellow, black);
    cout << "=== ПРАВИЛА ИГРЫ ===";

    const char* rules[] = {
        "",
        "  Цель: потопить весь флот противника.",
        "",
        "  Флот: 10 кораблей",
        "    - 1 четырехпалубный (авианосец)",
        "    - 2 трехпалубных (крейсера)",
        "    - 3 двухпалубных (эсминцы)",
        "    - 4 однопалубных (миноносцы)",
        "",
        "  Управление:",
        "    Стрелки - перемещение",
        "    ENTER   - выстрел / поставить корабль",
        "    ПРОБЕЛ  - поворот корабля",
        "    ESC     - выход",
        "",
        "  При попадании - дополнительный ход.",
        "  Побеждает тот, кто уничтожит флот!"
    };

    for (int i = 0; i < 18; i++) {
        setCursor(8, 4 + i);
        setColor(white, black);
        cout << rules[i];
    }

    setCursor(25, 22);
    setColor(yellow, black);
    cout << "Нажмите любую клавишу...";
    setColor(white, black);
    _getch();
}

// --- Настройки ---

void showSettings(bool& sound) {
    int sel = 0;
    while (true) {
        system("cls");
        drawBox(20, 6, 36, 7, yellow);

        setColor(yellow, black);
        setCursor(26, 7);
        cout << "=== НАСТРОЙКИ ===";

        setCursor(22, 9);
        if (sel == 0) setColor(black, yellow); else setColor(white, black);
        cout << "Звук: " << (sound ? "[ВКЛ]" : "[ВЫКЛ]");

        setCursor(22, 10);
        if (sel == 1) setColor(black, yellow); else setColor(white, black);
        cout << "Тест звука";

        setCursor(22, 11);
        if (sel == 2) setColor(black, yellow); else setColor(white, black);
        cout << "Назад";

        setColor(darkgray, black);
        setCursor(2, 23);
        cout << "^/v - выбор | </> - изменить | ENTER - применить";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: sel = (sel - 1 + 3) % 3; break;
                case 80: sel = (sel + 1) % 3; break;
                case 75: case 77: if (sel == 0) sound = !sound; break;
            }
        } else if (key == 13) {
            if (sel == 0) { /* переключено выше */ }
            else if (sel == 1) {
                playSound(800, 100); playSound(1200, 150); playSound(400, 200);
            }
            else if (sel == 2) return;
        } else if (key == 27) return;
    }
}

// --- Подтверждение выхода ---

void confirmExit() {
    setCursor(20, 22);
    setColor(yellow, black);
    cout << " Вы точно хотите выйти? (Y/N): ";
    setColor(white, black);
    int key;
    do {
        key = _getch();
        if (key == 'Y' || key == 'y') {
            system("cls");
            exit(0);
        }
        else if (key == 'N' || key == 'n' || key == 27) {
            setCursor(20, 22);
            cout << "                                      ";
            return;
        }
    } while (true);
}

// --- Экран передачи хода ---

void switchScreenWithTimer(const string& nextPlayerName) {
    system("cls");
    hideCursor();

    drawBox(20, 6, 40, 12, yellow);
    setCursor(28, 8);
    setColor(yellow, black);
    cout << "=== ПЕРЕДАЧА ХОДА ===";
    setCursor(25, 10);
    setColor(cyan, black);
    cout << "Поменяйтесь местами!";
    setCursor(30, 12);
    setColor(white, black);
    cout << "Следующий ход:";
    setCursor(32, 14);
    setColor(lightgreen, black);
    cout << ">>> " << nextPlayerName << " <<<";
    setColor(white, black);

    for (int i = 3; i >= 1; i--) {
        setCursor(36, 16);
        setColor(lightred, black);
        cout << i;
        setColor(white, black);
        Sleep(1000);
    }
    system("cls");
}

// --- Бой с ботом ---

void playBotMode(int f1[R][R], int f2[R][R], int level, bool autoPlace) {
    // Настройки
    int botLevel = level;
    int pChoice = autoPlace ? 1 : 0;
    int sel = 0;

    while (true) {
        system("cls");
        drawBox(15, 3, 50, 12, cyan);
        setCursor(25, 4);
        setColor(yellow, black);
        cout << "=== НАСТРОЙКИ ===";

        setCursor(20, 6);
        if (sel == 0) { setColor(black, yellow); cout << "> "; }
        else { setColor(white, black); cout << "  "; }
        cout << "СЛОЖНОСТЬ: " << (botLevel == 0 ? "ЛЕГКИЙ  " : "СЛОЖНЫЙ");

        setCursor(20, 8);
        if (sel == 1) { setColor(black, yellow); cout << "> "; }
        else { setColor(white, black); cout << "  "; }
        cout << "КОРАБЛИ: " << (pChoice == 0 ? "ВРУЧНУЮ  " : "АВТОМАТ");

        setCursor(18, 11);
        setColor(darkgray, black);
        cout << "Стрелки - выбор | <-/-> - изменить";
        setCursor(22, 12);
        cout << "ENTER - начать | ESC - назад";
        setColor(white, black);

        int kn = _getch();
        if (kn == 224) {
            kn = _getch();
            if (kn == 72 && sel > 0) sel--;
            if (kn == 80 && sel < 1) sel++;
            if (kn == 75 || kn == 77) {
                if (sel == 0) botLevel = 1 - botLevel;
                if (sel == 1) pChoice = 1 - pChoice;
            }
        } else if (kn == 27) return;
        else if (kn == 13) break;
    }

    // Расстановка
    if (pChoice == 1) autoPlace(f1);
    else stavlyusam(f1, "ИГРОК");
    autoPlace(f2);

    system("cls");
    setCursor(20, 10);
    setColor(lightgreen, black);
    cout << "Корабли расставлены!";
    setCursor(18, 12);
    setColor(white, black);
    cout << "Нажмите ENTER для начала боя...";
    int start;
    do { start = _getch(); } while (start != 13);

    // Бой
    int curY = 0, curX = 0;
    resetBot();

    while (checkAlive(f1) && checkAlive(f2)) {
        // Ход игрока
        int v = 0;
        while (v == 0) {
            drawBattleScreen(f1, f2, curY, curX, "БОЙ С БОТОМ", true);

            int kn = _getch();
            if (kn == 224) {
                kn = _getch();
                if (kn == 72 && curY > 0) curY--;
                if (kn == 80 && curY < R - 1) curY++;
                if (kn == 75 && curX > 0) curX--;
                if (kn == 77 && curX < R - 1) curX++;
            } else if (kn == 27) { confirmExit(); }
            else if (kn == 13) {
                if (f2[curY][curX] == CELL_HIT || f2[curY][curX] == CELL_MISS) {
                    showMessage("Уже стреляли!", yellow, 20);
                    Sleep(600);
                } else if (f2[curY][curX] == CELL_SHIP) {
                    f2[curY][curX] = CELL_HIT;
                    showMessage("БА-БАХ! ПОПАДАНИЕ!", lightred, 20);
                    flashHit(curY, curX, 43, 4);
                    v = 1;
                } else {
                    f2[curY][curX] = CELL_MISS;
                    showMessage("МИМО...", cyan, 20);
                    flashMiss(curY, curX, 43, 4);
                    v = 1;
                }
            }
        }
        if (!checkAlive(f2)) break;

        // Ход бота
        int by = -1, bx = -1;
        if (botLevel == 1) botSmartMove(f1, by, bx);
        else botEasyMove(f1, by, bx);

        if (by >= 0 && bx >= 0) {
            drawBattleScreen(f1, f2, curY, curX, "БОЙ С БОТОМ", true);
            if (f1[by][bx] == CELL_HIT) {
                showMessage("ВАС ПОДБИЛИ!", lightred, 20);
                flashHit(by, bx, 1, 4);
            } else {
                showMessage("Бот промахнулся", cyan, 20);
                Sleep(500);
            }
        }
    }

    // Результат
    system("cls");
    bool botAlive = checkAlive(f2);
    drawBox(20, 6, 40, 8, botAlive ? red : green);
    setCursor(28, 8);
    if (!botAlive) {
        setColor(lightgreen, black);
        cout << "=== ВЫ ПОБЕДИЛИ! ===";
    } else {
        setColor(lightred, black);
        cout << "=== ВЫ ПРОИГРАЛИ ===";
    }
    setCursor(24, 11);
    setColor(white, black);
    cout << "ENTER - играть снова | ESC - выход";
    int key;
    do {
        key = _getch();
        if (key == 27) { confirmExit(); break; }
    } while (key != 13);
}

// --- 1 на 1 по очереди ---

static bool playPVPRound(int myField[R][R], int enemyField[R][R], const string& name) {
    int curY = 0, curX = 0;
    int v = 0;

    while (v == 0) {
        system("cls");
        setCursor(0, 0);
        setColor(yellow, black);
        cout << "=========== ВАШЕ ПОЛЕ (" << name << ") ===========" << endl;
        setColor(white, black);
        drawSingleGrid(myField, -1, -1, true, false, 0, true, true, false, 1, 1);
        cout << endl;
        setColor(lightred, black);
        cout << "=========== ПОЛЕ ПРОТИВНИКА ===========" << endl;
        setColor(white, black);
        drawSingleGrid(enemyField, curY, curX, false, false, 0, true, true, true, 1, 13);

        setCursor(0, R * 2 + 5);
        cout << name << ": Стрелки | ENTER | ESC";

        int kn = _getch();
        if (kn == 224) {
            kn = _getch();
            if (kn == 72 && curY > 0) curY--;
            if (kn == 80 && curY < R - 1) curY++;
            if (kn == 75 && curX > 0) curX--;
            if (kn == 77 && curX < R - 1) curX++;
        } else if (kn == 27) { confirmExit(); }
        else if (kn == 13) {
            if (enemyField[curY][curX] == CELL_SHIP) {
                enemyField[curY][curX] = CELL_HIT;
                showMessage("БА-БАХ! ПОПАДАНИЕ!", lightred, R + 2);
                flashHit(curY, curX, 1, 13);
                v = 1;
            } else if (enemyField[curY][curX] == CELL_WATER) {
                enemyField[curY][curX] = CELL_MISS;
                showMessage("МИМО...", cyan, R + 2);
                Sleep(500);
                v = 1;
            } else {
                setColor(red, black);
                setCursor(0, R * 2 + 6);
                cout << "Уже стреляли! Выберите другую.";
                Sleep(600);
            }
        }
    }
    return checkAlive(enemyField);
}

void playPVPTurn(int f1[R][R], int f2[R][R]) {
    stavlyusam(f1, "ИГРОК 1");
    switchScreenWithTimer("ИГРОК 2");
    stavlyusam(f2, "ИГРОК 2");
    system("cls");

    setCursor(20, 10);
    setColor(lightgreen, black);
    cout << "Корабли расставлены!";
    setCursor(18, 12);
    setColor(white, black);
    cout << "Нажмите ENTER для начала боя...";
    int start;
    do { start = _getch(); } while (start != 13);

    bool p1Alive = true, p2Alive = true;
    bool turnP1 = true;

    while (p1Alive && p2Alive) {
        if (turnP1) {
            p2Alive = playPVPRound(f1, f2, "ИГРОК 1");
            if (!p2Alive) break;
            switchScreenWithTimer("ИГРОК 2");
            turnP1 = false;
        } else {
            p1Alive = playPVPRound(f2, f1, "ИГРОК 2");
            if (!p1Alive) break;
            switchScreenWithTimer("ИГРОК 1");
            turnP1 = true;
        }
    }

    system("cls");
    drawBox(20, 6, 40, 8, p1Alive ? green : red);
    setCursor(26, 8);
    if (p1Alive) {
        setColor(lightgreen, black);
        cout << "=== ПОБЕДИЛ ИГРОК 1 ===";
    } else {
        setColor(lightred, black);
        cout << "=== ПОБЕДИЛ ИГРОК 2 ===";
    }
    setCursor(24, 11);
    setColor(white, black);
    cout << "ENTER - играть снова | ESC - выход";
    int key;
    do {
        key = _getch();
        if (key == 27) { confirmExit(); break; }
    } while (key != 13);
}

// --- Разделенный экран ---

static void drawSplitScreen(int p1Field[R][R], int p2Field[R][R], bool p1Turn) {
    system("cls");

    setCursor(28, 0);
    setColor(yellow, black);
    cout << "=== М О Р С К О Й   Б О Й ===";
    setColor(white, black);
    drawLine(0, 1, 80, true, cyan);

    setCursor(8, 2);
    setColor(lightgreen, black);
    if (p1Turn) cout << ">>> ИГРОК 1 (ВАШ ХОД) <<<";
    else        cout << "    ИГРОК 1 (ОЖИДАЕТ)    ";
    setColor(white, black);
    drawBox(0, 3, 38, 14, lightgreen);
    drawSingleGrid(p1Field, -1, -1, true, false, 0, true, true, false, 1, 4);

    setCursor(48, 2);
    setColor(lightred, black);
    if (!p1Turn) cout << ">>> ИГРОК 2 (ВАШ ХОД) <<<";
    else         cout << "    ИГРОК 2 (ОЖИДАЕТ)    ";
    setColor(white, black);
    drawBox(42, 3, 38, 14, lightred);
    drawSingleGrid(p2Field, -1, -1, true, false, 0, true, true, false, 43, 4);

    drawDivider();

    setCursor(0, 18);
    drawLine(0, 18, 80, true, darkgray);
    setCursor(2, 19);
    setColor(darkgray, black);
    cout << "Стрелки - движение | ENTER - выстрел | ESC - меню";
    setCursor(2, 20);
    cout << "Попадание = еще ход | Промах = передача";
    setColor(white, black);
}

static bool playSplitRound(int p1Field[R][R], int p2Field[R][R],
    int p1Fog[R][R], int p2Fog[R][R], bool& p1Turn) {

    int curY = 0, curX = 0;
    int v = 0;
    string name = p1Turn ? "ИГРОК 1" : "ИГРОК 2";
    int offsetX = p1Turn ? 43 : 1;

    while (v == 0) {
        drawSplitScreen(p1Field, p2Field, p1Turn);

        // Прицел
        setCursor(offsetX + curX * 3 + 3, 5 + curY);
        setColor(yellow, black);
        cout << "[";
        setColor(red, black);
        cout << "+";
        setColor(yellow, black);
        cout << "]";
        setColor(white, black);

        setCursor(25, 22);
        setColor(lightcyan, black);
        cout << name << ", выберите цель и нажмите ENTER";
        setColor(white, black);

        int kn = _getch();
        if (kn == 224) {
            kn = _getch();
            if (kn == 72 && curY > 0) curY--;
            if (kn == 80 && curY < R - 1) curY++;
            if (kn == 75 && curX > 0) curX--;
            if (kn == 77 && curX < R - 1) curX++;
        } else if (kn == 27) { confirmExit(); }
        else if (kn == 13) {
            if (p1Turn) {
                if (p2Fog[curY][curX] != 0) {
                    showMessage("Уже стреляли!", yellow, 22);
                    Sleep(800);
                } else if (p2Field[curY][curX] == CELL_SHIP) {
                    p2Field[curY][curX] = CELL_HIT;
                    p2Fog[curY][curX] = CELL_HIT;
                    flashHit(curY, curX, 43, 4);
                    showMessage("БА-БАХ! ПОПАДАНИЕ!", lightred, 22);
                    playSound(1200, 200);
                    Sleep(500);
                    v = 1;
                } else {
                    p2Field[curY][curX] = CELL_MISS;
                    p2Fog[curY][curX] = CELL_MISS;
                    showMessage("МИМО...", cyan, 22);
                    Sleep(600);
                    v = 1; p1Turn = !p1Turn;
                }
            } else {
                if (p1Fog[curY][curX] != 0) {
                    showMessage("Уже стреляли!", yellow, 22);
                    Sleep(800);
                } else if (p1Field[curY][curX] == CELL_SHIP) {
                    p1Field[curY][curX] = CELL_HIT;
                    p1Fog[curY][curX] = CELL_HIT;
                    flashHit(curY, curX, 1, 4);
                    showMessage("БА-БАХ! ПОПАДАНИЕ!", lightred, 22);
                    playSound(1200, 200);
                    Sleep(500);
                    v = 1;
                } else {
                    p1Field[curY][curX] = CELL_MISS;
                    p1Fog[curY][curX] = CELL_MISS;
                    showMessage("МИМО...", cyan, 22);
                    Sleep(600);
                    v = 1; p1Turn = !p1Turn;
                }
            }
        }
    }
    return p1Turn ? checkAlive(p2Field) : checkAlive(p1Field);
}

void playPVPSplit(int f1[R][R], int f2[R][R]) {
    // Инструкция
    system("cls");
    drawBox(10, 5, 60, 10, yellow);
    setCursor(20, 7);
    setColor(yellow, black);
    cout << "=== РЕЖИМ: РАЗДЕЛЕННЫЙ ЭКРАН ===";
    setCursor(15, 9);
    setColor(white, black);
    cout << "ИГРОК 1 (слева) vs ИГРОК 2 (справа)";
    setCursor(12, 11);
    setColor(cyan, black);
    cout << "Поставьте книгу по центру экрана!";
    setCursor(15, 13);
    setColor(darkgray, black);
    cout << "Нажмите ENTER для продолжения...";
    int start;
    do { start = _getch(); } while (start != 13);

    // Расстановка
    system("cls");
    setCursor(5, 10);
    setColor(lightgreen, black);
    cout << "ИГРОК 1: Расставьте корабли";
    Sleep(1000);
    stavlyusam(f1, "ИГРОК 1");

    system("cls");
    setCursor(5, 10);
    setColor(lightred, black);
    cout << "ИГРОК 2: Расставьте корабли";
    Sleep(1000);
    stavlyusam(f2, "ИГРОК 2");

    system("cls");
    drawBox(10, 8, 60, 6, green);
    setCursor(22, 10);
    setColor(lightgreen, black);
    cout << "К О Р А Б Л И   Р А С С Т А В Л Е Н Ы !";
    setCursor(18, 12);
    setColor(white, black);
    cout << "Нажмите ENTER для начала боя...";
    do { start = _getch(); } while (start != 13);

    // Бой
    bool p1Alive = true, p2Alive = true;
    bool p1Turn = true;
    int fog1[R][R] = {}, fog2[R][R] = {};

    while (p1Alive && p2Alive) {
        bool enemyAlive = playSplitRound(f1, f2, fog1, fog2, p1Turn);
        if (p1Turn) p2Alive = enemyAlive;
        else p1Alive = enemyAlive;
    }

    system("cls");
    drawBox(20, 6, 40, 8, p1Alive ? green : red);
    setCursor(26, 8);
    if (p1Alive) {
        setColor(lightgreen, black);
        cout << "=== ПОБЕДИЛ ИГРОК 1 ===";
    } else {
        setColor(lightred, black);
        cout << "=== ПОБЕДИЛ ИГРОК 2 ===";
    }
    setCursor(24, 11);
    setColor(white, black);
    cout << "ENTER - играть снова | ESC - выход";
    int key;
    do {
        key = _getch();
        if (key == 27) { confirmExit(); break; }
    } while (key != 13);
}
