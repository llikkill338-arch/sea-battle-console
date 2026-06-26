// ============================================================================
// graphics.h — Графика и пользовательский интерфейс
// Модуль: цвета, курсор, рамки, отрисовка полей, анимации
// ============================================================================

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "utils.h"
#include <string>

// --- Базовые функции консоли ---

/** Установка цвета текста и фона */
void setColor(Color text, Color background);

/** Позиционирование курсора в указанные координаты */
void setCursor(int x, int y);

/** Скрытие мигающего курсора консоли */
void hideCursor();

// --- Рисование рамок и линий ---

/** Рисование прямоугольной рамки псевдографикой */
void drawBox(int x, int y, int w, int h, Color borderColor);

/** Рисование линии символами псевдографики */
void drawLine(int x, int y, int len, bool horizontal, Color color);

/** Рисование вертикального разделителя экрана */
void drawDivider();

// --- Отрисовка клеток и полей ---

/**
 * Отрисовка одной клетки поля (3 символа шириной).
 * @param val — значение клетки (CELL_WATER/SHIP/MISS/HIT)
 * @param isCursor — клетка под прицелом
 * @param showShips — показывать корабли
 * @param isGhost — призрачный корабль
 * @param isValid — валидность размещения (для ghost)
 */
void drawCell(int val, bool isCursor, bool showShips, bool isGhost, bool isValid);

/**
 * Отрисовка полного поля 10x10 с рамкой и координатами.
 */
void drawSingleGrid(int field[R][R], int cursorY, int cursorX, bool showShips,
    bool showFleet, int ghostSize, bool ghostDir, bool isValid,
    bool showCrosshair, int offsetX, int offsetY);

// --- Анимации и эффекты ---

/** Анимация попадания (взрыв) */
void flashHit(int hy, int hx, int offsetX, int offsetY);

/** Анимация промаха (затухание) */
void flashMiss(int my, int mx, int offsetX, int offsetY);

/** Пульсация воды на поле */
void pulseWater(int offsetX, int offsetY);

#endif // GRAPHICS_H
