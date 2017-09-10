class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int result = 0;
        int curLen = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (i > 0 && nums[i] > nums[i-1]) {
                curLen++;
            } else {
                result = max(result, curLen);
                curLen = 1;
            }
        }
        result = max(result, curLen);
        return result;
    }
};
