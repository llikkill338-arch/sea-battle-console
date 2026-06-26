// ============================================================================
// Game.cpp - v6.0 Simplified: No audio lib, no pixel art, console Beep sound
// ============================================================================

#include "Game.hpp"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <windows.h>  // For Beep() - no extra DLL needed!

using namespace Colors;

// ===== UTF-8 Text =====
#define T_TITLE   u8"\u2620 \u041C\u041E\u0420\u0421\u041A\u041E\u0419 \u0411\u041E\u0419 \u2620"
#define T_SUB     u8"\u041F\u0438\u0440\u0430\u0442\u0441\u043A\u0430\u044F \u043C\u043E\u0440\u0441\u043A\u0430\u044F \u0431\u0438\u0442\u0432\u0430 v6.0"
#define T_START   u8"\u041D\u0430\u0447\u0430\u0442\u044C \u0431\u043E\u0439!"
#define T_RULES   u8"\u041A\u0430\u0440\u0442\u0430 \u0441\u043E\u043A\u0440\u043E\u0432\u0438\u0449"
#define T_SETT    u8"\u041D\u0430\u0441\u0442\u0440\u043E\u0439\u043A\u0438"
#define T_EXIT    u8"\u041F\u043E\u043A\u0438\u043D\u0443\u0442\u044C \u043A\u043E\u0440\u0430\u0431\u043B\u044C"
#define T_SETT_T  u8"\u041D\u0410\u0421\u0422\u0420\u041E\u0419\u041A\u0418"
#define T_BOTLVL  u8"\u0421\u043B\u043E\u0436\u043D\u043E\u0441\u0442\u044C \u0431\u043E\u0442\u0430"
#define T_PLACE   u8"\u0420\u0430\u0441\u0441\u0442\u0430\u043D\u043E\u0432\u043A\u0430"
#define T_SOUND   u8"\u0417\u0432\u0443\u043A (Beep)"
#define T_FULL    u8"\u041F\u043E\u043B\u043D\u044B\u0439 \u044D\u043A\u0440\u0430\u043D"
#define T_BACK    u8"\u041D\u0430\u0437\u0430\u0434"
#define T_EASY    u8"\u041B\u0401\u0413\u041A\u0418\u0419"
#define T_HARD    u8"\u0421\u041B\u041E\u0416\u041D\u042B\u0419"
#define T_AUTO    u8"\u0410\u0412\u0422\u041E"
#define T_MANUAL  u8"\u0412\u0420\u0423\u0427\u041D\u0423\u042E"
#define T_ON      u8"\u0412\u041A\u041B"
#define T_OFF     u8"\u0412\u042B\u041A\u041B"
#define T_R_TIT   u8"\u041A\u0410\u0420\u0422\u0410 \u0421\u041E\u041A\u0420\u041E\u0412\u0418\u0429"
#define T_R1      u8"\u0426\u0435\u043B\u044C: \u043F\u043E\u0442\u043E\u043F\u0438\u0442\u044C \u0432\u0435\u0441\u044C \u0444\u043B\u043E\u0442 (20 \u043F\u0430\u043B\u0443\u0431)."
#define T_R2      u8"\u0424\u043B\u043E\u0442: 1x4, 2x3, 3x2, 4x1 \u043A\u043E\u0440\u0430\u0431\u043B\u044F."
#define T_R3      u8"\u041A\u043E\u0440\u0430\u0431\u043B\u0438 \u043D\u0435 \u043A\u0430\u0441\u0430\u044E\u0442\u0441\u044F."
#define T_R4      u8"\u041F\u0440\u0438 \u043F\u043E\u043F\u0430\u0434\u0430\u043D\u0438\u0438 - \u0435\u0449\u0451 \u0445\u043E\u0434!"
#define T_R5      u8"\u041F\u0440\u0438 \u0443\u043D\u0438\u0447\u0442\u043E\u0436\u0435\u043D\u0438\u0438 - \u043E\u0440\u0435\u043E\u043B \u0430\u0432\u0442\u043E."
#define T_R6      u8"\u0421\u0442\u0440\u0435\u043B\u043A\u0438 | ENTER-\u0432\u044B\u0441\u0442\u0440\u0435\u043B | ESC"
#define T_R7      u8"\u041F\u0420\u041E\u0411\u0415\u041B-\u043F\u043E\u0432\u043E\u0440\u043E\u0442 | \u041F\u0435\u0440\u0432\u044B\u0439 \u0445\u043E\u0434 50/50"
#define T_R8      u8"\u041F\u043E\u0431\u0435\u0436\u0434\u0430\u0435\u0442 \u0442\u043E\u0442, \u043A\u0442\u043E \u043F\u043E\u0442\u043E\u043F\u0438\u0442 20 \u043F\u0430\u043B\u0443\u0431!"
#define T_PRESS   u8"\u041D\u0430\u0436\u043C\u0438 ENTER \u0438\u043B\u0438 ESC..."
#define T_PL_TIT  u8"\u0420\u0410\u0421\u0421\u0422\u0410\u041D\u041E\u0412\u041A\u0410 \u0424\u041B\u041E\u0422\u0410"
#define T_YP      u8"\u0412\u0430\u0448\u0435 \u043F\u043E\u043B\u0435"
#define T_SHIP    u8"\u041A\u043E\u0440\u0430\u0431\u043B\u044C:"
#define T_P       u8"-\u043F\u0430\u043B\u0443\u0431\u043D\u044B\u0439"
#define T_DIR     u8"\u041D\u0430\u043F\u0440\u0430\u0432\u043B\u0435\u043D\u0438\u0435:"
#define T_HOR     u8">>> \u0413\u041E\u0420\u0418\u0417\u041E\u041D\u0422\u0410\u041B\u042C\u041D\u041E"
#define T_VER     u8"vvv \u0412\u0415\u0420\u0422\u0418\u041A\u0410\u041B\u042C\u041D\u041E"
#define T_OK      u8"[OK] \u041C\u043E\u0436\u043D\u043E \u0441\u0442\u0430\u0432\u0438\u0442\u044C"
#define T_BAD     u8"[X] \u041C\u0435\u0441\u0442\u043E \u0437\u0430\u043D\u044F\u0442\u043E!"
#define T_CTRL    u8"\u0421\u0442\u0440\u0435\u043B\u043A\u0438-\u0434\u0432\u0438\u0436. | \u041F\u0420\u041E\u0411\u0415\u041B-\u043F\u043E\u0432\u043E\u0440\u043E\u0442"
#define T_CTR2    u8"ENTER-\u043F\u043E\u0441\u0442\u0430\u0432\u0438\u0442\u044C | ESC-\u041C\u0435\u043D\u044E"
#define T_LEFT    u8"\u041E\u0441\u0442\u0430\u043B\u043E\u0441\u044C:"
#define T_BATTLE  u8"\u0411\u041E\u0419 \u0421 \u0411\u041E\u0422\u041E\u041C"
#define T_EP      u8"\u041F\u043E\u043B\u0435 \u0432\u0440\u0430\u0433\u0430"
#define T_BOT     u8"\u0411\u041E\u0422 \u0414\u0423\u041C\u0410\u0415\u0422..."
#define T_WIN     u8"\u0412\u042B \u041F\u041E\u0411\u0415\u0414\u0418\u041B\u0418!"
#define T_WIN2    u8"\u0412\u0441\u0435 \u043A\u043E\u0440\u0430\u0431\u043B\u0438 \u043D\u0430 \u0434\u043D\u0435!"
#define T_LOSE    u8"\u0412\u042B \u041F\u0420\u041E\u0418\u0413\u0420\u0410\u041B\u0418..."
#define T_LOSE2   u8"\u0412\u0430\u0448 \u0444\u043B\u043E\u0442 \u043F\u043E\u0442\u043E\u043F\u043B\u0435\u043D!"
#define T_MNU2    u8"ENTER-\u041C\u0435\u043D\u044E | ESC-\u0412\u044B\u0445\u043E\u0434"
#define T_VY      u8"\u0412\u044B: "
#define T_VRAG    u8"\u0412\u0440\u0430\u0433: "
#define T_KOR     u8" \u043A\u043E\u0440."
#define T_AIM     u8"\u041F\u0440\u0438\u0446\u0435\u043B: "
#define T_1ST     u8"\u041F\u0435\u0440\u0432\u044B\u0439 \u0445\u043E\u0434: "
#define T_1YOU    u8"\u0412\u044B!"
#define T_1BOT    u8"\u0411\u043E\u0442"
#define T_SUNK    u8"\u041F\u043E\u0442\u043E\u043F\u043B\u0435\u043D\u043E: "
#define T_DECK    u8"\u041F\u0430\u043B\u0443\u0431: "
#define T_HINT    u8"\u2191\u2193\u2190\u2192 \u0434\u0432\u0438\u0436. | ENTER-\u0432\u044B\u0441\u0442\u0440\u0435\u043B | ESC"

