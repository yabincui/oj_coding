class Solution {
    
    int split(vector<int>& nums, vector<int>& left, vector<int>& right) {
        for (int bit = 30; bit >= 0; --bit) {
            vector<int> a, b;
            int bitFlag = 1 << bit;
            for (int n : nums) {
                if (n & bitFlag) {
                    a.push_back(n);
                } else {
                    b.push_back(n);
                }
            }
            if (!a.empty() && !b.empty()) {
                left = std::move(a);
                right = std::move(b);
                return bit;
            }
        }
        return -1;
    }
    
    int recur(vector<int>& a, vector<int>& b, int bit) {
        if (bit == -1) {
            return a[0] ^ b[0];
        }
        vector<int> a_left, a_right, b_left, b_right;
        int bitFlag = 1 << bit;
        for (int n : a) {
            if (n & bitFlag) {
                a_right.push_back(n);
            } else {
                a_left.push_back(n);
            }
        }
        for (int n : b) {
            if (n & bitFlag) {
                b_right.push_back(n);
            } else {
                b_left.push_back(n);
            }
        }
        int maxValue = 0;
        if (!a_left.empty() && !b_right.empty()) {
            maxValue = max(maxValue, recur(a_left, b_right, bit - 1));
        }
        if (!a_right.empty() && !b_left.empty()) {
            maxValue = max(maxValue, recur(a_right, b_left, bit - 1));
        }
        if (maxValue > 0) {
            return maxValue;
        }
        return recur(a, b, bit - 1);
    }
    
    
public:
    int findMaximumXOR(vector<int>& nums) {
        vector<int> left, right;
        int bit = split(nums, left, right);
        //printf("bit = %d\n", bit);
        if (bit == -1) {
            return 0;
        }
        return recur(left, right, bit);
    }
};