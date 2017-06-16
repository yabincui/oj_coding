class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        for (int len = 1; len <= s.size() / 2; ++len) {
            if (s.size() % len != 0) {
                continue;
            }
            bool ok = true;
            for (int i = 0, j = 0; i < s.size(); ++i) {
                if (s[i] != s[j]) {
                    ok = false;
                    break;
                }
                j = (j + 1) % len;
            }
            if (ok) return true;
        }
        return false;
    }
};
