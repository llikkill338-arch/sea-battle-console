// ============================================================================
// Game.hpp - v6.0 Simplified (works!)
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Board.hpp"

enum class GameState {
    Menu, Settings, Rules, Placement, Battle, BotTurn, Victory, Defeat, Exit
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

    std::unique_ptr<Board> playerBoard;
    std::unique_ptr<Board> enemyBoard;

    int cursorR, cursorC;
    int currentShipIdx;
    bool placingHorizontal;

    int botLevel;
    bool botThinking;
    float botTimer;
    std::vector<std::pair<int, int>> botTargets;
    bool botHunting;
    int botDirIndex;

    bool soundEnabled;
    bool autoPlace;
    bool fullscreen;
    bool playerTurnFirst;

    float animTimer;
    int menuSelection;
    int settingsSelection;

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

    void renderMenu();
    void renderSettings();
    void renderRules();
    void renderPlacement();
    void renderBattle();
    void renderBotTurn();
    void renderVictory();
    void renderDefeat();
    void drawInfoPanel();

    void startPlacement();
    void startBattle();
    void botMakeMove();
    void resetGame();
};
