class Solution {
    
    short dp[20000][100];
    
public:
    
    string minWindow(string s, string t) {
        // dp[i][j] means starting from s[i], the min length to match t[j..]. -1 if count.
        int m = s.size();
        int n = t.size();
        for (int j = 0; j < n - 1; ++j) {
            dp[m - 1][j] = -1;
        }
        dp[m - 1][n - 1] = (s[m - 1] == t[n - 1]) ? 1 : -1;
        for (int i = m - 2; i >= 0; --i) {
            for (int j = 0; j < n - 1; ++j) {
                if (s[i] == t[j]) {
                    int tmp = dp[i+1][j+1];
                    if (tmp == -1) {
                        dp[i][j] = -1;
                    } else {
                        dp[i][j] = 1 + tmp;
                    }
                } else {
                    int tmp = dp[i+1][j];
                    if (tmp == -1) {
                        dp[i][j] = -1;
                    } else {
                        dp[i][j] = tmp + 1;
                    }
                }
                //printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
            }
            if (s[i] == t[n-1]) {
                dp[i][n-1] = 1;
            } else {
                int tmp = dp[i+1][n-1];
                if (tmp == -1) {
                    dp[i][n-1] = -1;
                } else {
                    dp[i][n-1] = tmp + 1;
                }
            }
        }
        int minLen = -1;
        int start = -1;
        for (int i = 0; i < m; ++i) {
            //printf("dp[%d][0] = %d\n", i, 0, dp[i][0]);
            if (dp[i][0] != -1 && (minLen == -1 || dp[i][0] < minLen)) {
                minLen = dp[i][0];
                start = i;
            }
        }
        if (minLen > 0) {
            return s.substr(start, minLen);
        }
        return "";
    }
    
};
