class Solution {
public:
    int minMoves(vector<int>& nums) {
        if (nums.empty()) return 0;
        int minValue = nums[0];
        long long sumValue = 0;
        for (auto& n : nums) {
            minValue = min(minValue, n);
            sumValue += n;
        }
        sumValue -= (long long)minValue * nums.size();
        return (int)sumValue;
    }
};
