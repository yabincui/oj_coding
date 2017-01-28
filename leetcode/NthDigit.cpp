// 400. Nth Digit
class Solution {
public:
    int findNthDigit(int n) {
        int digits = 1;
        int base = 1;
        int count_in_current_level = 9;
        while (true) {
            if (lessEqual(n, count_in_current_level, digits)) {
                int value = (n - 1) / digits;
                value += base;
                return getNth(value, base, (n - 1) % digits);
            }
            n -= count_in_current_level * digits;
            count_in_current_level *= 10;
            base *= 10;
            digits++;
        }
        return -1;
    }
    
    bool lessEqual(int n, int a, int b) {
        if (n / a < b) {
            return true;
        }
        if (n / a == b) {
            return n % a == 0;
        }
        return false;
    }
    
    int getNth(int value, int base, int n) {
        //printf("value = %d, base = %d, n = %d\n", value, base, n);
        for (int i = 0; i < n; ++i) {
            base /= 10;
        }
        return (value / base) % 10;
    }
};
