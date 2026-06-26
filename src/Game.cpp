// ============================================================================
// Game.cpp - v7.0 PIRATE EDITION - Full pirate theme overhaul
// ============================================================================

#include "Game.hpp"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <windows.h>  // For Beep() - no extra DLL needed!

using namespace Colors;

// ===== Пиратские UTF-8 фразы =====
// Меню
#define T_TITLE   u8"\u2620 \u041C\u041E\u0420\u0421\u041A\u041E\u0419 \u0411\u041E\u0419 \u2620"
#define T_SUB     u8"\u041F\u0438\u0440\u0430\u0442\u0441\u043A\u043E\u0435 \u0438\u0437\u0434\u0430\u043D\u0438\u0435 v7.0"
#define T_START   u8"\u0412 \u043C\u043E\u0440\u0435!"
#define T_RULES   u8"\u041A\u0430\u0440\u0442\u0430 \u0441\u043E\u043A\u0440\u043E\u0432\u0438\u0449"
#define T_SETT    u8"\u041D\u0430\u0441\u0442\u0440\u043E\u0439\u043A\u0438"
#define T_EXIT    u8"\u041F\u043E\u043A\u0438\u043D\u0443\u0442\u044C \u043A\u043E\u0440\u0430\u0431\u043B\u044C"
#define T_SETT_T  u8"\u041F\u0410\u0420\u0423\u0421\u041D\u0410\u042F \u041A\u0410\u042E\u0422\u0410"
#define T_BOTLVL  u8"\u0421\u043B\u043E\u0436\u043D\u043E\u0441\u0442\u044C \u0431\u043E\u0442\u0430"
#define T_PLACE   u8"\u0420\u0430\u0441\u0441\u0442\u0430\u043D\u043E\u0432\u043A\u0430"
#define T_SOUND   u8"\u0417\u0432\u0443\u043A (\u0411\u0438\u043F)"
#define T_FULL    u8"\u041F\u043E\u043B\u043D\u044B\u0439 \u044D\u043A\u0440\u0430\u043D"
#define T_BACK    u8"\u041D\u0430\u0437\u0430\u0434"
#define T_EASY    u8"\u041B\u0401\u0413\u041A\u0418\u0419"
#define T_HARD    u8"\u0421\u041B\u041E\u0416\u041D\u042B\u0419"
#define T_AUTO    u8"\u0410\u0412\u0422\u041E"
#define T_MANUAL  u8"\u0412\u0420\u0423\u0427\u041D\u0423\u042E"
#define T_ON      u8"\u0412\u041A\u041B"
#define T_OFF     u8"\u0412\u042B\u041A\u041B"
// Правила
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
// Расстановка
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
// Бой
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

// ===== Вспомогательные функции декораций =====

