class Solution {
    
    int getNeighbors(vector<vector<int>>& board, int r, int c) {
        int res = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int dr = i + r;
                int dc = j + c;
                if (dr < 0 || dr >= board.size() || dc < 0 || dc >= board[0].size()) {
                    
                } else if (board[dr][dc] & 1) {
                    res++;
                }
            }
        }
        return res;
    }
    
public:
    void gameOfLife(vector<vector<int>>& board) {
        int rows = board.size();
        if (rows == 0) return;
        int cols = board[0].size();
        if (cols == 0) return;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int neighbors = getNeighbors(board, r, c);
                if (board[r][c] & 1) {
                    if (neighbors < 2) {
                        board[r][c] &= ~2;
                    } else if (neighbors <= 3) {
                        board[r][c] |= 2;
                    } else {
                        board[r][c] &= ~2;
                    }
                } else {
                    if (neighbors == 3) {
                        board[r][c] |= 2;
                    }
                }
            }
        }
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                board[r][c] >>= 1;
            }
        }
    }
};
