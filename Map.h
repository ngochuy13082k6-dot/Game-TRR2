#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map {
public:
    // Các hàm công khai (bên ngoài có thể gọi)
    bool loadFromFile(std::string filename);  // Đọc file map.txt
    bool isValid(int r, int c) const;         // Kiểm tra ô (r, c) có đi được không
    int getRows() const { return rows; }      // Lấy số hàng
    int getCols() const { return cols; }      // Lấy số cột
    void draw(sf::RenderWindow& window, int tileSize); // Vẽ bức tường lên màn hình

private:
    // Các biến nội bộ (chỉ Map mới được động vào)
    std::vector<std::vector<int>> grid; // Mảng 2 chiều lưu bản đồ
    int rows = 0;
    int cols = 0;
    sf::RectangleShape wallRect; // Khối hình chữ nhật dùng để vẽ tường
};