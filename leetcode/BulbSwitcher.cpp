class Solution {
public:
    int bulbSwitch(int n) {
        if (n < 1) return 0;
        int sq = 1;
        int64_t sq2 = 1;
        int res = 1;
        for (int i = 2; i <= n; ++i) {
            while (sq2 < i) {
                sq++;
                sq2 = (int64_t)sq * sq;
            }
            if (sq2 == i) {
                res++;
            }
        }
        return res;
    }
};