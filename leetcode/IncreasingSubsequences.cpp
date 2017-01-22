class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        recur(-200, 0, nums, path, result);
        return result;
    }
    
    void recur(int lastValue, int curIndex, const vector<int>& nums, vector<int>& path, vector<vector<int>>& result) {
        if (curIndex == nums.size()) {
            return;
        }
        unordered_map<int, bool> used;
        for (int i = curIndex; i < nums.size(); ++i) {
            if (nums[i] >= lastValue && used.find(nums[i]) == used.end()) {
                used[nums[i]] = true;
                path.push_back(nums[i]);
                if (path.size() > 1) {
                    result.push_back(path);
                }
                recur(nums[i], i + 1, nums, path, result);
                path.pop_back();
            }
        }
    }
};
