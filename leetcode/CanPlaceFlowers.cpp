class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int m = flowerbed.size();
        vector<vector<int>> dp(m + 1, vector<int>(2, 0));
        dp[0][0] = dp[0][1] = 0;
        for (int i = 1; i <= m; ++i) {
            if (flowerbed[i-1] == 1) {
                dp[i][0] = -1;
                dp[i][1] = dp[i-1][0];
            } else {
                dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
                if (dp[i-1][0] != -1) {
                    dp[i][1] = dp[i-1][0] + 1;
                } else {
                    dp[i][1] = -1;
                }
            }
        }
        return max(0, max(dp[m][0], dp[m][1])) >= n;
    }
};
