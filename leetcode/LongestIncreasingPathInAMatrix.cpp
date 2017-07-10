class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        if (rows == 0) return 0;
        int cols = matrix[0].size();
        if (cols == 0) return 0;
        vector<vector<int>> dp(rows, vector<int>(cols, 1));
        vector<pair<int, int>> v;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                v.push_back(make_pair(matrix[r][c], r * cols + c));
            }
        }
        sort(v.begin(), v.end());
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        int res = 0;
        for (auto& pair : v) {
            int r = pair.second / cols;
            int c = pair.second % cols;
            for (int i = 0; i < 4; ++i) {
                int pr = r + dr[i];
                int pc = c + dc[i];
                if (pr < 0 || pr >= rows || pc < 0 || pc >= cols || matrix[pr][pc] >= matrix[r][c]) {
                    continue;
                }
                dp[r][c] = max(dp[r][c], dp[pr][pc] + 1);
            }
            res = max(res, dp[r][c]);
        }
        return res;
    }
};
