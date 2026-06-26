// ============================================================================
// Game.hpp - Главный игровой класс v5.0 (Pixel-Art + Sound)
// ============================================================================

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include "Board.hpp"

enum class GameState {
    Menu,
    Settings,
    Rules,
    Placement,
    Battle,
    BotTurn,
    Victory,
    Defeat,
    Exit
};

// Particle for explosion effect
struct ExplosionParticle {
    float x, y, vx, vy;
    float timer;
    sf::Color color;
    float size;
};

// Floating battle message
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
    // --- Window ---
    sf::RenderWindow window;
    sf::Font font;

    // --- State ---
    GameState state;
    GameState prevState;

    std::unique_ptr<Board> playerBoard;
    std::unique_ptr<Board> enemyBoard;

    // --- Placement ---
    int cursorR, cursorC;
    int currentShipIdx;
    bool placingHorizontal;

    // --- Bot ---
    int botLevel;          // 0 = Easy, 1 = Hard
    bool botThinking;
    float botTimer;
    std::vector<std::pair<int, int>> botTargets;
    bool botHunting;
    int botDirIndex;

    // --- Settings ---
    bool soundEnabled;
    bool autoPlace;
    bool fullscreen;
    bool playerTurnFirst;

    // --- Animation ---
    float animTimer;
    int menuSelection;
    int settingsSelection;

    // --- Sound ---
    bool soundsLoaded;
    sf::SoundBuffer hitBuf;
    sf::SoundBuffer missBuf;
    sf::SoundBuffer sunkBuf;
    sf::Sound hitSound;
    sf::Sound missSound;
    sf::Sound sunkSound;
    sf::Music bgMusic;

    // --- Effects ---
    std::vector<ExplosionParticle> particles;
    std::vector<BattleMessage> messages;

    // --- Resources ---
    void loadResources();
    void loadSounds();

    // --- Core loop ---
    void handleEvents();
    void update(float dt);
    void render();

    // --- Utils ---
    sf::String toUtf8(const std::string& text) const;
    void drawText(const std::string& text, float x, float y, int size,
                  sf::Color color, bool center = false);
    void drawButton(const std::string& text, float x, float y, float w, float h,
                    bool hovered, bool selected);
    bool isMouseOver(float x, float y, float w, float h) const;
    void applyFullscreen();

    // --- Messages ---
    void addMessage(const std::string& text, sf::Color color);

    // --- Sound ---
    void playHitSound();
    void playMissSound();
    void playSunkSound();

    // --- Pirate phrases ---
    std::string getRandomHitPhrase() const;
    std::string getRandomMissPhrase() const;
    std::string getRandomSunkPhrase() const;
    std::string getRandomBotHitPhrase() const;

    // --- Particles ---
    void spawnExplosion(float cx, float cy);
    void drawParticles();

    // --- Pixel art (all drawn with code) ---
    void drawPixelFrigate(float x, float y);
    void drawPixelSkeleton(float x, float y);
    void drawPixelTreasure(float x, float y);
    void drawPixelPalms(float x, float y);
    void drawPixelExplosion(float x, float y, float scale);
    void drawDecorations();

    // --- UI ---
    void drawInfoPanel();

    // --- Render screens ---
    void renderMenu();
    void renderSettings();
    void renderRules();
    void renderPlacement();
    void renderBattle();
    void renderBotTurn();
    void renderVictory();
    void renderDefeat();

    // --- Game flow ---
    void startPlacement();
    void startBattle();
    void botMakeMove();
    void resetGame();
};
