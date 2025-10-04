// key: sort, overflow
// error: edge case, needs i >= 2 when calculating sum.
class Solution {
   public:
    long long largestPerimeter(vector<int>& nums) {
        // sort, acc_sum
        if (nums.size() < 3) {
            return -1;
        }
        sort(nums.begin(), nums.end());
        vector<long long> acc_sum(nums.size(), 0);
        acc_sum[0] = nums[0];
        long long result = -1;
        for (int i = 1; i < nums.size(); i++) {
            acc_sum[i] = acc_sum[i - 1] + nums[i];
            if (acc_sum[i - 1] > nums[i] && i >= 2) {
                result = max(result, acc_sum[i]);
            }
        }
        return result;
    }
};