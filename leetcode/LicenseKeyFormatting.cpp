class Solution {
public:
    string licenseKeyFormatting(string S, int K) {
        int count = 0;
        for (auto c : S) {
            if (c != '-') {
                count++;
            }
        }
        int remain = count % K;
        if (remain == 0) remain = K;
        string res;
        int i = 0;
        for (auto c : S) {
            if (c == '-') {
                continue;
            }
            if (c >= 'a' && c <= 'z') {
                c += 'A' - 'a';
            }
            if (i == remain) {
                res.push_back('-');
                remain = K;
                i = 0;
            }
            res.push_back(c);
            i++;
        }
        return res;
    }
};