const float P_BX = 45,  P_BY = 75;
const float E_BX = 625, E_BY = 75;
const float INF_X = 45, INF_Y = 545, INF_W = 1040, INF_H = 110;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE,
             sf::Style::Close | sf::Style::Titlebar),
      state(GameState::Menu), cursorR(0), cursorC(0), currentShipIdx(0),
      placingHorizontal(true), botLevel(0), botThinking(false), botTimer(0),
      soundEnabled(true), autoPlace(false), fullscreen(false), playerTurnFirst(true),
      animTimer(0), menuSelection(0), settingsSelection(0),
      botDirIndex(0), botHunting(false) {
    srand((unsigned)time(nullptr));
    window.setFramerateLimit(60);
    loadResources();
    playerBoard = std::make_unique<Board>(P_BX, P_BY, false);
    enemyBoard = std::make_unique<Board>(E_BX, E_BY, true);
}

Game::~Game() {}

sf::String Game::toUtf8(const std::string& text) const {
    return sf::String::fromUtf8(text.begin(), text.end());
}

void Game::drawText(const std::string& text, float x, float y, int size, sf::Color color, bool center) {
    sf::Text t;
    t.setString(toUtf8(text));
    t.setFont(font);
    t.setCharacterSize(size);
    t.setFillColor(color);
    if (center) { sf::FloatRect b = t.getLocalBounds(); t.setOrigin(b.width / 2, 0); }
    t.setPosition(x, y);
    window.draw(t);
}

