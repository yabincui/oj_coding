class Solution {
    
    int depart(int n, int count) {
        int avg = n / count;
        int rem = n % count;
        int res = 1;
        for (int i = 1; i <= count; ++i) {
            if (i <= rem) {
                res *= avg + 1;
            } else {
                res *= avg;
            }
        }
        return res;
    }
    
public:
    int integerBreak(int n) {
        int res = 0;
        for (int i = 2; i <= n; ++i) {
            res = max(res, depart(n, i));
        }
        return res;
    }
};