// ============================================================================
// Constants.hpp - PIRATE v7.0 - All colors are pirate-themed
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>

// --- Размеры ---
const int BOARD_SIZE = 10;
const int CELL_SIZE = 48;
const int CELL_MARGIN = 2;
const int BOARD_PIXELS = BOARD_SIZE * (CELL_SIZE + CELL_MARGIN);

// --- Окно ---
const int WINDOW_WIDTH = 1100;
const int WINDOW_HEIGHT = 750;
#define WINDOW_TITLE "Morskoj Boj - PIRATE v7.0"

// --- Пиратская палитра (старая карта, дерево, ром, золото, кровь) ---
namespace Colors {
    // Вода - глубокое тёмное море
    const sf::Color WATER      (25,  55,  85);
    const sf::Color WATER_DARK (18,  42,  65);

    // Дощатый настил палубы
    const sf::Color DECK       (101, 67,  33);
    const sf::Color DECK_LIGHT (125, 85,  42);
    const sf::Color DECK_DARK  (78,  52,  26);

    // Корабль - тёмное дерево с гвоздями
    const sf::Color SHIP       (80,  50,  25);
    const sf::Color SHIP_HIT   (160, 40,  20);

    // Попадание - кроваво-красный
    const sf::Color HIT        (200, 35,  35);
    const sf::Color HIT_CROSS  (230, 200, 150);

    // Промах - старая пуля/песок
    const sf::Color MISS       (160, 140, 100);
    const sf::Color MISS_DOT   (120, 105, 75);

    // Курсор - пылающий факел
    const sf::Color CURSOR     (255, 160, 40);

    // Рамка сетки - бронзовая
    const sf::Color GRID_LINE  (140, 110, 60);

    // Фон - старая карта / пергамент тёмный
    const sf::Color BG         (35,  28,  18);
    const sf::Color BG_MAP     (45,  38,  25);

    // Панель - кожа/пергамент
    const sf::Color PANEL_BG   (55,  45,  30);
    const sf::Color PANEL_BORDER(120, 95, 55);

    // Текст - пергаментный белый
    const sf::Color TEXT       (220, 205, 175);
    const sf::Color TEXT_GOLD  (230, 190, 65);
    const sf::Color TEXT_RUM   (160, 100, 45);

    // Призрак корабля
    const sf::Color GHOST_OK   (60,  160, 60);
    const sf::Color GHOST_BAD  (180, 40,  40);

    // Кнопки - деревянные
    const sf::Color BUTTON      (90,  60,  30);
    const sf::Color BUTTON_HOVER(120, 80,  40);
    const sf::Color BUTTON_TEXT (230, 210, 170);

    // Пиратский флаг
    const sf::Color BLACK_FLAG  (15,  15,  15);
    const sf::Color BONE_WHITE  (210, 200, 185);
}

// --- Флот ---
const int FLEET_COUNT = 10;
const int FLEET_SIZES[FLEET_COUNT] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

// --- Задержки ---
const float ANIMATION_SPEED = 0.15f;
const float BOT_THINK_DELAY = 0.8f;
