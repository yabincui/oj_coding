// 516 Longest Palindromic Subsequence
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        if (n == 0) return 0;
        int dp[n][n];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }
        for (int step = 1; step < n; ++step) {
            for (int i = 0; i + step < n; ++i) {
                int j = i + step;
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                if (s[i] == s[j]) {
                    int tmp = (i + 1 < j) ? dp[i+1][j-1] : 0;
                    dp[i][j] = 2 + tmp;
                }
            }
        }
        return dp[0][n-1];
    }
};
