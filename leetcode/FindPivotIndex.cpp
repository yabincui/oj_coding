class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        vector<int> rightSum(nums.size(), 0);
        for (int i = nums.size() - 2; i >= 0; --i) {
            rightSum[i] = rightSum[i + 1] + nums[i + 1];
        }
        int leftSum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (leftSum == rightSum[i]) {
                return i;
            }
            leftSum += nums[i];
        }
        return -1;
    }
};
