class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        // dp[i], sum is i, dp[i] is the types to arrive at i.
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= target; ++i) {
            // choose a number from nums.
            for (int j = 0; j < nums.size(); ++j) {
                if (nums[j] <= i) {
                    dp[i] += dp[i-nums[j]];
                }
            }
        }
        return dp[target];   
    }
};