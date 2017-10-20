class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int res = 0;
        for (int r = 0; r < board.size(); ++r) {
            for (int c = 0; c < board[r].size(); ++c) {
                if (board[r][c] == 'X') {
                    if (r > 0 && board[r-1][c] == 'X' || c > 0 && board[r][c-1] == 'X') {
                        continue;
                    }
                    res++;
                }
            }
        }
        return res;
    }
};