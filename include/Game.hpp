// ============================================================================
// Game.hpp - v7.0 + Hotseat & Split-screen 1v1 modes
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Board.hpp"

enum class GameState {
    Menu, Settings, Rules,
    Placement, P2Placement,   // P1 places ships, then P2 (hotseat/split)
    SwitchScreen,             // "Pass to other player" 3-sec screen
    Battle, BotTurn,          // VsBot: P1 plays, Bot plays
    P1Turn, P2Turn,           // 1v1 modes: P1 shoots, P2 shoots
    SplitscreenBattle,        // Split-screen: both boards visible
    P1Victory, P2Victory,     // 1v1: specific player wins
    Victory, Defeat, Exit     // VsBot results
};

enum class GameMode {
    None, VsBot, Hotseat, Splitscreen
};

struct BattleMessage {
    std::string text;
    float timer;
    sf::Color color;
};

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    GameState state;
    GameMode  gameMode;

    // Boards: player1 (left/top), player2 (right/bottom)
    std::unique_ptr<Board> playerBoard;  // P1's board
    std::unique_ptr<Board> boardP2;      // P2's board (hotseat/split)
    std::unique_ptr<Board> enemyBoard;   // Bot's board (vsBot)

    int cursorR, cursorC;
    int currentShipIdx;
    bool placingHorizontal;

    // Bot
    int botLevel;
    bool botThinking;
    float botTimer;
    std::vector<std::pair<int, int>> botTargets;
    bool botHunting;
    int botDirIndex;

    // Settings
    bool soundEnabled;
    bool autoPlace;
    bool fullscreen;
    bool playerTurnFirst;

    float animTimer;
    int menuSelection;
    int settingsSelection;

    // 1v1
    float switchTimer;
    bool placingP2;           // true when P2 is placing ships
    int cursorP2R, cursorP2C; // P2 cursor in split-screen

    std::vector<BattleMessage> messages;

    void loadResources();
    void handleEvents();
    void update(float dt);
    void render();

    sf::String toUtf8(const std::string& text) const;
    void drawText(const std::string& text, float x, float y, int size,
                  sf::Color color, bool center = false);
    void drawButton(const std::string& text, float x, float y, float w, float h,
                    bool hovered, bool selected);
    void applyFullscreen();
    void addMessage(const std::string& text, sf::Color color);

    void playHitSound();
    void playMissSound();
    void playSunkSound();

    // Menu & settings
    void renderMenu();
    void renderSettings();
    void renderRules();

    // Placement (shared for all modes)
    void renderPlacement();
    void renderPlacementP2(); // P2 placement screen (hotseat)

    // Battle modes
    void renderBattle();      // VsBot
    void renderBotTurn();
    void renderP1Turn();      // 1v1: P1 shoots at P2's board
    void renderP2Turn();      // 1v1: P2 shoots at P1's board
    void renderSplitscreenBattle(); // Both boards visible
    void renderSwitchScreen(); // 3-sec "pass device" screen

    // Results
    void renderVictory();
    void renderDefeat();
    void renderP1Wins();
    void renderP2Wins();

    void drawInfoPanel();
    void drawInfoPanel1v1(const std::string& p1Label, const std::string& p2Label,
                          Board* b1, Board* b2);
    void drawSplitscreenDivider();

    // Game flow
    void startPlacement();
    void startP2Placement();
    void startBattle();
    void startP1Turn();
    void startP2Turn();
    void startSplitscreenBattle();
    void botMakeMove();
    void resetGame();

    // Shooting helpers for 1v1
    void handleP1Shoot();
    void handleP2Shoot();
};
