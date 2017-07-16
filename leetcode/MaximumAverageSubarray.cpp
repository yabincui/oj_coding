class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double sum = 0;
        double maxRes = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (i == k - 1) {
                maxRes = sum;
            } else if (i > k - 1) {
                sum -= nums[i-k];
                maxRes = max(maxRes, sum);
            }
        }
        return maxRes / k;
    }
};
