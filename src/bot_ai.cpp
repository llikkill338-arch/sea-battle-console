// ============================================================================
// bot_ai.cpp — Реализация ИИ бота
// ============================================================================

#include "bot_ai.h"
#include <cstdlib>
#include <vector>

static bool inBounds(int y, int x) {
    return (y >= 0 && y < R && x >= 0 && x < R);
}

static void resetHunt(bool& inHuntMode, int& firstHitY, int& firstHitX,
    int& lastHitY, int& lastHitX, int& huntDir, bool triedDir[4]) {
    inHuntMode = false;
    firstHitY = firstHitX = -1;
    lastHitY = lastHitX = -1;
    huntDir = 0;
    for (int i = 0; i < 4; i++) triedDir[i] = false;
}

static int countHits(int grid[R][R]) {
    int hits = 0;
    for (int y = 0; y < R; y++) {
        for (int x = 0; x < R; x++) {
            if (grid[y][x] == CELL_HIT) hits++;
        }
    }
    return hits;
}

static void pickCheckerboard(int grid[R][R], int& by, int& bx) {
    std::vector<std::pair<int, int>> cells;
    for (int y = 0; y < R; y++) {
        for (int x = 0; x < R; x++) {
            if (grid[y][x] == CELL_WATER && (y + x) % 2 == 0) {
                cells.push_back({y, x});
            }
        }
    }
    if (!cells.empty()) {
        int idx = rand() % cells.size();
        by = cells[idx].first;
        bx = cells[idx].second;
    } else {
        std::vector<std::pair<int, int>> allWater;
        for (int y = 0; y < R; y++) {
            for (int x = 0; x < R; x++) {
                if (grid[y][x] == CELL_WATER) {
                    allWater.push_back({y, x});
                }
            }
        }
        if (!allWater.empty()) {
            int idx = rand() % allWater.size();
            by = allWater[idx].first;
            bx = allWater[idx].second;
        }
    }
}

static bool allDirectionsTried(bool triedDir[4]) {
    return triedDir[0] && triedDir[1] && triedDir[2] && triedDir[3];
}

static void getDirOffset(int dir, int& dy, int& dx) {
    switch (dir) {
        case 0: dy = -1; dx = 0; break;
        case 1: dy = 0; dx = 1; break;
        case 2: dy = 1; dx = 0; break;
        case 3: dy = 0; dx = -1; break;
        default: dy = 0; dx = 0;
    }
}

void botEasyMove(int grid[R][R], int& by, int& bx) {
    std::vector<std::pair<int, int>> waterCells;
    for (int y = 0; y < R; y++) {
        for (int x = 0; x < R; x++) {
            if (grid[y][x] == CELL_WATER) {
                waterCells.push_back({y, x});
            }
        }
    }
    if (!waterCells.empty()) {
        int idx = rand() % waterCells.size();
        by = waterCells[idx].first;
        bx = waterCells[idx].second;
    } else {
        by = -1; bx = -1;
    }
}

void botSmartMove(int grid[R][R], int& by, int& bx) {
    static bool inHuntMode = false;
    static int firstHitY = -1, firstHitX = -1;
    static int lastHitY = -1, lastHitX = -1;
    static int huntDir = 0;
    static bool triedDir[4] = {false, false, false, false};
    static int prevHitCount = 0;

    int currentHits = countHits(grid);
    bool lastWasHit = (currentHits > prevHitCount);
    prevHitCount = currentHits;

    if (lastWasHit && !inHuntMode) {
        inHuntMode = true;
        firstHitY = lastHitY;
        firstHitX = lastHitX;
        huntDir = 0;
        for (int i = 0; i < 4; i++) triedDir[i] = false;
    }

    if (inHuntMode) {
        if (lastWasHit && lastHitY >= 0) {
            int dy, dx;
            getDirOffset(huntDir, dy, dx);
            int ny = lastHitY + dy;
            int nx = lastHitX + dx;
            if (inBounds(ny, nx) && grid[ny][nx] == CELL_WATER) {
                by = ny; bx = nx;
                return;
            }
            triedDir[huntDir] = true;
        }

        for (int attempts = 0; attempts < 4; attempts++) {
            int dy, dx;
            getDirOffset(huntDir, dy, dx);
            int ny = firstHitY + dy;
            int nx = firstHitX + dx;

            if (!triedDir[huntDir] && inBounds(ny, nx) && grid[ny][nx] == CELL_WATER) {
                by = ny; bx = nx;
                lastHitY = ny;
                lastHitX = nx;
                return;
            }

            triedDir[huntDir] = true;
            huntDir = (huntDir + 1) % 4;
        }

        if (allDirectionsTried(triedDir)) {
            resetHunt(inHuntMode, firstHitY, firstHitX, lastHitY, lastHitX, huntDir, triedDir);
        }
    }

    pickCheckerboard(grid, by, bx);
    lastHitY = by;
    lastHitX = bx;
}
