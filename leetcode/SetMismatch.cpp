class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        vector<bool> hit(n + 1, false);
        vector<int> res;
        for (auto num : nums) {
            if (hit[num]) {
                res.push_back(num);
            } else {
                hit[num] = true;
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (!hit[i]) {
                res.push_back(i);
                break;
            }
        }
        return res;
    }
};
