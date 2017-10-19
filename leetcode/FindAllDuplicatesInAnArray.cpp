class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        unordered_map<int, int> hit_map;
        vector<int> result;
        for (auto n : nums) {
            hit_map[n]++;
            if (hit_map[n] == 2) {
                result.push_back(n);
            }
        }
        return result;
    }
};