void Game::drawButton(const std::string& text, float x, float y, float w, float h, bool hovered, bool selected) {
    sf::RectangleShape btn(sf::Vector2f(w, h));
    btn.setPosition(x, y);
    sf::Color fill = selected ? BUTTON_HOVER : BUTTON;
    if (hovered) fill = BUTTON_HOVER;
    btn.setFillColor(fill);
    btn.setOutlineColor(selected ? sf::Color::Yellow : sf::Color(100, 160, 220));
    btn.setOutlineThickness(selected ? 3 : 2);
    window.draw(btn);
    sf::Text lbl;
    lbl.setString(toUtf8(text));
    lbl.setFont(font);
    lbl.setCharacterSize(22);
    lbl.setFillColor(BUTTON_TEXT);
    sf::FloatRect b = lbl.getLocalBounds();
    lbl.setOrigin(b.width / 2, b.height / 2);
    lbl.setPosition(x + w / 2, y + h / 2 - 4);
    window.draw(lbl);
}

void Game::loadResources() {
    if (!font.loadFromFile("assets/fonts/Roboto.ttf"))
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
}

// ===== Console Beep sounds (Windows API, no DLL needed!) =====
void Game::playHitSound()   { if (soundEnabled) Beep(800, 150); }
void Game::playMissSound()  { if (soundEnabled) Beep(300, 300); }
void Game::playSunkSound()  {
    if (soundEnabled) {
        Beep(1200, 100);
        Beep(900, 100);
        Beep(600, 200);
    }
}

void Game::applyFullscreen() {
    window.close();
    if (fullscreen) window.create(sf::VideoMode::getDesktopMode(), WINDOW_TITLE, sf::Style::Fullscreen);
    else window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen() && state != GameState::Exit) {
        float dt = clock.restart().asSeconds();
        animTimer += dt;
        update(dt);
        handleEvents();
        render();
    }
}

void Game::addMessage(const std::string& text, sf::Color color) {
    messages.push_back({text, 2.5f, color});
}

// ===== PIRATE PHRASES =====
std::string getRandomHitPhrase() {
    const char* p[] = {
        u8"\u041F\u0440\u044F\u043C\u043E \u0432 \u0446\u0435\u043B\u044C, \u043A\u0430\u043F\u0438\u0442\u0430\u043D!",
        u8"\u0415\u0449\u0451 \u043E\u0434\u0438\u043D \u043A \u0414\u044D\u0432\u0438 \u0414\u0436\u043E\u043D\u0441\u0443!",
        u8"\u0410\u0440\u0440\u0440! \u041E\u0433\u043E\u043D\u044C \u0438 \u043F\u043E\u0440\u043E\u0445!",
        u8"\u041C\u0435\u0442\u043A\u0430\u044F \u043F\u043E\u043F\u0430\u043B!",
        u8"\u041A\u043E\u0440\u0430\u0431\u043B\u044C \u0433\u043E\u0440\u0438\u0442!",
        u8"\u0423\u0434\u0430\u0447\u0430 \u043F\u0438\u0440\u0430\u0442\u0430!"
    };
    return p[rand() % 6];
}

std::string getRandomMissPhrase() {
    const char* p[] = {
        u8"\u041C\u0438\u043C\u043E! \u0422\u043E\u043B\u044C\u043A\u043E \u0432\u043E\u043B\u043D\u044B...",
        u8"\u041C\u043E\u0440\u0441\u043A\u0430\u044F \u043F\u0435\u043D\u0430!",
        u8"\u041F\u0440\u043E\u043C\u0430\u0445... \u0412\u0435\u0442\u0435\u0440!",
        u8"\u041D\u0435\u0442! \u0417\u0434\u0435\u0441\u044C \u043F\u0443\u0441\u0442\u043E!",
        u8"\u0420\u044B\u0431\u044B \u043F\u043B\u0430\u0432\u0430\u044E\u0442...",
        u8"\u041C\u0438\u043C\u043E! \u0412 \u0441\u043B\u0435\u0434\u0443\u044E\u0449\u0438\u0439 \u0440\u0430\u0437!"
    };
    return p[rand() % 6];
}

