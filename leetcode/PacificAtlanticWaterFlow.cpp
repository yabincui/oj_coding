// 417 Pacific Atlantic Water Flow
class Solution {
public:
    struct Pos {
      int r, c;
      Pos(int r, int c) : r(r), c(c) {}
    };
    
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int, int>> res;
        int rows = matrix.size();
        if (rows == 0) return res;
        int cols = matrix[0].size();
        if (cols == 0) return res;
        bool okUp[rows][cols];
        bool okDown[rows][cols];
        memset(okDown, 0, sizeof(okDown));
        memset(okUp, 0, sizeof(okUp));
        queue<Pos> upQ;
        queue<Pos> downQ;
        for (int c = 0; c < cols; ++c) {
            okUp[0][c] = true;
            upQ.push(Pos(0, c));
            okDown[rows-1][c] = true;
            downQ.push(Pos(rows-1, c));
        }
        for (int r = 0; r < rows; ++r) {
            okUp[r][0] = true;
            upQ.push(Pos(r, 0));
            okDown[r][cols - 1] = true;
            downQ.push(Pos(r, cols - 1));
        }
        while (!upQ.empty()) {
            Pos cur = upQ.front(); upQ.pop();
            for (int i = 0; i < 4; ++i) {
                int r = cur.r + dr[i];
                int c = cur.c + dc[i];
                if (r >= 0 && r < rows && c >= 0 && c < cols && !okUp[r][c] && matrix[r][c] >= matrix[cur.r][cur.c]) {
                    okUp[r][c] = true;
                    upQ.push(Pos(r, c));
                }
            }
        }
        while (!downQ.empty()) {
            Pos cur = downQ.front(); downQ.pop();
            for (int i = 0; i < 4; ++i) {
                int r = cur.r + dr[i];
                int c = cur.c + dc[i];
                if (r >= 0 && r < rows && c >= 0 && c < cols && !okDown[r][c] && matrix[r][c] >= matrix[cur.r][cur.c]) {
                    okDown[r][c] = true;
                    downQ.push(Pos(r, c));
                }
            }
        }
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (okUp[r][c] && okDown[r][c]) {
                    res.push_back(make_pair(r, c));
                }
            }
        }
        return res;
    }
};
