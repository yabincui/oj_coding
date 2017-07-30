class Solution {
public:
    int minSteps(int n) {
        if (n == 1) return 0;
        int* m = new int[1001 * 1001];
        memset(m, 0x40, sizeof(int) * 1001 * 1001);
        int (*dp)[1001] = (int (*)[1001])m;
        //vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
        dp[0][0] = 0;
        dp[1][0] = 0;
        int min_res = INT_MAX;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (dp[i][j] == INT_MAX) continue;
                // copy
                if (j < i) {
                    dp[i][i] = min(dp[i][i], dp[i][j] + 1);
                }
                // paste
                if (j > 0) {
                    int t = i + j;
                    if (t > n) {
                    } else if (t == n) {
                        min_res = min(min_res, dp[i][j] + 1);
                    } else {
                        dp[t][j] = min(dp[t][j], dp[i][j] + 1);
                    }
                }
            }
        }
        delete m;
        return min_res;
    }
};
