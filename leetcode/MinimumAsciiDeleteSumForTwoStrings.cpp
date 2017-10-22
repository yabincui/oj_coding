class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        vector<int> dp(n + 1);
        vector<int> ndp(n + 1);
        
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i-1] + s2[i-1];
        }
        for (int i = 1; i <= m; ++i) {
            ndp[0] = dp[0] + s1[i-1];
            for (int j = 1; j <= n; ++j) {
                int minValue = min(dp[j] + s1[i-1], ndp[j-1] + s2[j-1]);
                if (s1[i-1] == s2[j-1]) {
                    minValue = min(minValue, dp[j-1]);
                }
                ndp[j] = minValue;
            }
            dp = ndp;
        }
        return dp[n];
    }
};