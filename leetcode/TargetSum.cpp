class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int total = 0;
        for (auto& v : nums) {
            total += v;
        }
        int value_count = total * 2 + 1;
        int dp[value_count];
        int new_dp[value_count];
        memset(dp, 0, sizeof(dp));
        dp[total + 0] = 1;
        for (auto& v : nums) {
            memset(new_dp, 0, sizeof(new_dp));
            // use positive v.
            for (int i = 0; i < value_count; ++i) {
                if (dp[i] != 0) {
                    new_dp[i + v] += dp[i];
                    new_dp[i - v] += dp[i];
                }
            }
            memcpy(dp, new_dp, sizeof(dp));
        }
        int t = S + total;
        if (t >= 0 && t < value_count) {
            return dp[t];
        }
        return 0;
    }
};
