class Solution {
public:
    int findComplement(int num) {
        int res = 0;
        bool started = false;
        for (int i = 31; i >= 0; --i) {
            int bit = 1 << i;
            if (num & bit) {
                started = true;
            } else {
                if (started) {
                    res |= bit;
                }
            }
        }
        return res;
    }
};
