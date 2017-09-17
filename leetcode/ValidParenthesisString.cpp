class Solution {
public:
    bool checkValidString(string s) {
        int n = s.size();
        int dps[2][n + 1];
        int* dp = dps[0];
        int* ndp = dps[1];
        
        memset(dp, 0, sizeof(int) * (n + 1));
        dp[0] = 1;
        for (char c : s) {
            memset(ndp, 0, sizeof(int) * (n + 1));
            if (c == '(' || c == '*') {
                for (int i = 0; i < n; ++i) {
                    if (dp[i]) {
                        ndp[i + 1] = 1;
                    }
                }
            }
            if (c == ')' || c == '*') {
                for (int i = 1; i <= n; ++i) {
                    if (dp[i]) {
                        ndp[i - 1] = 1;
                    }
                }
            }
            if (c == '*') {
                for (int i = 0; i <= n; ++i) {
                    if (dp[i]) {
                        ndp[i] = 1;
                    }
                }
            }
            
            swap(dp, ndp);
        }
        return dp[0] == 1;
    }
};
