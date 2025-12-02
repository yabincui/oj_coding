// dp, big result
// error: array edge case
// 2140. Solving Questions With Brainpower
class Solution {
   public:
    long long mostPoints(vector<vector<int>>& questions) {
        // dp[i] the max point when reaching a problem (without solving it).
        // dp[i] = max(dp[i - 1], prev(dp[j] + points[j], can reach i))
        size_t n = questions.size();
        vector<long long> dp(n + 1, 0);
        for (size_t i = 0; i < n; i++) {
            dp[i + 1] = max(dp[i], dp[i + 1]);
            // solve the current problem.
            size_t j = min(n, i + questions[i][1] + 1);
            dp[j] = max(dp[j], dp[i] + questions[i][0]);
        }
        return dp[n];
    }
};