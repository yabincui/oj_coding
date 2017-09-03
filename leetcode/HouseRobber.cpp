class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = nums[i];
        }
        for (int step = 2; step <= n; ++step) {
            for (int i = 0; i + step <= n; ++i) {
                int j = i + step - 1;
                int maxValue = 0;
                for (int k = i; k <= j; ++k) {
                    int value = nums[k];
                    if (k - 2 >= i) {
                        value += dp[i][k-2];
                    }
                    if (k + 2 <= j) {
                        value += dp[k + 2][j];
                    }
                    maxValue = max(maxValue, value);
                }
                dp[i][j] = maxValue;
            }
        }
        return dp[0][n-1];
    }
};
