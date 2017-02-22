233. Number of Digit One.
class Solution {
public:
    int countDigitOne(int n) {
        if (n <= 0) return 0;
        int res = 0;
        int base = 1;
        int max_level = 0;
        while (n / base >= 10) {
            base *= 10;
            max_level++;
        }
        base = 1;
        for (int level = 0; level <= max_level; ++level) {
            // How many digit 1 at 10^level.
            int value = base;
            int left_count = n / value / 10;
            int tmp = 0;
            if (n / value % 10 == 1) {
                tmp += n % value + 1;
                tmp += left_count * value;
            } else if (n / value % 10 == 0) {
                tmp += left_count * value;
            } else {
                tmp += (left_count + 1) * value;
            }
            res += tmp;
            base *= 10;
        }
        return res;
    }
};
