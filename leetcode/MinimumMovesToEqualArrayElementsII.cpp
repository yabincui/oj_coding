class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<uint64_t> leftDiff(nums.size());
        for (int i = 1; i < nums.size(); ++i) {
            uint64_t eachDiff = (uint64_t)nums[i] - nums[i-1];
            uint64_t totalDiff = eachDiff * i;
            leftDiff[i] = leftDiff[i-1] + totalDiff;
            //printf("leftDiff[%d] = %d\n", i, leftDiff[i]);
        }
        uint64_t result = leftDiff.back();
        uint64_t prevRightDiff = 0;
        for (int i = nums.size() - 2; i >= 0; --i) {
            uint64_t rightDiff = ((uint64_t)nums[i + 1] - nums[i]) * (nums.size() - 1 - i) + prevRightDiff;
            //printf("rightDiff[%d] = %d\n", i, rightDiff);
            result = min(result, leftDiff[i] + rightDiff);
            prevRightDiff = rightDiff;
        }
        return (int)result;
    }
};