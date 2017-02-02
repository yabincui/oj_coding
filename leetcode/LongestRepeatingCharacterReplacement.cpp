// 424. Longest Repeating Character Replacement
class Solution {
public:
    int characterReplacement(string s, int k) {
        int max_len = 0;
        for (char i = 'A'; i <= 'Z'; ++i) {
            max_len = max(max_len, getMaxLen(s, i, k));
        }
        return max_len;
    }
    
    int getMaxLen(string& s, char key, int k) {
        int max_len = 0;
        int start = 0;
        int end = 0;
        int diff = 0;
        while (end < s.size()) {
            while (diff <= k && end < s.size()) {
                if (s[end] != key) {
                    diff++;
                }
                end++;
            }
            if (end - 1 - start > max_len) {
                max_len = end - 1 - start;
            }
            while (diff > k && start < end) {
                if (s[start] != key) {
                    diff--;
                }
                start++;
            }
        }
        if (end - start > max_len) {
            max_len = end - start;
        }
        return max_len;
    }
};
