class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res(num + 1);
        for (int i = 1; i <= num; ++i) {
            if (i & 1) {
                res[i] = res[i-1] + 1;
            } else {
                // like 10111 -> 11000, count[a & b] + 1.
                res[i] = res[i & (i - 1)] + 1;
            }
        }
        return res;
    }
};