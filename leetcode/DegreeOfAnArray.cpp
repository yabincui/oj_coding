class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        int maxDegree = 0;
        unordered_map<int, int> hit_map;
        for (auto n : nums) {
            int d = ++hit_map[n];
            maxDegree = max(maxDegree, d);
        }
        int left = 0;
        int right = -1;
        int degree = 0;
        hit_map.clear();
        int minLength = nums.size();
        while (right + 1 < nums.size()) {
            int relyValue = -1;
            while (degree < maxDegree && right + 1 < nums.size()) {
                int d = ++hit_map[nums[++right]];
                degree = max(degree, d);
                relyValue = nums[right];
            }
            if (degree < maxDegree) break;
            while (nums[left] != relyValue) {
                hit_map[nums[left++]]--;
            }
            minLength = min(minLength, right - left + 1);
            degree--;
            left++;
            hit_map[relyValue]--;
        }
        return minLength;
    }
};