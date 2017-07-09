class Solution {
    
    int64_t getMod(int64_t a) {
        int mod = 1000000000 + 7;
        return a % mod;
    }
    
public:
    
    int numDecodings(string s) {
        int n = s.size();
        if (n == 0) return 0;
        
        vector<int64_t> cur(3, 0);
        vector<int64_t> prev(3, 0);
        
          // dp[i][j], i is pos, j is 0 for no prefix, 1 for prefix 1, 2 for prefix 2.
        // dp[i][j] is the ways to decode.
        cur[0] = 1;
        for (int i = 1; i <= n; ++i) {
            prev = cur;
            cur[0] = cur[1] = cur[2] = 0;
            char c = s[i - 1];
            if (c == '0') {
                cur[0] = getMod(prev[1] + prev[2]);
            } else if (c >= '1' && c <= '6') {
                cur[0] = getMod(prev[0] + prev[1] + prev[2]);
                if (c == '1') {
                    cur[1] = prev[0];
                } else if (c == '2') {
                    cur[2] = prev[0];
                }
            } else if (c >= '7' && c <= '9') {
                cur[0] = getMod(prev[0] + prev[1]);
            } else if (c == '*') {
                cur[0] = getMod(prev[0] * 9 + prev[1] * 9 + prev[2] * 6);
                cur[1] = prev[0];
                cur[2] = prev[0];
            }
        }
        return (int)cur[0];
    }
};
