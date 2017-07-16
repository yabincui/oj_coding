class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int start = -1;
        int end = 0;
        int n = nums.size();
        int sum = 0;
        int res = INT_MAX;
        while (start + 1 < nums.size()) {
            while (start + 1 < nums.size() && sum < s) {
                sum += nums[++start];
            }
            while (sum - nums[end] >= s) {
                sum -= nums[end++];
            }
            //printf("start = %d, end = %d, sum = %d\n", start, end, sum);
            if (sum >= s) {
                res = min(res, start - end + 1);
                sum -= nums[end++];
            }
        }
        if (res == INT_MAX) return 0;
        return res;
    }
};
