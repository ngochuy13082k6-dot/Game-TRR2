#pragma once
#include "Common.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>

class BFS {
public:
    BFS();
    void start(Point start, int rows, int cols); // Khởi động Rada từ vị trí hiện tại
    void update(Point goal, const Map& map);     // Loang sóng đi tiếp 1 bước
    void draw(sf::RenderWindow& window, int tileSize); // Vẽ sóng và đường đi
    void clear(); // Xóa sạch dữ liệu Rada

    bool isRunning() const { return running; }
    bool isFinished() const { return finished; }

private:
    std::queue<Point> queue;                         // Hàng đợi chứa các ô đang duyệt
    std::vector<std::vector<bool>> visited;          // Mảng đánh dấu ô đã đi qua
    std::vector<std::vector<Point>> parent;          // Mảng lưu vết (để tìm đường quay ngược lại)
    std::vector<Point> finalPath;                    // Đường đi màu vàng cuối cùng

    bool running;
    bool finished;

    int dx[4]; // Mảng di chuyển cột
    int dy[4]; // Mảng di chuyển hàng

    sf::RectangleShape waveRect; // Khối vẽ sóng xanh
    sf::RectangleShape pathRect; // Khối vẽ đường vàng
};