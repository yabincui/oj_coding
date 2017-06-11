class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> s_to_t;
        unordered_map<char, char> t_to_s;
        for (int i = 0; i < s.size(); ++i) {
            char c1 = s[i];
            char c2 = t[i];
            auto it = s_to_t.find(c1);
            if (it != s_to_t.end()) {
                if (it->second == c2) {
                    continue;
                } else {
                    return false;
                }
            } else {
                auto it2 = t_to_s.find(c2);
                if (it2 != t_to_s.end()) {
                    return false;
                }
                s_to_t[c1] = c2;
                t_to_s[c2] = c1;
            }
        }
        return true;
    }
};
