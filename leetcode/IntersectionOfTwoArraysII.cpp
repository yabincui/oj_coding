class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> hit_map;
        for (auto n : nums1) {
            hit_map[n]++;
        }
        vector<int> res;
        for (auto n : nums2) {
            auto it = hit_map.find(n);
            if (it != hit_map.end() && it->second > 0) {
                it->second--;
                res.push_back(n);
            }
        }
        return res;
    }
};