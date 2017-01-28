// 485. Max Consecutive Ones
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int max_len = 0;
        int start;
        bool in_one = false;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 1) {
                if (!in_one) {
                    start = i;
                    in_one = true;
                }
            } else {
                if (in_one) {
                    in_one = false;
                    int cur = i - start;
                    if (cur > max_len) {
                        max_len = cur;
                    }
                }
            }
        }
        if (in_one) {
            int cur = nums.size() - start;
            if (cur > max_len) {
                max_len = cur;
            }
        }
        return max_len;
    }
};
