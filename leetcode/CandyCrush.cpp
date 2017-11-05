class Solution {
    
    
    
    bool canMark(vector<vector<int>>& board, int r, int c) {
        if (board[r][c] == 0) {
            return false;
        }
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        int need = board[r][c];
        vector<int> count(4, 0);
        for (int d = 0; d < 4; ++d) {
            int tr = r;
            int tc = c;
            for (int i = 0; i < 2; ++i) {
                tr += dr[d];
                tc += dc[d];
                if (tr < 0 || tr >= board.size() || tc < 0 || tc >= board[0].size() || abs(board[tr][tc]) != need) {
                    break;
                }
                count[d]++;
            }
        }
        if (count[0] + count[1] >= 2 || count[2] + count[3] >= 2) {
            return true;
        }
        return false;
    }
    
    bool markBoard(vector<vector<int>>& board) {
        int rows = board.size();
        int cols = board[0].size();
        bool hasMark = false;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (canMark(board, r, c)) {
                    //printf("mark (%d, %d) %d\n", r, c, board[r][c]);
                    board[r][c] = -board[r][c];
                    hasMark = true;
                }
            }
        }
        return hasMark;
    }
    
    void moveBoard(vector<vector<int>>& board) {
        for (int c = 0; c < board[0].size(); ++c) {
            int tr = board.size() - 1;
            for (int r = board.size() - 1; r >= 0; --r) {
                if (board[r][c] > 0) {
                    board[tr--][c] = board[r][c];
                }
            }
            for (; tr >= 0; --tr) {
                board[tr][c] = 0;
            }
        }
    }
    
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        while (true) {
            //printf("turn\n");
            if (!markBoard(board)) {
                break;
            }
            moveBoard(board);
        }
        return board;
    }
};