std::string getRandomSunkPhrase() {
    const char* p[] = {
        u8"\u041A\u041E\u0420\u0410\u0411\u041B\u042C \u041D\u0410 \u0414\u041D\u041E!",
        u8"\u0423\u041D\u0418\u0427\u0422\u041E\u0416\u0415\u041D! \u0410\u0440\u0440\u0440!",
        u8"\u041F\u043E\u0442\u043E\u043F\u043B\u0435\u043D! \u0422\u0430\u043A \u0435\u043C\u0443!",
        u8"\u041D\u0430 \u0434\u043D\u043E \u043A\u043E \u0434\u044C\u044F\u0432\u043E\u043B\u0443!",
        u8"\u0412\u0437\u0440\u044B\u0432! \u041A\u043E\u0440\u0430\u0431\u043B\u044C \u0440\u0430\u0437\u043B\u0435\u0442\u0435\u043B\u0441\u044F!"
    };
    return p[rand() % 5];
}

std::string getRandomBotHitPhrase() {
    const char* p[] = {
        u8"\u0411\u043E\u0442 \u043F\u043E\u043F\u0430\u043B! \u0412 \u0430\u0441 \u0441\u0442\u0440\u0435\u043B\u044F\u044E\u0442!",
        u8"\u0412\u0440\u0430\u0436\u0435\u0441\u043A\u0430\u044F \u044F\u0434\u0440\u0430!",
        u8"\u041D\u0430\u0448 \u043A\u043E\u0440\u0430\u0431\u043B\u044C \u043F\u043E\u0434 \u043E\u0431\u0441\u0442\u0440\u0435\u043B\u043E\u043C!",
        u8"\u0410\u0440\u0440\u0440! \u0412\u0440\u0430\u0433 \u043F\u043E\u043F\u0430\u043B!",
        u8"\u041A\u043E\u0440\u043F\u0443\u0441 \u0440\u0430\u043D\u0435\u043D!"
    };
    return p[rand() % 5];
}

// ===== EVENTS =====
void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) state = GameState::Exit;

        if (event.type == sf::Event::KeyPressed) {
            if (state == GameState::Menu) {
                if (event.key.code == sf::Keyboard::Up && menuSelection > 0) menuSelection--;
                if (event.key.code == sf::Keyboard::Down && menuSelection < 3) menuSelection++;
                if (event.key.code == sf::Keyboard::Enter) {
                    switch (menuSelection) {
                        case 0: startPlacement(); break;
                        case 1: state = GameState::Rules; break;
                        case 2: state = GameState::Settings; break;
                        case 3: state = GameState::Exit; break;
                    }
                }
            }
            else if (state == GameState::Settings) {
                if (event.key.code == sf::Keyboard::Up && settingsSelection > 0) settingsSelection--;
                if (event.key.code == sf::Keyboard::Down && settingsSelection < 4) settingsSelection++;
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                    if (settingsSelection == 0) botLevel = 1 - botLevel;
                    if (settingsSelection == 1) autoPlace = !autoPlace;
                    if (settingsSelection == 2) soundEnabled = !soundEnabled;
                    if (settingsSelection == 3) { fullscreen = !fullscreen; applyFullscreen(); }
                }
                if (event.key.code == sf::Keyboard::Enter && settingsSelection == 4) state = GameState::Menu;
                if (event.key.code == sf::Keyboard::Escape) state = GameState::Menu;
            }
            else if (state == GameState::Rules) {
                if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
                    state = GameState::Menu;
            }
            else if (state == GameState::Placement) {
                int size = FLEET_SIZES[currentShipIdx];
                if (event.key.code == sf::Keyboard::Up && cursorR > 0) cursorR--;
                if (event.key.code == sf::Keyboard::Down && cursorR < BOARD_SIZE - 1) cursorR++;
                if (event.key.code == sf::Keyboard::Left && cursorC > 0) cursorC--;
                if (event.key.code == sf::Keyboard::Right && cursorC < BOARD_SIZE - 1) cursorC++;
                if (event.key.code == sf::Keyboard::Space) {
                    placingHorizontal = !placingHorizontal;
                    if (placingHorizontal) { if (cursorC + size > BOARD_SIZE) cursorC = BOARD_SIZE - size; }
                    else { if (cursorR + size > BOARD_SIZE) cursorR = BOARD_SIZE - size; }
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    if (playerBoard->canPlaceShip(cursorR, cursorC, size, placingHorizontal)) {
                        playerBoard->placeShip(cursorR, cursorC, size, placingHorizontal);
                        currentShipIdx++;
                        if (currentShipIdx >= FLEET_COUNT) startBattle();
                    }
                }
                if (event.key.code == sf::Keyboard::Escape) state = GameState::Menu;
            }
            else if (state == GameState::Battle) {
                if (event.key.code == sf::Keyboard::Up && cursorR > 0) cursorR--;
                if (event.key.code == sf::Keyboard::Down && cursorR < BOARD_SIZE - 1) cursorR++;
                if (event.key.code == sf::Keyboard::Left && cursorC > 0) cursorC--;
                if (event.key.code == sf::Keyboard::Right && cursorC < BOARD_SIZE - 1) cursorC++;
                if (event.key.code == sf::Keyboard::Enter) {
                    CellState cs = enemyBoard->getCellState(cursorR, cursorC);
                    if (cs != CellState::Hit && cs != CellState::Miss) {
                        int shipsBefore = enemyBoard->getShipsAlive();
                        bool hit = enemyBoard->shoot(cursorR, cursorC);
                        int shipsAfter = enemyBoard->getShipsAlive();

                        if (hit) {
                            if (shipsAfter < shipsBefore) {
                                addMessage(getRandomSunkPhrase(), sf::Color(255, 140, 0));
                                playSunkSound();
                            } else {
                                addMessage(getRandomHitPhrase(), sf::Color(255, 80, 80));
                                playHitSound();
                            }
                        } else {
                            addMessage(getRandomMissPhrase(), sf::Color(150, 200, 255));
                            playMissSound();
                        }

                        if (enemyBoard->allShipsSunk()) {
                            state = GameState::Victory;
                        } else if (!hit) {
                            state = GameState::BotTurn;
                            botTimer = 0;
                            botThinking = true;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Escape) state = GameState::Menu;
            }
            else if (state == GameState::Victory || state == GameState::Defeat) {
                if (event.key.code == sf::Keyboard::Enter) { resetGame(); state = GameState::Menu; }
                if (event.key.code == sf::Keyboard::Escape) state = GameState::Menu;
            }
        }
    }
}

