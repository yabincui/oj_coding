class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> hit_map;
        for (auto& n : nums) {
            hit_map[n]++;
        }
        map<int, vector<int>> count_map;
        for (auto& pair : hit_map) {
            count_map[pair.second].push_back(pair.first);
        }
        vector<int> res;
        for (auto it = count_map.rbegin(); it != count_map.rend() && k > 0; ++it) {
            for (int i = 0; i < it->second.size() && k > 0; ++i) {
                res.push_back(it->second[i]);
                k--;
            }
        }
        return res;
    }
};
