// 375. Guess Number Higher or Lower II
class Solution {
public:
    int getMoneyAmount(int n) {
        if (n == 1) {
            return 0;
        }
        int dp[n+1][n+1];
        memset(dp, -1, sizeof(dp));
        for (int i = 1; i <= n; ++i) {
            dp[i][i] = 0;
        }
        for (int step = 2; step <= n; ++step) {
            for (int i = 1; i <= n - step + 1; ++i) {
                int j = i + step - 1;
                int min_val = INT_MAX;
                for (int t = i; t <= j; ++t) {
                    int tmp = 0;
                    if (t > i) {
                        tmp = dp[i][t-1];
                    }
                    if (t < j) {
                        tmp = max(tmp, dp[t+1][j]);
                    }
                    tmp += t;
                    if (min_val > tmp) {
                        min_val = tmp;
                    }
                }
                dp[i][j] = min_val;
            }
        }
        return dp[1][n];
    }
};
