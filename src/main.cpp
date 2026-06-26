// ============================================================================
// main.cpp - Точка входа
// ============================================================================

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <clocale>
#include "utils.h"
#include "graphics.h"
#include "game_logic.h"
#include "screens.h"

using namespace std;

int main() {
    // Кодировка UTF-8 для консоли + русская локаль
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "ru");
    srand((unsigned int)time(NULL));

    int f1[R][R], f2[R][R];

    showLogo();

    while (true) {
        clearField(f1);
        clearField(f2);

        int selected = 0;
        int mode = 0;

        // Главное меню
        while (true) {
            showMainMenu(selected);
            int kn = _getch();
            if (kn == 224) {
                kn = _getch();
                if (kn == 72 && selected > 0) selected--;
                if (kn == 80 && selected < 4) selected++;
            }
            else if (kn == 13) { mode = selected; break; }
            else if (kn == 27) { mode = 4; break; }
        }

        // Выход
        if (mode == 4) {
            system("cls");
            setColor(yellow, black);
            cout << "Вы точно хотите выйти? (Y/N): ";
            setColor(white, black);
            int key;
            do {
                key = _getch();
                if (key == 'Y' || key == 'y') {
                    system("cls");
                    setColor(lightcyan, black);
                    setCursor(30, 12);
                    cout << "Спасибо за игру!";
                    setCursor(28, 14);
                    cout << "МОРСКОЙ БОЙ v1.0";
                    Sleep(1000);
                    return 0;
                }
                else if (key == 'N' || key == 'n' || key == 27) break;
            } while (true);
            continue;
        }

        // Правила
        if (mode == 3) { showRules(); continue; }

        // Игровые режимы
        switch (mode) {
            case 0: playBotMode(f1, f2, 0, false); break;
            case 1: playPVPTurn(f1, f2); break;
            case 2: playPVPSplit(f1, f2); break;
        }
    }

    return 0;
}
