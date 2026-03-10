
#pragma once // Lệnh này giúp tránh việc thư viện bị include (gọi) nhiều lần gây lỗi

// Enum lưu trữ các trạng thái (màn hình) của game
enum GameState {
    MENU,       // Màn hình chính lúc mới vào
    PLAYING,    // Đang trong màn chơi
    PAUSED,     // Tạm dừng (Mở Menu con)
    VICTORY     // Màn hình chúc mừng chiến thắng
};

// Cấu trúc Point để lưu tọa độ lưới (Hàng, Cột) thay vì tọa độ pixel (X, Y)
struct Point {
    int r; // Row (Hàng)
    int c; // Column (Cột)

    // Nạp chồng toán tử == để dễ dàng so sánh 2 điểm (ví dụ: playerPos == goalPos)
    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }
};