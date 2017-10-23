class Solution {
    
    int64_t A[11][11];
    
public:
    
    Solution() {
        // A[i][j] = i * (i - 1) * ... * (i - j + 1).
        // A[i-1][j - 1] = (i - 1) * ... * (i - j + 1) * (i - j + 1).
        // A[i][j] = A[i-1][j-1] * i.
        for (int i = 0; i <= 10; ++i) {
            A[i][0] = 1;
        }
        for (int i = 1; i <= 10; ++i) {
            for (int j = 1; j <= i; ++j) {
                A[i][j] = A[i-1][j-1] * i;
            }
        }
    }
    
    int countNumbersWithUniqueDigits(int n) {
        int res = 1;
        if (n > 10) {
            n = 10;
        }
        for (int i = 1; i <= n; ++i) {
            // select i numbers with 0. (select i - 1 numbers from 1 - 9).
            // and insert 0 at i - 1 positions.
            res += A[9][i-1] * (i - 1);
            // select i numbers without 0.
            res += A[9][i];
        }
        return res;
    }
};