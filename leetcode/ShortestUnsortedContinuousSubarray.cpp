class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int start = -1;
        int end = -1;
        if (nums.empty()) return 0;
        int cur_max = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            int n = nums[i];
            if (n >= cur_max) {
                cur_max = n;
                continue;
            } else {
                if (start == -1) {
                    start = i;
                }
                while (start > 0 && nums[start - 1] > n) {
                    start--;
                }
                end = i;
            }
        }
        if (start == -1) return 0;
        return end - start + 1;
    }
};