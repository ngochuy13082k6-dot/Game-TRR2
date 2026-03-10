#include "Map.h"
#include <fstream>
#include <sstream>

// Hàm đọc bản đồ tự động co giãn theo số lượng dữ liệu trong file text
bool Map::loadFromFile(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    // Đọc từng dòng
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<int> row;
        std::stringstream ss(line);
        int val;
        // Đọc từng số trong dòng đó
        while (ss >> val) row.push_back(val);
        grid.push_back(row); // Thêm dòng vào lưới
    }
    file.close();

    // Cập nhật số hàng, cột thực tế
    rows = grid.size();
    if (rows > 0) cols = grid[0].size();

    // Đặt màu xám cho bức tường
    wallRect.setFillColor(sf::Color(100, 100, 100));
    return true;
}

// Hàm kiểm tra va chạm: Không ra ngoài bản đồ và phải là số 0 (đường đi)
bool Map::isValid(int r, int c) const {
    return r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == 0;
}

// Duyệt qua toàn bộ lưới, cứ chỗ nào là số 1 thì đặt khối vuông vào và vẽ
void Map::draw(sf::RenderWindow& window, int tileSize) {
    wallRect.setSize(sf::Vector2f((float)tileSize, (float)tileSize));
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                wallRect.setPosition((float)(c * tileSize), (float)(r * tileSize));
                window.draw(wallRect);
            }
        }
    }
}