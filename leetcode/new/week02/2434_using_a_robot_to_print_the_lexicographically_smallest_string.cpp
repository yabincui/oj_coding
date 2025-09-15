// key: stack, map
// no error
class Solution {
public:
    string robotWithString(string s) {
        // zza => t=zza => write azz
        // bac => t=ba -> write abc
        // bdda => t=bdda -> addb
        // if t.last is the smallest in s, pop it.
        // otherwise, push s.first to t.last.
        string t;
        string result;
        map<char, int> count_map;
        for (char c : s) {
            count_map[c]++;
        }
        for (int i = 0; i < s.size(); i++) {
            while (!t.empty()) {
                int c = t.back();
                if (count_map.begin()->first < c) {
                    break;
                }
                result.push_back(c);
                t.pop_back();
            }
            if (--count_map[s[i]] == 0) {
                count_map.erase(s[i]);
            }
            t.push_back(s[i]);
        }
        while (!t.empty()) {
            result.push_back(t.back());
            t.pop_back();
        }
        return result;
    }
};