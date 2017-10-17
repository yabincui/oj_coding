class Solution {
public:
    int countBinarySubstrings(string s) {
        vector<int> v;
        char cur = s[0];
        int len = 1;
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == cur) {
                len++;
            } else {
                v.push_back(len);
                len = 1;
                cur = s[i];
            }
        }
        v.push_back(len);
        int result = 0;
        for (int i = 0; i + 1 < v.size(); ++i) {
            int a = v[i];
            int b = v[i+1];
            result += min(a, b);
        }
        return result;
    }
};