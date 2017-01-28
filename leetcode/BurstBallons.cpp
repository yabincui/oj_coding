// 312. Burst Balloons
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        int dp[n+2][n+2];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i <= n; ++i) {
            dp[i][i+1] = 0;
        }
        for (int step = 2; step <= n + 1; ++step) {
            for (int i = 0; i <= n + 1 - step; ++i) {
                int j = i + step;
                int max_coin = 0;
                int mul = 1;
                if (i > 0) mul *= nums[i-1];
                if (j < n + 1) mul *= nums[j-1];
                for (int k = i + 1; k < j; ++k) {
                    int tmp = nums[k-1] * mul + dp[i][k] + dp[k][j];
                    max_coin = max(max_coin, tmp);
                }
                dp[i][j] = max_coin;
            }
        }
        return dp[0][n+1];
    }
};
