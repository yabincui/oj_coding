class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<int> dp(n);
        vector<int> ways(n);
        dp[0] = 1;
        ways[0] = 1;
        for (int i = 1; i < n; ++i) {
            int maxLen = 0;
            int maxWay = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[i] <= nums[j]) continue;
                if (dp[j] > maxLen) {
                    maxLen = dp[j];
                    maxWay = ways[j];
                } else if (dp[j] == maxLen) {
                    maxWay += ways[j];
                }
            }
            dp[i] = maxLen + 1;
            ways[i] = maxWay;
            //printf("dp[%d] = %d, ways = %d\n", i, dp[i], ways[i]);
        }
        int result = 0;
        int maxLen = 0;
        for (int i = 0; i < n; ++i) {
            if (dp[i] > maxLen) {
                maxLen = dp[i];
                result = ways[i];
            } else if (dp[i] == maxLen) {
                result += ways[i];
            }
        }
        return result;
    }
};
