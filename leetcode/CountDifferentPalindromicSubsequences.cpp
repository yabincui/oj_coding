uint32_t dp[1000][1000][4];
class Solution {
    

    int next[1000][4];
    int prev[1001][4];
    
public:
    int countPalindromicSubsequences(string S) {
        int MOD = 1000000000 + 7;
        int n = S.size();
        for (int k = 0; k < 4; ++k) {
            prev[0][k] = -1;
        }
        for (int i = 1; i <= n; ++i) {
            int t = S[i-1] - 'a';
            for (int k = 0; k < 4; ++k) {
                prev[i][k] = (t == k) ? i - 1 : prev[i-1][k];
            }
        }
        for (int k = 0; k < 4; ++k) {
            next[n-1][k] = n;
        }
        for (int i = n - 2; i >= 0; --i) {
            int t = S[i+1] - 'a';
            for (int k = 0; k < 4; ++k) {
                next[i][k] = (t == k) ? i + 1 : next[i+1][k];
            }
        }
        
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < 4; ++k) {
                dp[i][i][k] = (S[i] - 'a' == k) ? 1 : 0;
            }
        }
        for (int step = 1; step <= n; ++step) {
            for (int i = 0; i + step <= n; ++i) {
                int j = i + step - 1;
                if (S[i] == S[j]) {
                    int t = S[i] - 'a';
                    dp[i][j][t] = 1;
                    if (i + 1 < j) {
                        for (int k = 0; k < 4; ++k) {
                            int ni = next[i][k];
                            int pj = prev[j][k];
                            
                            if (ni < j || pj > i) {
                              dp[i][j][t] = (dp[i][j][t] + 1) % MOD;
                              //printf("add one dp[%d][%d][%d] = %d, k = %d\n", i, j, t, dp[i][j][t], k);
                            }
                            if (ni < pj) {
                                dp[i][j][t] = (dp[i][j][t] + dp[ni][pj][k]) % MOD;
                            }
                        }
                    }
                }
            }
        }
        uint32_t result = 0;
        for (int k = 0; k < 4; ++k) {
            for (int i = 0; i < n; ++i) {
                if (S[i] == 'a' + k) {
                    result = (result + 1) % MOD;
                    int j = prev[n][k];
                    if (j > i) {
                        result = (result + dp[i][j][k]) % MOD;
                        //printf("dp[%d][%d][%d] = %d\n", i, j, k, dp[i][j][k]);
                    }
                    break;
                }
            }
        }
        return (int)result;
    }
};