// ===== UPDATE =====
void Game::update(float dt) {
    for (auto& m : messages) m.timer -= dt;
    messages.erase(std::remove_if(messages.begin(), messages.end(),
        [](const BattleMessage& m) { return m.timer <= 0; }), messages.end());

    if (state == GameState::BotTurn && botThinking) {
        botTimer += dt;
        if (botTimer >= BOT_THINK_DELAY) {
            int shipsBefore = playerBoard->getShipsAlive();
            botMakeMove();
            int shipsAfter = playerBoard->getShipsAlive();

            if (shipsAfter < shipsBefore) {
                addMessage(getRandomSunkPhrase(), sf::Color(255, 140, 0));
                playSunkSound();
            } else if (!botTargets.empty() && botHunting) {
                addMessage(getRandomBotHitPhrase(), sf::Color(255, 100, 100));
                playHitSound();
            } else {
                playMissSound();
            }

            botThinking = false;
            if (playerBoard->allShipsSunk()) {
                state = GameState::Defeat;
            } else {
                state = GameState::Battle;
            }
        }
    }
}

// ===== BOT AI =====
void Game::botMakeMove() {
    if (botLevel == 0) {
        int r, c;
        do { r = rand() % BOARD_SIZE; c = rand() % BOARD_SIZE; }
        while (playerBoard->getCellState(r, c) == CellState::Hit ||
               playerBoard->getCellState(r, c) == CellState::Miss);
        playerBoard->shoot(r, c);
    } else {
        if (botHunting && !botTargets.empty()) {
            int tr = botTargets[0].first;
            int tc = botTargets[0].second;
            if (botTargets.size() >= 2) {
                bool horizontal = botTargets[0].first == botTargets[1].first;
                int minR = tr, maxR = tr, minC = tc, maxC = tc;
                for (auto& t : botTargets) {
                    minR = std::min(minR, t.first); maxR = std::max(maxR, t.first);
                    minC = std::min(minC, t.second); maxC = std::max(maxC, t.second);
                }
                int nr, nc;
                if (horizontal) {
                    nr = tr; nc = maxC + 1;
                    if (nc >= BOARD_SIZE || playerBoard->getCellState(nr, nc) == CellState::Miss) nc = minC - 1;
                } else {
                    nr = maxR + 1; nc = tc;
                    if (nr >= BOARD_SIZE || playerBoard->getCellState(nr, nc) == CellState::Miss) nr = minR - 1;
                }
                if (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE &&
                    playerBoard->getCellState(nr, nc) != CellState::Hit &&
                    playerBoard->getCellState(nr, nc) != CellState::Miss) {
                    bool hit = playerBoard->shoot(nr, nc);
                    if (hit) botTargets.push_back({nr, nc});
                    else { botDirIndex++; if (botDirIndex > 3) { botHunting = false; botTargets.clear(); botDirIndex = 0; } }
                    return;
                }
            }
            int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
            for (int i = botDirIndex; i < 4; i++) {
                int nr = tr + dirs[i][0], nc = tc + dirs[i][1];
                if (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE &&
                    playerBoard->getCellState(nr, nc) != CellState::Hit &&
                    playerBoard->getCellState(nr, nc) != CellState::Miss) {
                    botDirIndex = i;
                    bool hit = playerBoard->shoot(nr, nc);
                    if (hit) botTargets.push_back({nr, nc});
                    else botDirIndex++;
                    return;
                }
            }
            botHunting = false;
            botTargets.clear();
            botDirIndex = 0;
        }
        if (!botHunting) {
            int r, c, attempts = 0;
            do {
                r = rand() % BOARD_SIZE; c = rand() % BOARD_SIZE; attempts++;
            } while (attempts < 300 && ((r + c) % 2 != 0 ||
                     playerBoard->getCellState(r, c) == CellState::Hit ||
                     playerBoard->getCellState(r, c) == CellState::Miss));
            if (attempts >= 300) {
                do { r = rand() % BOARD_SIZE; c = rand() % BOARD_SIZE; }
                while (playerBoard->getCellState(r, c) == CellState::Hit ||
                       playerBoard->getCellState(r, c) == CellState::Miss);
            }
            bool hit = playerBoard->shoot(r, c);
            if (hit) {
                botHunting = true;
                botTargets.clear();
                botTargets.push_back({r, c});
                botDirIndex = 0;
            }
        }
    }
}

