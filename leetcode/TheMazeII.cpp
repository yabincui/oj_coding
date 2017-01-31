// 499. The Maze II
class Solution {
public:
    enum {
      UP = 0,
      RIGHT = 1,
      DOWN = 2,
      LEFT = 3,
    };
    
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};
    char sd[4] = {'u', 'r', 'd', 'l'};
    int tryd[4] = {DOWN, LEFT, RIGHT, UP};

    // min dist from [r][c][dir].
    int m[30][30][4];

    int buildKey(int r, int c, int d) {
        return (r << 10) | (c << 5) | d;
    }
    
    void getKey(int key, int& r, int& c, int& d) {
        d = key & 0x1f;
        key >>= 5;
        c = key & 0x1f;
        key >>= 5;
        r = key & 0x1f;
    }
    
    bool InRange(int r, int c, vector<vector<int>>& maze) {
        return r >= 0 && r < maze.size() && c >= 0 && c < maze[0].size();
    }

    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        memset(m, -1, sizeof(m));
        queue<int> q;
        for (int d = 0; d < 4; ++d) {
            m[hole[0]][hole[1]][d] = 0;
            q.push(buildKey(hole[0], hole[1], d));
        }
        while (!q.empty()) {
            int key = q.front();
            q.pop();
            int r, c, d;
            getKey(key, r, c, d);
            if (r == ball[0] && c == ball[1]) {
                break;
            }
            int rd = (d + 2) % 4;
            int nr = r + dr[rd];
            int nc = c + dc[rd];
            int dist = m[r][c][d];
            
            if (InRange(nr, nc, maze) && maze[nr][nc] != 1) {
                if (m[nr][nc][d] == -1 || m[nr][nc][d] > dist + 1) {
                    m[nr][nc][d] = dist + 1;
                    q.push(buildKey(nr, nc, d));
                }
            }
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (!InRange(nr, nc, maze) || maze[nr][nc] == 1) {
                    rd = (i + 2) % 4;
                    nr = r + dr[rd];
                    nc = c + dc[rd];
                    if (InRange(nr, nc, maze) && maze[nr][nc] != 1) {
                        if (m[nr][nc][i] == -1 || m[nr][nc][i] > dist + 1) {
                            m[nr][nc][i]  = dist + 1;
                            q.push(buildKey(nr, nc, i));
                        }
                    }
                }
            }
        }
        string result;
        int r = ball[0];
        int c = ball[1];
        int d;
        int i;
        int rd;
        for (i = 0; i < 4; ++i) {
            d = tryd[i];
            rd = (d + 2) % 4;
            printf("try d = %c, m[%d][%d][%d] = %d\n", sd[d], r, c, d, m[r][c][d]);
            if (m[r][c][d] != -1) {
                break;
            }
        }
        if (i == 4) {
            return "impossible";
        }
        //printf("hole r = %d, c = %d, d = %c\n", r, c, sd[d]);
        int cur = m[r][c][d];
        while (r != hole[0] || c != hole[1]) {
            //printf("nr = %d, nc = %d, cur = %d, d = %c\n", r, c, cur, sd[d]);
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (m[nr][nc][d] != cur - 1) {
                result.push_back(sd[d]);
                for (int i = 0; i < 4; ++i) {
                    d = tryd[i];
                    if (m[nr][nc][d] == cur - 1) {
                        break;
                    }
                }
            }
            
            cur--;
            r = nr;
            c = nc;
        }
        result.push_back(sd[d]);
        return result;
    }
};


