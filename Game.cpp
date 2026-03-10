#include "Game.h"
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace sf;

// Đã fix lỗi "uninitialized": Khởi tạo toàn bộ biến bằng 0 ngay từ đầu
Game::Game() : currentState(MENU), fogEnabled(false), delayCounter(0),
tileSize(0), windowWidth(0), windowHeight(0),
startPos{ 0, 0 }, playerPos{ 0, 0 }, goalPos{ 0, 0 } {
}

bool Game::init() {
    if (!map.loadFromFile("map.txt")) return false;

    tileSize = min(1200 / map.getCols(), 800 / map.getRows());
    windowWidth = map.getCols() * tileSize;
    windowHeight = map.getRows() * tileSize;

    window.create(VideoMode(windowWidth, windowHeight), "Maze OOP - Pro Architecture");
    window.setFramerateLimit(60);

    if (!font.loadFromFile("PressStart2P-Regular.ttf")) cout << "Loi font!\n";

    startPos = { 1, 1 };
    playerPos = startPos;
    goalPos = { map.getRows() - 2, map.getCols() - 2 };

    initGraphics();
    return true;
}

void Game::initGraphics() {
    playerRect.setSize(Vector2f((float)(tileSize - 2), (float)(tileSize - 2)));
    playerRect.setFillColor(Color::Blue);

    goalRect.setSize(Vector2f((float)(tileSize - 2), (float)(tileSize - 2)));
    goalRect.setFillColor(Color::Red);

    fogRect.setSize(Vector2f((float)tileSize, (float)tileSize));
    overlay.setSize(Vector2f((float)windowWidth, (float)windowHeight));
    overlay.setFillColor(Color(0, 0, 0, 230));

    auto setupText = [&](Text& t, string str, int size, float yOffset, Color color = Color::White) {
        t.setFont(font); t.setString(str); t.setCharacterSize(size); t.setFillColor(color);
        FloatRect bounds = t.getLocalBounds();
        t.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        t.setPosition((float)windowWidth / 2.0f, (float)windowHeight / 2.0f + yOffset);
        };

    setupText(titleText, "MAZE GAME", 60, -100.0f, Color::Cyan);
    setupText(startText, "Nhan [ENTER] de bat dau", 20, 50.0f);
    setupText(pauseText, "=== PAUSED ===\n\n[H]: Rada tim duong\n\n[D]: Bat/Tat Suong mu\n\n[ESC]: Tiep tuc", 20, 60.0f);
    setupText(victoryText, "CHUC MUNG!", 50, -40.0f, Color::Yellow);
    setupText(restartText, "Nhan [ENTER] de choi lai", 18, 40.0f);
}

void Game::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) window.close();

        if (event.type == Event::KeyPressed) {
            if (currentState == MENU) {
                if (event.key.code == Keyboard::Enter) currentState = PLAYING;
            }
            else if (currentState == PAUSED) {
                if (event.key.code == Keyboard::Escape) currentState = PLAYING;
                if (event.key.code == Keyboard::H) bfs.start(playerPos, map.getRows(), map.getCols());
                if (event.key.code == Keyboard::D) fogEnabled = !fogEnabled;
            }
            else if (currentState == VICTORY) {
                if (event.key.code == Keyboard::Enter) {
                    playerPos = startPos;
                    bfs.clear();
                    fogEnabled = false;
                    currentState = PLAYING;
                }
            }
            else if (currentState == PLAYING) {
                if (event.key.code == Keyboard::Escape) {
                    currentState = PAUSED;
                }
                else {
                    Point next = playerPos;
                    if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) next.r--;
                    if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) next.r++;
                    if (event.key.code == Keyboard::A || event.key.code == Keyboard::Left) next.c--;
                    if (event.key.code == Keyboard::D || event.key.code == Keyboard::Right) next.c++;

                    if (map.isValid(next.r, next.c)) {
                        playerPos = next;
                        if (bfs.isRunning() || bfs.isFinished()) bfs.clear();
                        if (playerPos == goalPos) currentState = VICTORY;
                    }
                }
            }
        }
    }
}

void Game::update() {
    delayCounter++;
    if (delayCounter % 2 == 0) bfs.update(goalPos, map);
}

void Game::renderFog() {
    if (!fogEnabled) return;
    for (int r = 0; r < map.getRows(); r++) {
        for (int c = 0; c < map.getCols(); c++) {
            // Đã fix lỗi "possible loss of data": Ép toàn bộ biểu thức về (float)
            float dist = (float)sqrt(pow(r - playerPos.r, 2) + pow(c - playerPos.c, 2));
            float maxSight = 4.5f, clearSight = 1.5f;
            if (dist > maxSight) {
                fogRect.setFillColor(Color(0, 0, 0, 255));
                fogRect.setPosition((float)(c * tileSize), (float)(r * tileSize));
                window.draw(fogRect);
            }
            else if (dist > clearSight) {
                float alpha = ((dist - clearSight) / (maxSight - clearSight)) * 255.0f;
                fogRect.setFillColor(Color(0, 0, 0, (Uint8)alpha));
                fogRect.setPosition((float)(c * tileSize), (float)(r * tileSize));
                window.draw(fogRect);
            }
        }
    }
}

void Game::renderUI() {
    if (currentState == MENU) {
        window.draw(overlay); window.draw(titleText); window.draw(startText);
    }
    else if (currentState == PAUSED) {
        window.draw(overlay); window.draw(titleText); window.draw(pauseText);
    }
    else if (currentState == VICTORY) {
        window.draw(overlay); window.draw(victoryText); window.draw(restartText);
    }
}

void Game::render() {
    window.clear(Color::Black);
    map.draw(window, tileSize);

    goalRect.setPosition((float)(goalPos.c * tileSize + 1), (float)(goalPos.r * tileSize + 1));
    window.draw(goalRect);

    playerRect.setPosition((float)(playerPos.c * tileSize + 1), (float)(playerPos.r * tileSize + 1));
    window.draw(playerRect);

    renderFog();
    bfs.draw(window, tileSize);
    renderUI();

    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}