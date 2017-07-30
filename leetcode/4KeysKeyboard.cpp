class Solution {
public:
    int maxA(int N) {
        vector<int64_t> dp(N + 1, 0);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 1; i < N; ++i) {
            // type A
            dp[i + 1] = max(dp[i + 1], dp[i] + 1);
            // ctrl-A + ctrl-C + ... ctrl-V.
            if (i + 2 < N) {
                int64_t cur = dp[i];
                for (int j = i + 3; j <= N; ++j) {
                    cur += dp[i];
                    dp[j] = max(dp[j], cur);
                }
            }
        }
        return dp[N];
    }
};
