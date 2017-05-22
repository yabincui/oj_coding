class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> value_map;
        for (auto& num : nums) {
            value_map[num]++;
        }
        int result = 0;
        for (auto pair : value_map) {
            int count = pair.second;
            auto it = value_map.find(pair.first + 1);
            if (it != value_map.end()) {
                count += it->second;
                result = max(result, count);
            }
        }
        return result;
    }
};