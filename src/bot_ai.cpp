// ============================================================================
// bot_ai.cpp - ИИ бота (легкий и сложный)
// ============================================================================

#include "bot_ai.h"
#include <cstdlib>

static int cel = 0, boty = 0, botx = 0, firsty = 0, firstx = 0;

void botEasyMove(int grid[R][R], int& by, int& bx) {
    do {
        by = rand() % R;
        bx = rand() % R;
    } while (grid[by][bx] > CELL_SHIP);
    if (grid[by][bx] == CELL_SHIP) grid[by][bx] = CELL_HIT;
    else grid[by][bx] = CELL_MISS;
}

void botSmartMove(int grid[R][R], int& by, int& bx) {
    if (cel == 0) {
        do {
            boty = rand() % R;
            botx = rand() % R;
        } while (grid[boty][botx] > CELL_SHIP);
        by = boty; bx = botx;
        if (grid[boty][botx] == CELL_SHIP) {
            grid[boty][botx] = CELL_HIT;
            cel = 1;
            firstx = botx; firsty = boty;
        } else {
            grid[boty][botx] = CELL_MISS;
        }
    } else {
        bool hit = false;
        if (!hit && boty + 1 < R && grid[boty + 1][botx] == CELL_SHIP) {
            grid[boty + 1][botx] = CELL_HIT; boty++; hit = true;
        }
        if (!hit && boty - 1 >= 0 && grid[boty - 1][botx] == CELL_SHIP) {
            grid[boty - 1][botx] = CELL_HIT; boty--; hit = true;
        }
        if (!hit && botx - 1 >= 0 && grid[boty][botx - 1] == CELL_SHIP) {
            grid[boty][botx - 1] = CELL_HIT; botx--; hit = true;
        }
        if (!hit && botx + 1 < R && grid[boty][botx + 1] == CELL_SHIP) {
            grid[boty][botx + 1] = CELL_HIT; botx++; hit = true;
        }
        if (!hit) {
            if (boty != firsty || botx != firstx) { boty = firsty; botx = firstx; }
            else { cel = 0; }
        }
        by = boty; bx = botx;
    }
}

void resetBot() {
    cel = 0; boty = 0; botx = 0; firsty = 0; firstx = 0;
}
