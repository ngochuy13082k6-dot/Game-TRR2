#include "Game.h"
#include <iostream>

int main() {
    Game myGame; // Khởi tạo cỗ máy Game

    // Khởi động các thiết lập ban đầu (như load map, mở cửa sổ)
    if (!myGame.init()) {
        std::cout << "Loi load map.txt! Kiem tra lai vi tri file." << std::endl;
        system("pause"); // Dừng Console để đọc lỗi
        return -1;
    }

    // Chạy vòng lặp vô tận của Game cho đến khi người dùng tắt cửa sổ
    myGame.run();

    return 0;
}