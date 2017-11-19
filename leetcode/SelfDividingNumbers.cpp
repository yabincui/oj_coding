class Solution {
    
    bool isOk(int n) {
        vector<int> digits;
        int tmp = n;
        while (tmp != 0) {
            digits.push_back(tmp % 10);
            tmp /= 10;
        }
        for (auto d : digits) {
            if (d == 0 || n % d != 0) {
                return false;
            }
        }
        return true;
    }
    
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> result;
        for (int i = left; i <= right; ++i) {
            if (isOk(i)) {
                result.push_back(i);
            }
        }
        return result;
    }
};
