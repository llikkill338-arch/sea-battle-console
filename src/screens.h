// ============================================================================
// screens.h — Экраны и игровые режимы
// Модуль: меню, заставка, настройки, игровые циклы
// ============================================================================

#ifndef SCREENS_H
#define SCREENS_H

#include "utils.h"
#include "graphics.h"
#include "game_logic.h"
#include "bot_ai.h"
#include <string>

/** Заставка с ASCII-арт логотипом и анимацией загрузки */
void showLogo();

/** Главное меню: устанавливает selected в индекс выбранного пункта (0-5) */
void showMainMenu(int& selected);

/** Экран правил / Об игре */
void showRules();

/** Настройки звука */
void showSoundSettings();

/** Подтверждение выхода: true если пользователь подтвердил */
bool confirmExit();

/** Экран передачи хода с 3-секундным обратным отсчётом */
void switchScreenWithTimer(const std::string& nextPlayerName);

/** Показать сообщение на экране в указанной строке */
void showMessage(const std::string& text, Color color, int row);

/** Экран победы */
void showVictoryScreen(const std::string& winner);

/** Экран поражения */
void showDefeatScreen(const std::string& loser);

/** Режим "Бой с ботом". botLevel: 0 = лёгкий, 1 = сложный */
bool playBotMode(int field1[R][R], int field2[R][R], int botLevel, bool autoPlaceP1);

/** Режим "1 на 1 по очереди" */
bool playPVP_TurnMode(int p1Field[R][R], int p2Field[R][R], int p1Fog[R][R], int p2Fog[R][R]);

/** Режим "1 на 1 разделённый экран" */
bool playPVP_SplitMode(int p1Field[R][R], int p2Field[R][R], int p1Fog[R][R], int p2Fog[R][R]);

#endif // SCREENS_H
