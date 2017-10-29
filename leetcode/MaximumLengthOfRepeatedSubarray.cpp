class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int m = A.size();
        int n = B.size();
        vector<int> dp(n + 1);
        int result = 0;
        for (int i = 1; i <= m; ++i) {
            vector<int> ndp(n + 1);
            for (int j = 1; j <= n; ++j) {
                if (A[i-1] == B[j-1]) {
                    ndp[j] = dp[j-1] + 1;
                    result = max(ndp[j], result);
                }
            }
            dp = ndp;
        }
        return result;
    }
};