void Game::startPlacement() {
    state = GameState::Placement;
    playerBoard->clear(); enemyBoard->clear();
    enemyBoard->autoPlace();
    currentShipIdx = 0; cursorR = 0; cursorC = 0; placingHorizontal = true;
    messages.clear();
    if (autoPlace) { playerBoard->autoPlace(); startBattle(); }
}

void Game::startBattle() {
    state = GameState::Battle;
    cursorR = 0; cursorC = 0; botThinking = false;
    botTargets.clear(); botHunting = false; botDirIndex = 0;
    messages.clear();
    playerTurnFirst = (rand() % 2 == 0);
    if (!playerTurnFirst) { state = GameState::BotTurn; botTimer = 0; botThinking = true; }
}

void Game::resetGame() {
    playerBoard->clear(); enemyBoard->clear();
    cursorR = 0; cursorC = 0; currentShipIdx = 0; menuSelection = 0;
    botTargets.clear(); botHunting = false; botDirIndex = 0;
    messages.clear();
}

// ===== RENDERING =====
void Game::render() {
    window.clear(BG);
    switch (state) {
        case GameState::Menu:      renderMenu(); break;
        case GameState::Settings:  renderSettings(); break;
        case GameState::Rules:     renderRules(); break;
        case GameState::Placement: renderPlacement(); break;
        case GameState::Battle:    renderBattle(); break;
        case GameState::BotTurn:   renderBotTurn(); break;
        case GameState::Victory:   renderVictory(); break;
        case GameState::Defeat:    renderDefeat(); break;
        default: break;
    }
    window.display();
}

void Game::renderMenu() {
    drawText(T_TITLE, WINDOW_WIDTH / 2, 70, 52, TEXT_GOLD, true);
    drawText(T_SUB, WINDOW_WIDTH / 2, 130, 18, sf::Color(180, 160, 100), true);

    sf::RectangleShape sep(sf::Vector2f(400, 2));
    sep.setPosition(WINDOW_WIDTH / 2 - 200, 165);
    sep.setFillColor(GRID_LINE);
    window.draw(sep);

    const char* buttons[] = { T_START, T_RULES, T_SETT, T_EXIT };
    for (int i = 0; i < 4; i++) {
        float y = 200 + i * 72;
        drawButton(buttons[i], WINDOW_WIDTH / 2 - 150, y, 300, 52, false, i == menuSelection);
    }
    drawText(u8"\u0421\u0442\u0440\u0435\u043B\u043A\u0438 ^/v - \u0432\u044B\u0431\u043E\u0440  |  ENTER - \u043F\u043E\u0434\u0442\u0432\u0435\u0440\u0434\u0438\u0442\u044C",
             WINDOW_WIDTH / 2, 530, 16, sf::Color(140, 140, 160), true);
}

