class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> s;
        for (int i = 0; i < nums.size(); ++i) {
            if (i < 3 || i + 3 >= nums.size()) {
                s.push_back(nums[i]);
            }
        }
        int res = INT_MIN;
        dfs(s, 0, 0, 1, &res);
        return res;
    }
    
    void dfs(vector<int>& s, int curPos, int usedNum, int curMul, int* res) {
        if (usedNum == 3) {
            if (curMul > *res) {
                *res = curMul;
            }
            return;
        }
        if (curPos >= s.size()) {
            return;
        }
        while (curPos < s.size()) {
            dfs(s, curPos + 1, usedNum + 1, curMul * s[curPos], res);
            curPos++;
        }
    }
};
