// 405. Convert a Number to Hexadecimal
class Solution {
public:
    string toHex(int num) {
        uint32_t val = num;
        string res;
        while (val != 0) {
            int t = val & 0xf;
            char c;
            if (t < 10) {
                c = t + '0';
            } else {
                c = t - 10 + 'a';
            }
            val >>= 4;
            res.push_back(c);
        }
        if (res.empty()) {
            res.push_back('0');
        }
        for (int i = 0, j = res.size() - 1; i < j; ++i, --j) {
            char c = res[i]; res[i] = res[j]; res[j] = c;
        }
        return res;
    }
};