void Game::renderSettings() {
    drawText(T_SETT_T, WINDOW_WIDTH / 2, 55, 38, TEXT_GOLD, true);
    const char* labels[] = { T_BOTLVL, T_PLACE, T_SOUND, T_FULL, T_BACK };
    const char* values[] = {
        botLevel == 0 ? T_EASY : T_HARD,
        autoPlace ? T_AUTO : T_MANUAL,
        soundEnabled ? T_ON : T_OFF,
        fullscreen ? T_ON : T_OFF,
        ""
    };
    for (int i = 0; i < 5; i++) {
        float y = 160 + i * 85;
        sf::Color color = (i == settingsSelection) ? sf::Color::Yellow : TEXT;
        drawText(labels[i], WINDOW_WIDTH / 2 - 250, y, 24, color, false);
        if (strlen(values[i]) > 0) {
            sf::Color vc = (i == settingsSelection) ? sf::Color::Green : sf::Color(100, 200, 255);
            drawText(values[i], WINDOW_WIDTH / 2 + 180, y, 24, vc, false);
        }
    }
    drawText(u8"</> - \u0438\u0437\u043C\u0435\u043D\u0438\u0442\u044C  |  ENTER/ESC - \u043D\u0430\u0437\u0430\u0434",
             WINDOW_WIDTH / 2, 650, 16, sf::Color(140, 140, 160), true);
}

void Game::renderRules() {
    drawText(T_R_TIT, WINDOW_WIDTH / 2, 50, 38, TEXT_GOLD, true);
    const char* lines[] = { T_R1, T_R2, T_R3, T_R4, T_R5, T_R6, T_R7, T_R8 };
    for (int i = 0; i < 8; i++) {
        sf::Color color = (i < 5) ? TEXT : sf::Color(180, 180, 200);
        drawText(lines[i], 80, 120 + i * 45, 20, color, false);
    }
    drawText(T_PRESS, WINDOW_WIDTH / 2, 520, 20, TEXT_GOLD, true);
    drawText(u8"\u041F\u0438\u0440\u0430\u0442\u0441\u043A\u0438\u0435 \u0437\u0430\u043A\u043E\u043D\u044B:", 80, 85, 18, sf::Color(200, 160, 80), false);
}

void Game::renderPlacement() {
    drawText(T_PL_TIT, WINDOW_WIDTH / 2, 15, 26, TEXT_GOLD, true);
    int size = FLEET_SIZES[currentShipIdx];
    bool valid = playerBoard->canPlaceShip(cursorR, cursorC, size, placingHorizontal);
    playerBoard->draw(window, font, cursorR, cursorC, true, size, placingHorizontal, valid);
    drawText(T_YP, P_BX + BOARD_PIXELS / 2 + 20, 50, 18, sf::Color(100, 255, 150), true);

    float px = P_BX + BOARD_PIXELS + 55;
    sf::RectangleShape panel(sf::Vector2f(260, 430));
    panel.setPosition(px, P_BY);
    panel.setFillColor(PANEL_BG);
    panel.setOutlineColor(GRID_LINE);
    panel.setOutlineThickness(1);
    window.draw(panel);

    drawText(T_SHIP, px + 15, P_BY + 15, 20, TEXT, false);
    drawText(std::to_string(size) + T_P, px + 15, P_BY + 42, 22, TEXT_GOLD, false);
    drawText(T_DIR, px + 15, P_BY + 80, 16, TEXT, false);
    drawText(placingHorizontal ? T_HOR : T_VER, px + 15, P_BY + 100, 16, sf::Color(100, 200, 255), false);
    if (valid) drawText(T_OK, px + 15, P_BY + 135, 16, sf::Color(50, 200, 80), false);
    else       drawText(T_BAD, px + 15, P_BY + 135, 16, sf::Color(255, 80, 80), false);

    drawText(T_CTRL, px + 15, P_BY + 180, 14, sf::Color(150, 150, 170), false);
    drawText(T_CTR2, px + 15, P_BY + 200, 14, sf::Color(150, 150, 170), false);

    drawText(std::to_string(currentShipIdx) + " / " + std::to_string(FLEET_COUNT), px + 15, P_BY + 250, 20, TEXT_GOLD, false);
    drawText(T_LEFT, px + 15, P_BY + 280, 15, sf::Color(150, 150, 170), false);

    int yPos = P_BY + 305, counts[5] = {0,0,0,0,0};
    for (int i = currentShipIdx; i < FLEET_COUNT; i++) { int s = FLEET_SIZES[i]; if (s >= 1 && s <= 4) counts[4-s]++; }
    for (int deck = 4; deck >= 1; deck--) {
        int cnt = counts[4 - deck];
        if (cnt > 0) {
            std::string line = std::to_string(cnt) + " x " + std::string(deck, '=') + " (" + std::to_string(deck) + "p)";
            drawText(line, px + 15, yPos, 14, sf::Color(100, 180, 255), false);
            yPos += 18;
        }
    }
}

