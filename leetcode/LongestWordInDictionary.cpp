class Solution {
public:
    string longestWord(vector<string>& words) {
        unordered_set<string> set;
        for (auto& s : words) {
            set.insert(s);
        }
        auto cmp = [](const string& a, const string& b) {
            if (a.size() != b.size()) {
                return a.size() > b.size();
            }
            return a < b;
        };
        sort(words.begin(), words.end(), cmp);
        for (auto& s : words) {
            string cur = s;
            bool ok = true;
            while (cur.size() > 1) {
                cur.pop_back();
                if (set.find(cur) == set.end()) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                return s;
            }
        }
        return "";
    }
};
