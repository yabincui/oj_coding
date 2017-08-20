class Solution {
    
    // dp[i][j][k], s[i-j] cost, with color k.
    int (*dp)[100][27];
    

public:
    
    Solution() {
        int* m = new int[100 * 100 * 27];
        dp = (int (*)[100][27])m;
    }
    
    ~Solution() {
        delete [] (int*)dp;
    }
    
    int strangePrinter(string s) {
        int n = s.size();
        if (n == 0) return 0;
        vector<int> s2(n);
        for (int i = 0; i < n; ++i) {
            s2[i] = s[i] - 'a';
        }
        for (int i = 0; i < n; ++i) {
            for (int c = 0; c <= 26; ++c) {
                dp[i][i][c] = (c == s2[i]) ? 0 : 1;
            }
        }
        for (int step = 2; step <= n; ++step) {
            for (int i = 0; i + step <= n; ++i) {
                int j = i + step - 1;
                for (int c = 0; c <= 26; ++c) {
                    if (c == s2[j]) {
                        dp[i][j][c] = dp[i][j-1][c];
                        continue;
                    }
                    int min_cost = INT_MAX;
                    for (int k = j; k >= i; k--) {
                        int cost = 1;
                        if (k > i) {
                            cost += dp[i][k-1][c];
                        }
                        if (k < j) {
                            cost += dp[k][j-1][s2[j]];
                        }
                        min_cost = min(cost, min_cost);
                    }
                    dp[i][j][c] = min_cost;
                }
            }
        }
        return dp[0][n-1][26];
    }
};
