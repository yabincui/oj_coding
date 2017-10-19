class Solution {
    
    bool recur(vector<int>& v, vector<int>& nums, int pos, int target) {
        if (pos == nums.size()) return true;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] + nums[pos] <= target) {
                v[i] += nums[pos];
                if (recur(v, nums, pos + 1, target)) {
                    return true;
                }
                v[i] -= nums[pos];
            }
        }
        return false;
    }
    
public:
    bool makesquare(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 4 != 0 || nums.size() < 4) {
            return false;
        }
        int target = sum / 4;
        vector<int> v(4, 0);
        return recur(v, nums, 0, target);
    }
};
