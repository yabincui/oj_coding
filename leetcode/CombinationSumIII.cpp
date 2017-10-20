class Solution {
    
    void recur(int cur, int k, int leftSum, vector<int>& path, vector<vector<int>>& res) {
        if (k == 0 || cur == 10) {
            if (k == 0 && leftSum == 0) {
                res.push_back(path);
            }
            return;
        }
        if (cur <= leftSum) {
            path.push_back(cur);
            recur(cur + 1, k - 1, leftSum - cur, path, res);
            path.pop_back();
        }
        recur(cur + 1, k, leftSum, path, res);
    }
    
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> path;
        recur(1, k, n, path, res);
        return res;
    }
};