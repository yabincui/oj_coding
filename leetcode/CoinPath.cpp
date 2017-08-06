class Solution {
public:
    vector<int> cheapestJump(vector<int>& A, int B) {
        int n = A.size();
        vector<int> dp(n);
        if (A[n-1] == -1) return vector<int>();
        dp[n-1] = A[n-1];
        for (int i = n - 2; i >= 0; --i) {
            if (A[i] == -1) {
                dp[i] = -1;
            } else {
                int minNext = INT_MAX;
                for (int j = i + 1; j <= i + B && j < n; ++j) {
                    if (dp[j] != -1 && dp[j] < minNext) {
                        minNext = dp[j];
                    }
                }
                if (minNext == INT_MAX) {
                    dp[i] = -1;
                } else {
                    dp[i] = A[i] + minNext;
                }
            }
            //printf("dp[%d] = %d\n", i, dp[i]);
        }
        vector<int> res;
        if (dp[0] == -1) return res;
        int cur = 0;
        res.push_back(1);
        while (cur != n - 1) {
            if (false) {
                res.push_back(n);
                break;
            } else {
                int minIndex = -1;
                for (int i = cur + 1; i <= cur + B && i < n; ++i) {
                    if (dp[i] != -1 && (minIndex == -1 || dp[i] < dp[minIndex])) {
                        minIndex = i;
                    }
                }
                res.push_back(minIndex + 1);
                cur = minIndex;
            }
        }
        return res;
    }
};
