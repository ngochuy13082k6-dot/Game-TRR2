
#pragma once
#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Map.h"
#include "BFS.h"

// Class Game là hệ thống đầu não, kết nối Màn hình, Map, Người chơi và BFS lại với nhau
class Game {
public:
    Game();
    bool init(); // Hàm nạp dữ liệu ban đầu
    void run();  // Hàm chạy Vòng lặp Game (Game Loop)

private:
    void processEvents(); // Xử lý nhấn phím, click chuột
    void update();        // Cập nhật logic (toán học, tọa độ)
    void render();        // Vẽ mọi thứ lên màn hình
    void initGraphics();  // Cài đặt thông số cho các khối màu và chữ
    void renderFog();     // Vẽ hiệu ứng Sương mù
    void renderUI();      // Vẽ Giao diện Menu

    sf::RenderWindow window; // Cửa sổ chính của game
    sf::Font font;           // Font chữ retro
    GameState currentState;  // Trạng thái game hiện tại
    bool fogEnabled;         // Cờ hiệu bật/tắt sương mù

    int tileSize, windowWidth, windowHeight, delayCounter;

    Map map; // Đối tượng bản đồ
    BFS bfs; // Đối tượng tìm đường

    Point startPos, playerPos, goalPos; // Tọa độ các thực thể

    // Các thành phần vẽ (Shapes & Texts)
    sf::RectangleShape playerRect, goalRect, overlay, fogRect;
    sf::Text titleText, startText, pauseText, victoryText, restartText;
};