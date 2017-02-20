// 526. Beautiful Arrangement
class Solution {
public:
    int res;
    int countArrangement(int N) {
        res = 0;
        recur(0, (1 << N) - 1);
        return res;
    }
    
    void recur(int pos, int mask) {
        if (mask == 0) {
            res++;
            return;
        }
        for (int i = 0;; ++i) {
            int bit = 1 << i;
            if (bit > mask) {
                break;
            }
            if (mask & bit) {
                int a = i + 1;
                int b = pos + 1;
                if (a % b == 0 || b % a == 0) {
                    recur(pos + 1, mask & ~bit);
                }
            }
        }
    }
};
