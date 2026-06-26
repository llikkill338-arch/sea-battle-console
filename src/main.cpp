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
#include <clocale>

int main() {
    system("mode con cols=80 lines=25");

    srand((unsigned)time(NULL));
    hideCursor();

    int field1[10][10], field2[10][10];
    int fog1[10][10], fog2[10][10];

    showLogo();

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
                const char* levelNames[] = { "\x8B\xF0\x83\x8A\x88\x89  ", "\x91\x8B\x8E\x86\x8D\x9B\x89  " };
                const char* placeNames[] = { "\x82\x90\x93\x97\x8D\x93\x9E  ", "\x80\x82\x92\x8E\x8C\x80\x92  " };

                while (true) {
                    system("cls");
                    drawBox(18, 4, 40, 10, yellow);

                    setColor(yellow, black);
                    setCursor(26, 5);
                    std::cout << "=== \x8D\x80\x91\x92\x90\x8E\x89\x8A\x88 \x81\x8E\x9F ===";

                    setCursor(22, 7);
                    if (settingSel == 0) setColor(black, yellow);
                    else setColor(white, black);
                    std::cout << "\x91\xAB\xAE\xA6\xAD\xAE\xE1\xE2\xEC: [" << levelNames[botLevel] << "]";

                    setCursor(22, 8);
                    if (settingSel == 1) setColor(black, yellow);
                    else setColor(white, black);
                    std::cout << "\x90\xA0\xE1\xE2\xA0\xAD\xAE\xA2\xAA\xA0: [" << placeNames[autoP1 ? 1 : 0] << "]";

                    setCursor(22, 9);
                    if (settingSel == 2) setColor(black, yellow);
                    else setColor(white, black);
                    std::cout << "[ \x8D\x80\x97\x80\x92\x9C \x81\x8E\x89 ]";

                    setCursor(22, 10);
                    if (settingSel == 3) setColor(black, yellow);
                    else setColor(white, black);
                    std::cout << "[ \x8D\x80\x87\x80\x84 ]";

                    setColor(darkgray, black);
                    setCursor(2, 23);
                    std::cout << "\x18\x19 - \xA2\xEB\xA1\xAE\xE0 | \x1B\x1A - \xA8\xA7\xAC\xA5\xAD\xA5\xAD\xA8\xA5 | ENTER - \xAF\xAE\xA4\xE2\xA2\xA5\xE0\xA4\xA8\xE2\xEC | ESC - \xAD\xA0\xA7\xA0\xA4";

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
                            clearField(field1); clearField(field2);
                            clearField(fog1); clearField(fog2);
                            playBotMode(field1, field2, botLevel, autoP1);
                            break;
                        } else if (settingSel == 3) break;
                    } else if (key == 27) break;
                }
                break;
            }
            case 1: {
                clearField(field1); clearField(field2);
                clearField(fog1); clearField(fog2);
                playPVP_TurnMode(field1, field2, fog1, fog2);
                break;
            }
            case 2: {
                clearField(field1); clearField(field2);
                clearField(fog1); clearField(fog2);
                playPVP_SplitMode(field1, field2, fog1, fog2);
                break;
            }
            case 3: showSoundSettings(); break;
            case 4: showRules(); break;
            case 5: running = false; break;
        }
    }

    system("cls");
    setColor(lightcyan, black);
    setCursor(25, 12);
    std::cout << "\x91\xAF\xA0\xE1\xA8\xA1\xAE \xA7\xA0 \xA8\xA3\xE0\xE3!";
    setCursor(25, 14);
    std::cout << "\x8C\x8E\x90\x91\x8A\x8E\x89 \x81\x8E\x89 v1.0";
    Sleep(500);
    return 0;
}
