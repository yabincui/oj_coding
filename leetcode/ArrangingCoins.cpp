class Solution {
public:
    int arrangeCoins(int n) {
        // 1 + 2 + ... + k = k * (k+1) / 2
        // n = k * (k + 1) / 2, k*(k+1) = 2n  (k+1) > sqrt(2n) > k.
        int temp = (int)sqrt((int64_t)2 * n);
        for (int i = 2; i >= -2; --i) {
            int64_t k = temp + i;
            if (k * (k + 1) <= (int64_t)2 * n) {
                return k;
            }
        }
    }
};
