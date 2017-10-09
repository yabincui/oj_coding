class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixSum(n + 1);
        prefixSum[0] = 0;
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = nums[i];
        }
        for (int step = 2; step <= n; step++) {
            for (int i = 0; i + step <= n; ++i) {
                int j = i + step - 1;
                int sum = prefixSum[j + 1] - prefixSum[i];
                dp[i][j] = max(sum - dp[i+1][j], sum - dp[i][j-1]);
            }
        }
        return dp[0][n-1] * 2 >= prefixSum[n];
    }
};
