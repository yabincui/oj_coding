// key: sort, sliding window
// error: integer overflow
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        // 1. sort
        // 2. for i, if adding smaller numbers to nums[i], how many operations are needed.
        // a sliding window.
        if (nums.empty()) {
            return 0;
        }
        sort(nums.begin(), nums.end());
        int max_freq = 1;
        int start = 0;
        int64_t cost = 0;
        for (int i = 1; i < nums.size(); i++) {
            int64_t per_cost = nums[i] - nums[i - 1];
            cost += per_cost * (i - start);
            while (cost > k) {
                cost -= nums[i] - nums[start];
                start++;
            }
            max_freq = max(max_freq, i - start + 1);
        }
        return max_freq;
    }
};