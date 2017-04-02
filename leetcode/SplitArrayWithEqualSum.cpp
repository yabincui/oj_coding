// 548. Split Array with Equal Sum

class Solution {
    int sum[2001];
    
    void partition(vector<int>& nums, int start, int end, unordered_set<int>& set1) {
        int total = sum[end+1] - sum[start];
        int left = 0;
        int right;
        for (int i = start + 1; i <= end - 1; ++i) {
            left += nums[i-1];
            right = total - left - nums[i];
            if (left == right) {
                set1.insert(left);
            }
        }
    }
    
public:
    bool splitArray(vector<int>& nums) {
        int n = nums.size();
        if (n < 7) {
            return false;
        }
        sum[0] = 0;
        for (int i = 0; i < n; ++i) {
            sum[i+1] = sum[i] + nums[i];
        }
        for (int j = 3; j <= n-4; ++j) {
            unordered_set<int> set1;
            unordered_set<int> set2;
            partition(nums, 0, j-1, set1);
            partition(nums, j+1, n-1, set2);
            for (auto& val : set1) {
                if (set2.find(val) != set2.end()) {
                    return true;
                }
            }
        }
        return false;
    }
    
    
};