void Game::renderBattle() {
    drawText(T_BATTLE, WINDOW_WIDTH / 2, 12, 24, TEXT_GOLD, true);
    drawText(T_YP, P_BX + BOARD_PIXELS / 2 + 20, 50, 17, sf::Color(100, 255, 150), true);
    drawText(T_EP, E_BX + BOARD_PIXELS / 2 + 20, 50, 17, sf::Color(255, 120, 100), true);

    playerBoard->draw(window, font, -1, -1, true, 0, true, true);
    enemyBoard->draw(window, font, cursorR, cursorC, false, 0, true, true);

    drawInfoPanel();

    if (!messages.empty()) {
        float msgY = 540;
        for (auto& m : messages) {
            float alpha = std::min(1.0f, m.timer);
            sf::Color c = m.color;
            c.a = (sf::Uint8)(255 * alpha);
            drawText(m.text, WINDOW_WIDTH / 2, msgY, 20, c, true);
            msgY -= 26;
        }
    }
}

void Game::renderBotTurn() {
    renderBattle();
    sf::RectangleShape overlay(sf::Vector2f(BOARD_PIXELS + 40, BOARD_PIXELS + 40));
    overlay.setPosition(E_BX + 8, E_BY + 8);
    overlay.setFillColor(sf::Color(0, 0, 0, 60));
    window.draw(overlay);
    drawText(T_BOT, E_BX + BOARD_PIXELS / 2 + 20, E_BY + BOARD_PIXELS / 2 - 15, 32, sf::Color(255, 200, 50), true);
    int dots = (int)(botTimer * 3) % 4;
    drawText(std::string(dots, '.'), E_BX + BOARD_PIXELS / 2 + 20, E_BY + BOARD_PIXELS / 2 + 20, 28, sf::Color(255, 200, 50), true);
}

void Game::drawInfoPanel() {
    sf::RectangleShape panel(sf::Vector2f(INF_W, INF_H));
    panel.setPosition(INF_X, INF_Y);
    panel.setFillColor(PANEL_BG);
    panel.setOutlineColor(GRID_LINE);
    panel.setOutlineThickness(2);
    window.draw(panel);

    sf::RectangleShape a1(sf::Vector2f(20, 3)); a1.setPosition(INF_X, INF_Y); a1.setFillColor(TEXT_GOLD); window.draw(a1);
    sf::RectangleShape a2(sf::Vector2f(3, 20)); a2.setPosition(INF_X, INF_Y); a2.setFillColor(TEXT_GOLD); window.draw(a2);
    sf::RectangleShape a3(sf::Vector2f(20, 3)); a3.setPosition(INF_X + INF_W - 20, INF_Y); a3.setFillColor(TEXT_GOLD); window.draw(a3);
    sf::RectangleShape a4(sf::Vector2f(3, 20)); a4.setPosition(INF_X + INF_W - 3, INF_Y); a4.setFillColor(TEXT_GOLD); window.draw(a4);

    drawText(std::string(T_VY) + std::to_string(playerBoard->getShipsAlive()) + T_KOR, INF_X + 30, INF_Y + 16, 20, sf::Color(100, 255, 150), false);
    drawText(std::string(T_VRAG) + std::to_string(enemyBoard->getShipsAlive()) + T_KOR, INF_X + 30, INF_Y + 48, 20, sf::Color(255, 120, 100), false);

    std::string aim = std::string(T_AIM) + char('A' + cursorC) + std::to_string(cursorR + 1);
    drawText(aim, INF_X + INF_W / 2, INF_Y + 22, 26, TEXT_GOLD, true);

    int sunkP = 10 - enemyBoard->getShipsAlive();
    int sunkE = 10 - playerBoard->getShipsAlive();
    drawText(std::string(T_SUNK) + std::to_string(sunkP), INF_X + INF_W - 200, INF_Y + 16, 18, sf::Color(255, 180, 50), false);
    drawText(std::string(T_DECK) + std::to_string(sunkP * 2 + sunkE), INF_X + INF_W - 200, INF_Y + 48, 18, sf::Color(200, 160, 80), false);

    drawText(T_HINT, INF_X + INF_W / 2, INF_Y + 80, 15, sf::Color(140, 140, 160), true);
    std::string ft = std::string(T_1ST) + (playerTurnFirst ? T_1YOU : T_1BOT);
    drawText(ft, INF_X + 30, INF_Y + 80, 15, sf::Color(100, 200, 255), false);
}

void Game::renderVictory() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 20, 0, 200));
    window.draw(overlay);

    drawText(T_WIN, WINDOW_WIDTH / 2, 300, 56, sf::Color(50, 255, 100), true);
    drawText(T_WIN2, WINDOW_WIDTH / 2, 380, 24, TEXT, true);
    drawText(T_MNU2, WINDOW_WIDTH / 2, 500, 20, TEXT_GOLD, true);
}

void Game::renderDefeat() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(20, 0, 0, 200));
    window.draw(overlay);

    drawText(T_LOSE, WINDOW_WIDTH / 2, 320, 56, sf::Color(255, 50, 50), true);
    drawText(T_LOSE2, WINDOW_WIDTH / 2, 400, 24, TEXT, true);
    drawText(T_MNU2, WINDOW_WIDTH / 2, 520, 20, TEXT_GOLD, true);
}