static void drawPirateLine(sf::RenderWindow& w, float x1, float y1, float x2, float y2, sf::Color c, float thickness = 2) {
    sf::RectangleShape line;
    float len = sqrtf((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    float angle = atan2f(y2-y1, x2-x1) * 180 / 3.14159f;
    line.setSize(sf::Vector2f(len, thickness));
    line.setOrigin(0, thickness/2);
    line.setPosition(x1, y1);
    line.setRotation(angle);
    line.setFillColor(c);
    w.draw(line);
}

static void drawPirateRect(sf::RenderWindow& w, float x, float y, float width, float height, sf::Color fill, sf::Color border, float borderThick = 2) {
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(x, y);
    rect.setFillColor(fill);
    rect.setOutlineColor(border);
    rect.setOutlineThickness(borderThick);
    w.draw(rect);
}

// ===== КЛАСС ИГРЫ =====

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

void Game::drawTextShadow(const std::string& text, float x, float y, int size, sf::Color color, bool center) {
    drawText(text, x + 2, y + 2, size, sf::Color(20, 15, 10), center);
    drawText(text, x, y, size, color, center);
}

void Game::drawButton(const std::string& text, float x, float y, float w, float h, bool hovered, bool selected) {
    drawPirateRect(window, x, y, w, h,
        hovered ? BUTTON_HOVER : BUTTON,
        selected ? sf::Color(200, 160, 60) : sf::Color(60, 40, 20), 3);

    // Гвозди по углам
    sf::CircleShape nail(2.5f);
    nail.setFillColor(sf::Color(140, 120, 80));
    float nailPos[4][2] = {{x+4,y+4}, {x+w-8,y+4}, {x+4,y+h-8}, {x+w-8,y+h-8}};
    for (auto& p : nailPos) { nail.setPosition(p[0], p[1]); window.draw(nail); }

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

// Beep sounds
void Game::playHitSound()   { if (soundEnabled) Beep(900, 120); }
void Game::playMissSound()  { if (soundEnabled) Beep(250, 350); }
void Game::playSunkSound()  {
    if (soundEnabled) { Beep(1300, 80); Beep(1000, 80); Beep(500, 250); }
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

// ===== Пиратские фразы =====
std::string getRandomHitPhrase() {
    const char* p[] = {
        u8"\u041F\u0440\u044F\u043C\u043E \u0432 \u0446\u0435\u043B\u044C, \u043A\u0430\u043F\u0438\u0442\u0430\u043D!",
        u8"\u0415\u0449\u0451 \u043E\u0434\u0438\u043D \u043A \u0414\u044D\u0432\u0438 \u0414\u0436\u043E\u043D\u0441\u0443!",
        u8"\u0410\u0440\u0440\u0440! \u042F\u0434\u0440\u043E \u043F\u043E\u0440\u043E\u0445\u0443!",
        u8"\u041C\u0435\u0442\u043A\u0430\u044F \u043F\u043E\u043F\u0430\u043B, \u043A\u0430\u043A \u0432 \u043F\u0442\u0438\u0446\u0443!",
        u8"\u041A\u043E\u0440\u0430\u0431\u043B\u044C \u0433\u043E\u0440\u0438\u0442! \u0425\u0430-\u0445\u0430!",
        u8"\u0423\u0434\u0430\u0447\u0430 \u043F\u0438\u0440\u0430\u0442\u0430, \u043C\u0430\u0442\u044C \u0435\u0433\u043E!"
    };
    return p[rand() % 6];
}

std::string getRandomMissPhrase() {
    const char* p[] = {
        u8"\u041C\u0438\u043C\u043E! \u0422\u043E\u043B\u044C\u043A\u043E \u0432\u043E\u043B\u043D\u044B...",
        u8"\u041C\u043E\u0440\u0441\u043A\u0430\u044F \u043F\u0435\u043D\u0430!",
        u8"\u041F\u0440\u043E\u043C\u0430\u0445... \u041F\u0440\u043E\u043A\u043B\u044F\u0442\u044B\u0439 \u0432\u0435\u0442\u0435\u0440!",
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
        u8"\u0412\u0440\u0430\u0436\u0435\u0441\u043A\u0430\u044F \u044F\u0434\u0440\u0430! \u0411\u0435\u0440\u0435\u0433\u0438\u0441\u044C!",
        u8"\u041D\u0430\u0448 \u043A\u043E\u0440\u0430\u0431\u043B\u044C \u043F\u043E\u0434 \u043E\u0431\u0441\u0442\u0440\u0435\u043B\u043E\u043C!",
        u8"\u0410\u0440\u0440\u0440! \u0412\u0440\u0430\u0433 \u043F\u043E\u043F\u0430\u043B!",
        u8"\u041A\u043E\u0440\u043F\u0443\u0441 \u0440\u0430\u043D\u0435\u043D! \u041A \u0431\u0443\u0448\u043F\u0440\u0438\u0442\u0443!"
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

// ===== ДЕКОРАЦИИ =====

void Game::drawPirateSkull(float ox, float oy, float scale) {
    sf::CircleShape skull(14 * scale);
    skull.setFillColor(BONE_WHITE);
    skull.setPosition(ox, oy);
    window.draw(skull);

    sf::CircleShape eyeL(3.5f * scale);
    eyeL.setFillColor(BLACK_FLAG);
    eyeL.setPosition(ox + 4 * scale, oy + 6 * scale);
    window.draw(eyeL);

    sf::CircleShape eyeR(3.5f * scale);
    eyeR.setFillColor(BLACK_FLAG);
    eyeR.setPosition(ox + 17 * scale, oy + 6 * scale);
    window.draw(eyeR);

    sf::CircleShape nose(2 * scale);
    nose.setFillColor(sf::Color(160, 140, 120));
    nose.setPosition(ox + 12 * scale, oy + 12 * scale);
    window.draw(nose);

    sf::RectangleShape bone1(sf::Vector2f(35 * scale, 5 * scale));
    bone1.setFillColor(BONE_WHITE);
    bone1.setOrigin(17 * scale, 2.5f * scale);
    bone1.setPosition(ox + 14 * scale, oy + 22 * scale);
    bone1.setRotation(45);
    window.draw(bone1);

    sf::RectangleShape bone2(sf::Vector2f(35 * scale, 5 * scale));
    bone2.setFillColor(BONE_WHITE);
    bone2.setOrigin(17 * scale, 2.5f * scale);
    bone2.setPosition(ox + 14 * scale, oy + 22 * scale);
    bone2.setRotation(-45);
    window.draw(bone2);
}

void Game::drawPirateAnchor(float x, float y, float scale) {
    drawPirateLine(window, x, y, x, y + 30 * scale, sf::Color(100, 80, 50), 3 * scale);

    sf::CircleShape ring(4 * scale);
    ring.setFillColor(sf::Color::Transparent);
    ring.setOutlineColor(sf::Color(100, 80, 50));
    ring.setOutlineThickness(2 * scale);
    ring.setPosition(x - 4 * scale, y - 4 * scale);
    window.draw(ring);

    drawPirateLine(window, x - 10 * scale, y + 8 * scale, x + 10 * scale, y + 8 * scale, sf::Color(100, 80, 50), 2 * scale);

    sf::VertexArray leftHook(sf::TriangleStrip, 3);
    leftHook[0].position = sf::Vector2f(x - 8 * scale, y + 22 * scale);
    leftHook[1].position = sf::Vector2f(x - 12 * scale, y + 30 * scale);
    leftHook[2].position = sf::Vector2f(x - 4 * scale, y + 30 * scale);
    for (int i = 0; i < 3; i++) leftHook[i].color = sf::Color(100, 80, 50);
    window.draw(leftHook);

    sf::VertexArray rightHook(sf::TriangleStrip, 3);
    rightHook[0].position = sf::Vector2f(x + 8 * scale, y + 22 * scale);
    rightHook[1].position = sf::Vector2f(x + 4 * scale, y + 30 * scale);
    rightHook[2].position = sf::Vector2f(x + 12 * scale, y + 30 * scale);
    for (int i = 0; i < 3; i++) rightHook[i].color = sf::Color(100, 80, 50);
    window.draw(rightHook);
}

void Game::drawCompass(float cx, float cy, float radius) {
    sf::CircleShape outer(radius);
    outer.setOrigin(radius, radius);
    outer.setPosition(cx, cy);
    outer.setFillColor(sf::Color(60, 45, 25));
    outer.setOutlineColor(sf::Color(140, 110, 60));
    outer.setOutlineThickness(3);
    window.draw(outer);

    sf::CircleShape inner(radius * 0.75f);
    inner.setOrigin(radius * 0.75f, radius * 0.75f);
    inner.setPosition(cx, cy);
    inner.setFillColor(sf::Color(45, 35, 20));
    inner.setOutlineColor(sf::Color(100, 80, 45));
    inner.setOutlineThickness(1);
    window.draw(inner);

    float angle = animTimer * 0.5f;
    sf::VertexArray arrow(sf::TriangleStrip, 3);
    arrow[0].position = sf::Vector2f(cx + cosf(angle) * radius * 0.6f, cy + sinf(angle) * radius * 0.6f);
    arrow[1].position = sf::Vector2f(cx + cosf(angle + 2.5f) * radius * 0.2f, cy + sinf(angle + 2.5f) * radius * 0.2f);
    arrow[2].position = sf::Vector2f(cx + cosf(angle - 2.5f) * radius * 0.2f, cy + sinf(angle - 2.5f) * radius * 0.2f);
    for (int i = 0; i < 3; i++) arrow[i].color = TEXT_GOLD;
    window.draw(arrow);

    sf::CircleShape center(3);
    center.setOrigin(3, 3);
    center.setPosition(cx, cy);
    center.setFillColor(sf::Color(160, 130, 60));
    window.draw(center);

    drawTextShadow("N", cx - 5, cy - radius + 5, 12, TEXT_GOLD, false);
    drawTextShadow("S", cx - 4, cy + radius - 16, 12, TEXT_RUM, false);
    drawTextShadow("E", cx + radius - 12, cy - 6, 12, TEXT_RUM, false);
    drawTextShadow("W", cx - radius + 4, cy - 6, 12, TEXT_RUM, false);
}

void Game::drawMapBorder() {
    sf::Color borderColor(100, 75, 40);
    float w = WINDOW_WIDTH, h = WINDOW_HEIGHT;
    float m = 8;

    drawPirateLine(window, m, m, w - m, m, borderColor, 2);
    drawPirateLine(window, w - m, m, w - m, h - m, borderColor, 2);
    drawPirateLine(window, w - m, h - m, m, h - m, borderColor, 2);
    drawPirateLine(window, m, h - m, m, m, borderColor, 2);

    sf::CircleShape corner(4);
    corner.setFillColor(TEXT_GOLD);
    sf::Vector2f corners[] = {
        {m - 2, m - 2}, {w - m - 2, m - 2},
        {m - 2, h - m - 2}, {w - m - 2, h - m - 2}
    };
    for (auto& c : corners) {
        corner.setPosition(c);
        window.draw(corner);
    }
}

// ===== RENDERING =====

void Game::render() {
    window.clear(BG);
    drawMapBorder();
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
    for (int i = 0; i < 5; i++) {
        float x = 100 + i * 220;
        float y = 80 + sin(animTimer * 0.5f + i * 1.2f) * 20;
        drawCompass(x, y, 20 + i * 3);
    }

    drawPirateSkull(40, 180, 1.2f);
    drawPirateAnchor(WINDOW_WIDTH - 80, 200, 1.5f);
    drawPirateSkull(WINDOW_WIDTH - 100, 400, 1.0f);
    drawPirateAnchor(60, 420, 1.3f);

    drawTextShadow(T_TITLE, WINDOW_WIDTH / 2, 60, 56, TEXT_GOLD, true);
    drawTextShadow(T_SUB, WINDOW_WIDTH / 2, 125, 20, TEXT_RUM, true);

    drawPirateRect(window, WINDOW_WIDTH / 2 - 220, 160, 440, 4,
        sf::Color(80, 50, 25), sf::Color(120, 80, 40), 1);

    const char* buttons[] = { T_START, T_RULES, T_SETT, T_EXIT };
    for (int i = 0; i < 4; i++) {
        float y = 190 + i * 75;
        drawButton(buttons[i], WINDOW_WIDTH / 2 - 150, y, 300, 55, false, i == menuSelection);
    }

    drawText(u8"\u2191\u2193 - \u0432\u044B\u0431\u043E\u0440  |  ENTER - \u043F\u043E\u0434\u0442\u0432\u0435\u0440\u0434\u0438\u0442\u044C",
             WINDOW_WIDTH / 2, 520, 16, sf::Color(130, 110, 80), true);

    drawPirateSkull(WINDOW_WIDTH / 2 - 25, 560, 0.9f);
}

void Game::renderSettings() {
    drawTextShadow(T_SETT_T, WINDOW_WIDTH / 2, 55, 40, TEXT_GOLD, true);
    drawPirateAnchor(50, 80, 1.0f);

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
        sf::Color color = (i == settingsSelection) ? sf::Color(255, 200, 80) : TEXT;
        drawText(labels[i], WINDOW_WIDTH / 2 - 250, y, 24, color, false);
        if (strlen(values[i]) > 0) {
            sf::Color vc = (i == settingsSelection) ? sf::Color(80, 180, 80) : sf::Color(100, 180, 220);
            drawText(values[i], WINDOW_WIDTH / 2 + 200, y, 24, vc, false);
        }
    }

    drawText(u8"</> - \u0438\u0437\u043C\u0435\u043D\u0438\u0442\u044C  |  ENTER/ESC - \u043D\u0430\u0437\u0430\u0434",
             WINDOW_WIDTH / 2, 650, 16, sf::Color(130, 110, 80), true);
}

void Game::renderRules() {
    drawTextShadow(T_R_TIT, WINDOW_WIDTH / 2, 50, 40, TEXT_GOLD, true);
    drawCompass(WINDOW_WIDTH - 90, 100, 35);
    drawPirateAnchor(40, 60, 0.8f);

    drawPirateRect(window, 60, 100, WINDOW_WIDTH - 120, 400,
        sf::Color(50, 40, 28), sf::Color(100, 75, 40), 2);

    const char* lines[] = { T_R1, T_R2, T_R3, T_R4, T_R5, T_R6, T_R7, T_R8 };
    for (int i = 0; i < 8; i++) {
        sf::Color color = (i < 5) ? TEXT : sf::Color(170, 155, 125);
        drawText(lines[i], 90, 125 + i * 42, 20, color, false);
    }

    drawTextShadow(T_PRESS, WINDOW_WIDTH / 2, 520, 20, TEXT_GOLD, true);
}

void Game::renderPlacement() {
    drawTextShadow(T_PL_TIT, WINDOW_WIDTH / 2, 15, 28, TEXT_GOLD, true);

    int size = FLEET_SIZES[currentShipIdx];
    bool valid = playerBoard->canPlaceShip(cursorR, cursorC, size, placingHorizontal);
    playerBoard->draw(window, font, cursorR, cursorC, true, size, placingHorizontal, valid);
    drawText(T_YP, P_BX + BOARD_PIXELS / 2 + 20, 50, 18, sf::Color(100, 220, 100), true);

    drawPirateAnchor(WINDOW_WIDTH / 2 - 20, 250, 0.7f);

    float px = P_BX + BOARD_PIXELS + 55;
    drawPirateRect(window, px, P_BY, 260, 430, PANEL_BG, PANEL_BORDER, 2);

    drawText(T_SHIP, px + 15, P_BY + 15, 20, TEXT, false);
    drawText(std::to_string(size) + T_P, px + 15, P_BY + 42, 22, TEXT_GOLD, false);
    drawText(T_DIR, px + 15, P_BY + 80, 16, TEXT, false);
    drawText(placingHorizontal ? T_HOR : T_VER, px + 15, P_BY + 100, 16, sf::Color(100, 200, 255), false);
    if (valid) drawText(T_OK, px + 15, P_BY + 135, 16, sf::Color(60, 180, 60), false);
    else       drawText(T_BAD, px + 15, P_BY + 135, 16, sf::Color(200, 60, 60), false);

    drawText(T_CTRL, px + 15, P_BY + 180, 14, sf::Color(140, 120, 90), false);
    drawText(T_CTR2, px + 15, P_BY + 200, 14, sf::Color(140, 120, 90), false);

    drawText(std::to_string(currentShipIdx) + " / " + std::to_string(FLEET_COUNT), px + 15, P_BY + 250, 20, TEXT_GOLD, false);
    drawText(T_LEFT, px + 15, P_BY + 280, 15, sf::Color(140, 120, 90), false);

    int yPos = P_BY + 305, counts[5] = {0,0,0,0,0};
    for (int i = currentShipIdx; i < FLEET_COUNT; i++) { int s = FLEET_SIZES[i]; if (s >= 1 && s <= 4) counts[4-s]++; }
    for (int deck = 4; deck >= 1; deck--) {
        int cnt = counts[4 - deck];
        if (cnt > 0) {
            std::string line = std::to_string(cnt) + " x " + std::string(deck, '=') + " (" + std::to_string(deck) + "p)";
            drawText(line, px + 15, yPos, 14, sf::Color(100, 170, 230), false);
            yPos += 18;
        }
    }

    drawCompass(px + 130, P_BY + 380, 25);
}

void Game::renderBattle() {
    drawTextShadow(T_BATTLE, WINDOW_WIDTH / 2, 12, 26, TEXT_GOLD, true);
    drawText(T_YP, P_BX + BOARD_PIXELS / 2 + 20, 50, 17, sf::Color(100, 220, 100), true);
    drawText(T_EP, E_BX + BOARD_PIXELS / 2 + 20, 50, 17, sf::Color(220, 100, 80), true);

    playerBoard->draw(window, font, -1, -1, true, 0, true, true);
    enemyBoard->draw(window, font, cursorR, cursorC, false, 0, true, true);

    drawPirateAnchor(WINDOW_WIDTH / 2 - 20, 280, 0.6f);

    drawInfoPanel();

    if (!messages.empty()) {
        float msgY = 540;
        for (auto& m : messages) {
            float alpha = std::min(1.0f, m.timer);
            sf::Color c = m.color;
            c.a = (sf::Uint8)(255 * alpha);
            drawTextShadow(m.text, WINDOW_WIDTH / 2, msgY, 20, c, true);
            msgY -= 26;
        }
    }
}

void Game::renderBotTurn() {
    renderBattle();
    sf::RectangleShape overlay(sf::Vector2f(BOARD_PIXELS + 40, BOARD_PIXELS + 40));
    overlay.setPosition(E_BX + 8, E_BY + 8);
    overlay.setFillColor(sf::Color(25, 20, 12, 100));
    window.draw(overlay);
    drawTextShadow(T_BOT, E_BX + BOARD_PIXELS / 2 + 20, E_BY + BOARD_PIXELS / 2 - 15, 32, sf::Color(230, 180, 40), true);
    int dots = (int)(botTimer * 3) % 4;
    drawTextShadow(std::string(dots, '.'), E_BX + BOARD_PIXELS / 2 + 20, E_BY + BOARD_PIXELS / 2 + 20, 28, sf::Color(230, 180, 40), true);
}

void Game::drawInfoPanel() {
    drawPirateRect(window, INF_X, INF_Y, INF_W, INF_H, PANEL_BG, PANEL_BORDER, 2);

    sf::RectangleShape g1(sf::Vector2f(18, 3)); g1.setPosition(INF_X, INF_Y); g1.setFillColor(TEXT_GOLD); window.draw(g1);
    sf::RectangleShape g2(sf::Vector2f(3, 18)); g2.setPosition(INF_X, INF_Y); g2.setFillColor(TEXT_GOLD); window.draw(g2);
    sf::RectangleShape g3(sf::Vector2f(18, 3)); g3.setPosition(INF_X + INF_W - 18, INF_Y); g3.setFillColor(TEXT_GOLD); window.draw(g3);
    sf::RectangleShape g4(sf::Vector2f(3, 18)); g4.setPosition(INF_X + INF_W - 3, INF_Y); g4.setFillColor(TEXT_GOLD); window.draw(g4);

    drawText(std::string(T_VY) + std::to_string(playerBoard->getShipsAlive()) + T_KOR, INF_X + 30, INF_Y + 16, 20, sf::Color(100, 220, 100), false);
    drawText(std::string(T_VRAG) + std::to_string(enemyBoard->getShipsAlive()) + T_KOR, INF_X + 30, INF_Y + 48, 20, sf::Color(220, 100, 80), false);

    std::string aim = std::string(T_AIM) + char('A' + cursorC) + std::to_string(cursorR + 1);
    drawTextShadow(aim, INF_X + INF_W / 2, INF_Y + 22, 26, TEXT_GOLD, true);

    int sunkP = 10 - enemyBoard->getShipsAlive();
    int sunkE = 10 - playerBoard->getShipsAlive();
    drawText(std::string(T_SUNK) + std::to_string(sunkP), INF_X + INF_W - 200, INF_Y + 16, 18, sf::Color(230, 170, 50), false);
    drawText(std::string(T_DECK) + std::to_string(sunkP * 2 + sunkE), INF_X + INF_W - 200, INF_Y + 48, 18, sf::Color(190, 155, 80), false);

    drawText(T_HINT, INF_X + INF_W / 2, INF_Y + 80, 15, sf::Color(130, 110, 80), true);
    std::string ft = std::string(T_1ST) + (playerTurnFirst ? T_1YOU : T_1BOT);
    drawText(ft, INF_X + 30, INF_Y + 80, 15, sf::Color(100, 190, 230), false);

    drawPirateSkull(INF_X + INF_W - 50, INF_Y + 70, 0.5f);
}

void Game::renderVictory() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(15, 35, 15, 220));
    window.draw(overlay);

    float cx = WINDOW_WIDTH / 2, cy = 180;
    drawPirateRect(window, cx - 60, cy, 120, 70, sf::Color(100, 60, 25), sf::Color(140, 100, 45), 2);
    drawPirateRect(window, cx - 60, cy - 25, 120, 28, sf::Color(85, 50, 20), sf::Color(130, 90, 40), 2);
    drawPirateRect(window, cx - 8, cy + 25, 16, 18, sf::Color(180, 160, 60), sf::Color(220, 190, 70), 2);

    for (int i = 0; i < 15; i++) {
        sf::CircleShape coin(4 + (i % 3));
        coin.setFillColor(sf::Color(220 + (i % 2) * 35, 190, 40));
        coin.setPosition(cx - 50 + (i * 7) + sin(i * 2.3f) * 5, cy + 72 + cos(i * 1.7f) * 4);
        window.draw(coin);
    }

    drawTextShadow(T_WIN, WINDOW_WIDTH / 2, 300, 56, sf::Color(50, 220, 80), true);
    drawTextShadow(T_WIN2, WINDOW_WIDTH / 2, 380, 24, TEXT, true);

    for (int i = 0; i < 10; i++) {
        sf::CircleShape sparkle(2 + (int)(sin(animTimer * 3 + i) * 1.5f));
        sparkle.setPosition(200 + (rand() % 700), 100 + (rand() % 400));
        sparkle.setFillColor(sf::Color(255, 230, 100, 120 + (int)(sin(animTimer * 2 + i) * 60)));
        window.draw(sparkle);
    }

    drawPirateSkull(WINDOW_WIDTH / 2 - 25, 420, 0.8f);
    drawTextShadow(T_MNU2, WINDOW_WIDTH / 2, 500, 20, TEXT_GOLD, true);
}

void Game::renderDefeat() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(35, 10, 10, 220));
    window.draw(overlay);

    drawPirateSkull(WINDOW_WIDTH / 2 - 45, 80, 1.6f);

    drawTextShadow(T_LOSE, WINDOW_WIDTH / 2, 300, 56, sf::Color(220, 40, 40), true);
    drawTextShadow(T_LOSE2, WINDOW_WIDTH / 2, 380, 24, TEXT, true);

    for (int i = 0; i < 8; i++) {
        sf::CircleShape ember(2);
        ember.setPosition(150 + (rand() % 800), 50 + (rand() % 500));
        int a = 50 + (int)(sin(animTimer * 4 + i * 1.5f) * 40);
        ember.setFillColor(sf::Color(200 + a, 60 + a, 0, a * 2));
        window.draw(ember);
    }

    drawTextShadow(T_MNU2, WINDOW_WIDTH / 2, 500, 20, TEXT_GOLD, true);
}
