class Solution {
public:
    bool isUgly(int num) {
        if (num < 1) return false;
        vector<int> key = {2, 3, 5};
        for (int k : key) {
            while (num >= k && num % k == 0) {
                num /= k;
            }
        }
        return num == 1;
    }
};