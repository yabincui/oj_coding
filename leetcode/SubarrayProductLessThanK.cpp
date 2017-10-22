class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k == 0) {
            return 0;
        }
        int mul = 1;
        int left = 0;
        int right = 0;
        int result = 0;
        while (left < nums.size()) {
            while (right < nums.size() && mul * nums[right] < k) {
                mul *= nums[right];
                right++;
            }
            result += right - left;
            if (left < right) {
                mul /= nums[left];
            }
            left++;
            if (left > right) {
                right = left;
            }
        }
        return result;
    }
};