class Solution {
public:
    int maximumSwap(int num) {
        vector<int> digits;
        if (num == 0) {
            return 0;
        }
        while (num != 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
        
        for (int i = digits.size() - 1; i >= 0; --i) {
            int maxPos = -1;
            int maxDigit = -1;
            for (int j = 0; j < i; ++j) {
                if (digits[j] > digits[i] && digits[j] > maxDigit) {
                    maxDigit = digits[j];
                    maxPos = j;
                }
            }
            if (maxPos == -1) continue;
            swap(digits[i], digits[maxPos]);
            break;
        }
        num = 0;
        for (int i = digits.size() - 1; i >= 0; --i) {
            num = num * 10 + digits[i];
        }
        return num;
    }
};
