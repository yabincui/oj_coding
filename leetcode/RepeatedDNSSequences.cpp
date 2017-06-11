class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> hit_map;
        for (int i = 0; i + 10 <= s.size(); ++i) {
            string t = s.substr(i, 10);
            hit_map[t]++;
        }
        vector<string> res;
        for (auto& pair : hit_map) {
            if (pair.second > 1) {
                res.push_back(pair.first);
            }
        }
        return res;
    }
};
