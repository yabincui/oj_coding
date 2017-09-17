class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        vector<double> s;
        for (auto n : nums) {
            s.push_back(n);
        }
        return judgePoint24(s);
    }
    
    bool isEqual(double a, double b) {
        return abs(a - b) < 1e-6;
    }
    
    bool judgePoint24(vector<double>& nums) {
        if (nums.size() == 1) {
            return isEqual(nums[0], 24);
        }
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                if (i == j) continue;
                vector<double> new_nums;
                for (int k = 0; k < nums.size(); ++k) {
                    if (k == i || k == j) continue;
                    new_nums.push_back(nums[k]);
                }
                for (int op = 0; op < 4; ++op) {
                    if (op == 0) {
                        new_nums.push_back(nums[i] + nums[j]);
                    } else if (op == 1) {
                        new_nums.push_back(nums[i] - nums[j]);
                    } else if (op == 2) {
                        new_nums.push_back(nums[i] * nums[j]);
                    } else if (op == 3) {
                        if (isEqual(nums[j], 0)) continue;
                        new_nums.push_back(nums[i] / nums[j]);
                    }
                    if (judgePoint24(new_nums)) {
                        return true;
                    }
                    new_nums.pop_back();
                }
            }
        }
        return false;
    }
};
