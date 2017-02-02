// 416. Partition Equal Subset Sum
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (auto& n : nums) {
            sum += n;
        }
        if (sum & 1) return false;
        int target = sum / 2;
        bool dp[target + 1];
        memset(dp, 0, sizeof(dp));
        dp[0] = true;
        for (auto& c : nums) {
            for (int i = target - c; i >= 0; --i) {
                if (dp[i]) {
                    dp[i + c] = true;
                }
            }
            if (dp[target]) break;
        }
        return dp[target];
    }
};
