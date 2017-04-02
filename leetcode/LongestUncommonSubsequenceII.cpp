// 522. Longest Uncommon Subsequence II
class Solution {
    
    bool isSubSequence(const string& s, const string& part) {
        int j = 0;
        for (int i = 0; i < s.size() && j < part.size(); ++i) {
            if (s[i] == part[j]) {
                j++;
            }
        }
        return j == part.size();
    }
    
public:
    int findLUSlength(vector<string>& strs) {
        int n = strs.size();
        vector<bool> valid(n, true);
        for (int i = 0; i < n; ++i) {
            if (valid[i]) {
                for (int j = 0; j < n; ++j) {
                    if (j == i) continue;
                    if (isSubSequence(strs[j], strs[i])) {
                        valid[i] = false;
                        break;
                    }
                }
            }
        }
        int res = -1;
        for (int i = 0; i < n; ++i) {
            if (valid[i]) {
                res = max(res, (int)strs[i].size());
            }
        }
        return res;
    }
};class Solution {
    
    bool isSubSequence(const string& s, const string& part) {
        int j = 0;
        for (int i = 0; i < s.size() && j < part.size(); ++i) {
            if (s[i] == part[j]) {
                j++;
            }
        }
        return j == part.size();
    }
    
public:
    int findLUSlength(vector<string>& strs) {
        int n = strs.size();
        vector<bool> valid(n, true);
        for (int i = 0; i < n; ++i) {
            if (valid[i]) {
                for (int j = 0; j < n; ++j) {
                    if (j == i) continue;
                    if (isSubSequence(strs[j], strs[i])) {
                        valid[i] = false;
                        break;
                    }
                }
            }
        }
        int res = -1;
        for (int i = 0; i < n; ++i) {
            if (valid[i]) {
                res = max(res, (int)strs[i].size());
            }
        }
        return res;
    }
};
