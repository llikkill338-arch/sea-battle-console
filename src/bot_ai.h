// ============================================================================
// bot_ai.h - ИИ бота
// ============================================================================

#ifndef BOT_AI_H
#define BOT_AI_H

#include "utils.h"

void botEasyMove(int grid[R][R], int& by, int& bx);
void botSmartMove(int grid[R][R], int& by, int& bx);
void resetBot();

#endif
