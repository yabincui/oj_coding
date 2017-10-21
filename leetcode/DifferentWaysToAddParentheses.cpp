class Solution {
    
    void splitInput(string& input, vector<int>& nums, vector<char>& ops) {
        int i = 0;
        while (i < input.size()) {
            char c = input[i++];
            if (isdigit(c)) {
                int value = 0;
                while (isdigit(c)) {
                    value = value * 10 + c - '0';
                    if (i == input.size()) break;
                    c = input[i++];
                }
                if (!isdigit(c)) --i;
                nums.push_back(value);
            } else {
                ops.push_back(c);
            }
        }
    }
    
    vector<int> permuteGroup(vector<int>& nums, vector<char>& ops, int left, int right) {
        vector<int> res;
        if (left == right) {
            res.push_back(nums[left]);
            return res;
        }
        // select an op from [left, right).
        for (int opIndex = left; opIndex < right; ++opIndex) {
            char op = ops[opIndex];
            vector<int> leftValues = permuteGroup(nums, ops, left, opIndex);
            vector<int> rightValues = permuteGroup(nums, ops, opIndex + 1, right);
            for (int lv : leftValues) {
                for (int rv : rightValues) {
                    int value;
                    if (op == '+') value = lv + rv;
                    else if (op == '-') value = lv - rv;
                    else value = lv * rv;
                    //printf("[%d - %d], opIndex = %d, lv = %d, rv = %d, res = %d\n", left, right, opIndex, olv, rv, lv);
                    res.push_back(value);
                }
            }
        }
        return res;
    }
    
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> nums;
        vector<char> ops;
        splitInput(input, nums, ops);
        if (nums.empty()) {
            return vector<int>(1, 0);
        }
        int right = static_cast<int>(nums.size()) - 1;
        return permuteGroup(nums, ops, 0, right);
    }
};