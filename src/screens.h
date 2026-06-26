// ============================================================================
// screens.h - Все экраны и игровые режимы
// ============================================================================

#ifndef SCREENS_H
#define SCREENS_H

#include "utils.h"
#include "graphics.h"
#include "game_logic.h"

void showLogo();
void showMainMenu(int& selected);
void showRules();
void showSettings(bool& sound);
void confirmExit();
void switchScreenWithTimer(const std::string& nextPlayerName);

// Режимы
void playBotMode(int f1[R][R], int f2[R][R], int level, bool autoPlace);
void playPVPTurn(int f1[R][R], int f2[R][R]);
void playPVPSplit(int f1[R][R], int f2[R][R]);

#endif
