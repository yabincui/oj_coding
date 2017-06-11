class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                int maxValue = nums[i] + nums[j] - 1;
                int id = binarySearch(nums.data(), j, nums.size() - 1, maxValue);
                result += id - j;
            }
        }
        return result;
    }
    
    int binarySearch(int* s, int low, int high, int target) {
        while (low + 1 < high) {
            int mid = (low + high) / 2;
            if (s[mid] <= target) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        if (s[high] <= target) return high;
        return low;
    }
};
