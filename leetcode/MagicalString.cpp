class Solution {
public:
    int magicalString(int n) {
        string s(n, '\0');
        s[0] = '1';
        int i = 0;
        int j = 0;
        char cur = '1';
        while (i < n) {
            if (s[j] == '1') {
                s[++i] = cur == '1' ? '2' : '1';
                j++;
            } else {
                s[++i] = cur;
                s[++i] = cur == '1' ? '2' : '1';
                j++;
            }
            cur = s[i];
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                res++;
            }
        }
        return res;
    }
};
