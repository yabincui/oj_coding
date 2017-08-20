class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> increasingArray;
        for (int num : nums) {
            auto it = lower_bound(increasingArray.begin(), increasingArray.end(), num);
            if (it == increasingArray.end()) {
                increasingArray.push_back(num);
            } else {
                *it = num;
            }
        }
        return increasingArray.size();
    }
};
