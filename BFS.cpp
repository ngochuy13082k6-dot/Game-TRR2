#include "BFS.h"

BFS::BFS() : running(false), finished(false) {
    dx[0] = -1; dx[1] = 1; dx[2] = 0; dx[3] = 0;
    dy[0] = 0;  dy[1] = 0; dy[2] = -1; dy[3] = 1;
    waveRect.setFillColor(sf::Color(100, 200, 255));
    pathRect.setFillColor(sf::Color::Yellow);
}

void BFS::start(Point start, int rows, int cols) {
    while (!queue.empty()) queue.pop();
    visited.assign(rows, std::vector<bool>(cols, false));
    parent.assign(rows, std::vector<Point>(cols, { -1, -1 }));
    finalPath.clear();

    queue.push(start);
    visited[start.r][start.c] = true;
    running = true;
    finished = false;
}

void BFS::update(Point goal, const Map& map) {
    if (!running || queue.empty()) return;

    Point current = queue.front();
    queue.pop();

    if (current == goal) {
        running = false;
        finished = true;
        Point cur = goal;
        while (parent[cur.r][cur.c].r != -1) {
            finalPath.push_back(cur);
            cur = parent[cur.r][cur.c];
        }
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nr = current.r + dx[i];
        int nc = current.c + dy[i];
        if (map.isValid(nr, nc) && !visited[nr][nc]) {
            visited[nr][nc] = true;
            parent[nr][nc] = current;
            queue.push({ nr, nc });
        }
    }
}

void BFS::clear() {
    running = false;
    finished = false;
    finalPath.clear();
    visited.clear();
    while (!queue.empty()) queue.pop();
}

void BFS::draw(sf::RenderWindow& window, int tileSize) {
    if (visited.empty()) return;

    waveRect.setSize(sf::Vector2f((float)(tileSize - 2), (float)(tileSize - 2)));
    pathRect.setSize(sf::Vector2f((float)(tileSize * 0.6f), (float)(tileSize * 0.6f)));

    for (int r = 0; r < (int)visited.size(); r++) {
        for (int c = 0; c < (int)visited[0].size(); c++) {
            if (visited[r][c]) {
                waveRect.setPosition((float)(c * tileSize + 1), (float)(r * tileSize + 1));
                window.draw(waveRect);
            }
        }
    }

    float offset = tileSize * 0.2f;
    for (Point p : finalPath) {
        pathRect.setPosition((float)(p.c * tileSize + offset), (float)(p.r * tileSize + offset));
        window.draw(pathRect);
    }
}
