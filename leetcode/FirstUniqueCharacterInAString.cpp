// 387. First Unique Character in a String
class Solution {
public:
    int firstUniqChar(string s) {
        int count[26];
        int firstAppear[26];
        memset(count, 0, sizeof(count));
        for (size_t i = 0; i < s.size(); ++i) {
            char c = s[i];
            int pos = c - 'a';
            count[pos]++;
            if (count[pos] == 1) {
                firstAppear[pos] = i;
            }
        }
        int sel = -1;
        for (int i = 0; i < 26; ++i) {
            if (count[i] == 1 && (sel == -1 || firstAppear[i] < firstAppear[sel])) {
                sel = i;
            }
        }
        if (sel == -1) {
            return -1;
        }
        return firstAppear[sel];
    }
};
