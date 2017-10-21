class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int low = 0;
        int high = n;
        int left = 0;
        int right = n - 1;
        while (low != high) {
            int midValue = (low + high) / 2;
            int i = left;
            for (int j = left; j <= right; ++j) {
                if (nums[j] <= midValue) {
                    if (i < j) {
                        swap(nums[i++], nums[j]);
                    } else {
                        i++;
                    }
                }
            }
            // nums[i] is > midValue.
            // in the left part, slot count = i - left, values = [low, midValue].
            if (i - left < midValue - low + 1) {
                right = i;
                high = midValue;
            } else {
                left = i;
                low = midValue + 1;
            }
        }
        return low;
    }
};