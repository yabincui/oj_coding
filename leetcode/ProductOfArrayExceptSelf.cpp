class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size());
        int cur = 1;
        for (int i = 0; i < nums.size(); ++i) {
            res[i] = cur * nums[i];
            cur = res[i];
        }
        int next = 1;
        for (int i = nums.size() - 1; i >= 0; --i) {
            // res[i] = res[i-1] * next;
            int prev = (i == 0) ? 1 : res[i - 1];
            res[i] = prev * next;
            next *= nums[i];
        }
        return res;
    }
};