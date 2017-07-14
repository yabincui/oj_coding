class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int dp[101][101];
        memset(dp, 0, sizeof(dp));
        for (auto& s : strs) {
            int count[2];
            count[0] = count[1] = 0;
            for (auto c : s) {
                if (c == '0') count[0]++;
                else count[1]++;
            }
            for (int i = count[0]; i <= m; ++i) {
                for (int j = count[1]; j <= n; ++j) {
                    dp[i-count[0]][j-count[1]] = max(dp[i][j] + 1, dp[i-count[0]][j-count[1]]);
                }
            }
        }
        int res = 0;
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j <= n; ++j) {
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }
};
