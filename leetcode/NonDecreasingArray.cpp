class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        bool used = false;
        for (int i = 0; i < nums.size(); ++i) {
            if (i + 1 < nums.size()) {
                if (nums[i] <= nums[i + 1]) {
                    continue;
                }
                if (used) return false;
                if (i > 0) {
                    if (nums[i - 1] > nums[i + 1]) {
                        nums[i + 1] = nums[i];
                        used = true;
                        continue;
                    }
                }
                // nums[i-1] <= nums[i+1] <= nums[i]. changes nums[i] to nums[i+1].
                used = true;
                nums[i] = nums[i + 1];
            }
        }
        return true;
    }
};
