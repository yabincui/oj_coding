// 438. Find All Anagrams in a String
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int need[26];
        memset(&need, 0, sizeof(need));
        for (auto c : p) {
            need[c-'a']++;
        }
        int meet[26];
        memset(meet, 0, sizeof(meet));
        int meet_count = 0;
        for (int i = 0; i < 26; ++i) {
            if (need[i] == 0) meet_count++;
        }
        int start = 0;
        int end = 0;
        vector<int> res;
        while (end < s.size()) {
            while (end < s.size()) {
                int t = s[end++] - 'a';
                meet[t]++;
                if (meet[t] == need[t]) {
                    meet_count++;
                    if (meet_count == 26) {
                        res.push_back(start);
                    }
                } else if (meet[t] > need[t]) {
                    meet_count--;
                    break;
                }
            }
            while (start < end) {
                int t = s[start++] - 'a';
                meet[t]--;
                if (meet[t] == need[t]) {
                    meet_count++;
                    if (meet_count == 26) {
                        res.push_back(start);
                    }
                    break;
                } else if (meet[t] == need[t]-1) {
                    meet_count--;
                }
            }
        }
        return res;
    }
};
