// 504. Base 7
class Solution {
public:
    string convertTo7(int num) {
        int64_t value = num;
        int sign = value < 0 ? -1 : 1;
        if (value < 0) value = -value;
        string res;
        if (value == 0) {
            res.push_back('0');
        }
        while (value != 0) {
            res.push_back(value % 7 + '0');
            value /= 7;
        }
        if (sign == -1)
            res.push_back('-');
        reverse(res.begin(), res.end());
        return res;
    }
};
