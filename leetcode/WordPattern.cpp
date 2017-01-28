// 290. Word Pattern
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        string map[26];
        unordered_map<string, char> rmap;
        const char* p = str.c_str();
        for (auto& c : pattern) {
            string s = getSubstr(p);
            if (s.empty()) {
                return false;
            }
            auto it = rmap.find(s);
            if (it == rmap.end()) {
                if (!map[c - 'a'].empty()) {
                    return false;
                }
                map[c - 'a'] = s;
                rmap[s] = c;
            } else {
                if (c != it->second || map[c - 'a'] != s) {
                    return false;
                }
            }
        }
        return getSubstr(p).empty();
    }
    
    string getSubstr(const char*& p) {
        const char* begin = p;
        while (*begin == ' ') {
            begin++;
        }
        const char* end = begin;
        while (*end >= 'a' && *end <= 'z') {
            end++;
        }
        p = end;
        return string(begin, end);
    }
};
