#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

char getCmd() {
    char cmd;
    string s = "ICLVHKFSX";
    while (true) {
        cmd = getchar();
        if (s.find(cmd) != string::npos) {
            return cmd;
        }
        while (cmd != '\n') {
            cmd = getchar();
        }
    }
}

class Image {
public:
    void createImg(int r, int c) {
        img.resize(r);
        for (auto& line : img) {
            line.resize(c);
        }
        clearImg();
    }

    void clearImg() {
        setColor(1, 1, img[0].size(), img.size(), 'O');
    }

    void setColor(int x1, int y1, int x2, int y2, char color) {
        if (x1 > x2) {
            swap(x1, x2);
        }
        if (y1 > y2) {
            swap(y1, y2);
        }
        x1--; y1--; x2--; y2--;
        for (int x = x1; x <= x2; ++x) {
            for (int y = y1; y <= y2; ++y) {
                img[y][x] = color;
            }
        }
    }

    void fillColor(int x, int y, char color) {
        x--; y--;
        char origin_color = img[y][x];
        if (origin_color == color) return;
        img[y][x] = color;
        queue<pair<int, int>> q;
        q.push(make_pair(x, y));
        int dx[] = {0, 0, -1, 1};
        int dy[] = {-1, 1, 0, 0};
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = cur.first + dx[i];
                int ny = cur.second + dy[i];
                if (nx < 0 || nx >= img[0].size() || ny < 0 || ny >= img.size() || img[ny][nx] != origin_color) {
                    continue;
                }
                img[ny][nx] = color;
                q.push(make_pair(nx, ny));
            }
        } 
    }

    void printImg() {
        for (auto& line : img) {
            printf("%s\n", line.c_str());
        }
    }

private:
    vector<string> img;
};

int main() {
    freopen("GraphicalEditor.in", "r", stdin);
    Image img;
    while (true) {
        char cmd = getCmd();
        char color[2];
        int x1, y1, x2, y2;
        if (cmd == 'X') {
            break;
        }
        switch (cmd) {
            case 'I': {
                int m, n;
                scanf("%d%d", &m, &n);
                img.createImg(n, m);
                break;
            }
            case 'C': {
                img.clearImg();
                break;
            }
            case 'L': {
                scanf("%d%d%s", &x1, &y1, color);
                img.setColor(x1, y1, x1, y1, color[0]);
                break;
            }
            case 'V': {
                scanf("%d%d%d%s", &x1, &y1, &y2, color);
                img.setColor(x1, min(y1, y2), x1, max(y1, y2), color[0]);
                break;
            }
            case 'H': {
                scanf("%d%d%d%s", &x1, &x2, &y1, color);
                img.setColor(min(x1, x2), y1, max(x1, x2), y1, color[0]);
                break;
            }
            case 'K': {
                scanf("%d%d%d%d%s", &x1, &y1, &x2, &y2, color);
                img.setColor(x1, y1, x2, y2, color[0]);
                break;
            }
            case 'F': {
                scanf("%d%d%s", &x1, &y1, color);
                img.fillColor(x1, y1, color[0]);
                break;
            }
            case 'S': {
                char name[20];
                scanf("%s", &name);
                printf("%s\n", name);
                img.printImg();
                break;
            }
        }
    }
}
