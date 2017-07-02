class Solution {
public:
    bool judgeSquareSum(int c) {
        if (c <= 2) {
            return true;
        }
        int max_i = (int)sqrt(c) + 1;
        for (int i = 0; i <= max_i; ++i) {
            int64_t i2 = (int64_t)i * i;
            int64_t j2 = c - i2;
            if (j2 < i2) {
                break;
            }
            if (isSquare(j2)) {
                return true;
            }
        }
        return false;
    }
    bool isSquare(int64_t value) {
        int a = (int)sqrt(value);
        if (a * a == value) return true;
        a++;
        if (a * a == value) return true;
        return false;
    }
};
