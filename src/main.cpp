// ============================================================================
// main.cpp — Точка входа в игру «Морской бой: Консольный Бой»
// Ретро-стилистика 80-х, C++ / WinAPI
// ============================================================================

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include "utils.h"
#include "graphics.h"
#include "game_logic.h"
#include "screens.h"

// --- Определение глобальных переменных ---

int main() {
    // Установка размера консоли 80x25
    system("mode con cols=80 lines=25");

    // Кодировка UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Инициализация генератора случайных чисел
    srand((unsigned)time(NULL));

    // Скрытие мигающего курсора
    hideCursor();

    // Игровые поля
    int field1[R][R], field2[R][R];
    int fog1[R][R], fog2[R][R];

    // Показать заставку
    showLogo();

    // Главный цикл
    int selected = 0;
    bool running = true;

    while (running) {
        showMainMenu(selected);

        switch (selected) {
            case 0: {
                system("cls");
                int botLevel = 0;
                bool autoP1 = false;
                int settingSel = 0;
                const char* levelNames[] = { "\xCB\xC5\xC3\xCA\xC8\xC9  ", "\xD1\xCB\xCE\xC6\xCD\xDB\xC9  " };
                const char* placeNames[] = { "\xC2\xD0\xD3\xD7\xD3\xDE\xD3  ", "\xC0\xC2\xD2\xCE\xCC\xC0\xD2  " };

                while (true) {
                    system("cls");
                    drawBox(18, 4, 40, 10, yellow);

                    setColor(yellow, black);
                    setCursor(26, 5);
                    std::cout << "=== \xCD\xC0\xD1\xD2\xD0\xCE\xC9\xCA\xC8 \xC1\xCE\xDF ===";

                    setCursor(22, 7);
                    if (settingSel == 0) setColor(black, yellow);
                    else setColor(white, black);
                    std::cout << "\xD1\xEB\xEE\xE6\xED\xEE\xF1\xF2\xFC: [" << levelNames[botLevel] << "]";

                    setCursor(22, 8);
                    if (settingSel == 1) setColor(black, yellow);
                    else setColor(white, black);
                    std::cout << "\xD0\xE0\xF1\xF1\xF2\xE0\xED\xEE\xE2\xEA\xE0: [" << placeNames[autoP1 ? 1 : 0] << "]";

                    setCursor(22, 9);
                    if (settingSel == 2) setColor(black, yellow);
                    else setColor(white, black);
                    std::cout << "[ \xCD\xC0\xDE\xC0\xD2\xDC \xC1\xCE\xC9 ]";

                    setCursor(22, 10);
                    if (settingSel == 3) setColor(black, yellow);
                    else setColor(white, black);
                    std::cout << "[ \xCD\xC0\xC7\xC0\xC4 ]";

                    setColor(darkgray, black);
                    setCursor(2, 23);
                    std::cout << "\x18\x19 - \xE2\xFB\xE1\xEE\xF0 | \x1B\x1A - \xE8\xE7\xEC\xE5\xED\xE5\xED\xE8\xE5 | ENTER - \xEF\xEE\xE4\xF2\xE2\xE5\xF0\xE4\xE8\xF2\xFC | ESC - \xED\xE0\xE7\xE0\xE4";

                    int key = _getch();
                    if (key == 224) {
                        key = _getch();
                        switch (key) {
                            case 72: settingSel = (settingSel - 1 + 4) % 4; break;
                            case 80: settingSel = (settingSel + 1) % 4; break;
                            case 75: case 77:
                                if (settingSel == 0) botLevel = 1 - botLevel;
                                if (settingSel == 1) autoP1 = !autoP1;
                                break;
                        }
                    } else if (key == 13) {
                        if (settingSel == 2) {
                            clearField(field1);
                            clearField(field2);
                            clearField(fog1);
                            clearField(fog2);
                            playBotMode(field1, field2, botLevel, autoP1);
                            break;
                        } else if (settingSel == 3) {
                            break;
                        }
                    } else if (key == 27) {
                        break;
                    }
                }
                break;
            }
            case 1: {
                clearField(field1);
                clearField(field2);
                clearField(fog1);
                clearField(fog2);
                playPVP_TurnMode(field1, field2, fog1, fog2);
                break;
            }
            case 2: {
                clearField(field1);
                clearField(field2);
                clearField(fog1);
                clearField(fog2);
                playPVP_SplitMode(field1, field2, fog1, fog2);
                break;
            }
            case 3:
                showSoundSettings();
                break;
            case 4:
                showRules();
                break;
            case 5:
                running = false;
                break;
        }
    }

    system("cls");
    setColor(lightcyan, black);
    setCursor(25, 12);
    std::cout << "\xD1\xEF\xE0\xF1\xE8\xE1\xEE \xE7\xE0 \xE8\xE3\xF0\xF3!";
    setCursor(25, 14);
    std::cout << "\xCC\xCE\xD0\xD1\xCA\xCE\xC9 \xC1\xCE\xC9 v1.0";
    Sleep(500);

    return 0;
}
