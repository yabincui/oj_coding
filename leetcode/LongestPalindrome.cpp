// 409. Longest Palindrome.
class Solution {
public:
    int longestPalindrome(string s) {
        int count[256];
        memset(count, 0, sizeof(count));
        for (auto& c : s) {
            count[c]++;
        }
        int res = 0;
        bool has_odd = false;
        for (int i = 0; i < 256; ++i) {
            if (count[i] > 0) {
                res += count[i] & ~1;
                count[i] &= 1;
                if (count[i]) {
                    has_odd = true;
                }
            }
        }
        if (has_odd) {
            res++;
        }
        return res;
    }
};
