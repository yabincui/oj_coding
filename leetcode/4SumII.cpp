class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> ab_map;
        unordered_map<int, int> cd_map;
        for (auto& a : A) {
            for (auto& b : B) {
                ab_map[a + b]++;
            }
        }
        for (auto& c : C) {
            for (auto& d : D) {
                cd_map[c + d]++;
            }
        }
        int result = 0;
        for (auto& p : ab_map) {
            auto it = cd_map.find(-p.first);
            if (it != cd_map.end()) {
                result += p.second * it->second;
            }
        }
        return result;
    }
};
