// ============================================================================
// game_logic.h — Логика игры
// Модуль: поля, корабли, проверки, расстановка
// ============================================================================

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "utils.h"
#include <vector>
#include <string>

// --- Флот кораблей ---
static const int FLEET[FLEET_SIZE] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

// --- Функции работы с полем ---

/** Очистка поля — заполнение водой */
void clearField(int grid[R][R]);

/** Проверка возможности размещения корабля (без касания углами) */
bool canPlace(int grid[R][R], int y, int x, int size, bool horizontal);

/** Размещение корабля на поле */
void placeShip(int grid[R][R], int y, int x, int size, bool horizontal);

/** Проверка наличия живых кораблей на поле */
bool checkAlive(int grid[R][R]);

/** Автоматическая случайная расстановка кораблей */
void autoPlace(int grid[R][R]);

/** Ручная расстановка кораблей игроком */
void stavlyusam(int field[R][R], const std::string& playerName);

#endif // GAME_LOGIC_H
