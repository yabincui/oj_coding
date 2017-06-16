class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        if (nums.size() < 3) {
            return false;
        }
        map<int, int> back_map;
        for (int i = 1; i < nums.size(); ++i) {
            back_map[nums[i]]++;
        }
        int min_prev = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (--back_map[nums[i]] == 0) {
                back_map.erase(nums[i]);
            }
            auto it = back_map.lower_bound(nums[i]);
            if (it != back_map.begin()) {
                --it;
                int value = it->first;
                if (value > min_prev) {
                    return true;
                }
            }
            min_prev = min(min_prev, nums[i]);
        }
        return false;
    }
};
