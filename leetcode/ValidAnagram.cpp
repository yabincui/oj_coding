class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> hit_map;
        for (auto c : s) {
            hit_map[c]++;
        }
        for (auto c : t) {
            hit_map[c]--;
        }
        for (auto& pair : hit_map) {
            if (pair.second != 0) {
                return false;
            }
        }
        return true;
    }
};