class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string> res;
        string cur;
        bool in_block_comment = false;
        for (auto& s : source) {
            for (int i = 0; i < s.size(); ++i) {
                if (in_block_comment) {
                    if (s[i] == '*') {
                        if (i + 1 < s.size() && s[i+1] == '/') {
                            in_block_comment = false;
                            ++i;
                        }
                    }
                } else {
                    if (s[i] == '/') {
                        if (i + 1 < s.size() && s[i + 1] == '/') {
                            break;
                        }
                        if (i + 1 < s.size() && s[i + 1] == '*') {
                            in_block_comment = true;
                            ++i;
                        } else {
                            cur.push_back(s[i]);
                        }
                    } else {
                        cur.push_back(s[i]);
                    }
                }
            }
            if (!in_block_comment) {
                if (!cur.empty()) {
                    res.push_back(cur);
                    cur.clear();
                }
            }
        }
        return res;
    }
};
