// key: math, no error
class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int64_t result = 0;
        int bigger_edge = -1;
        int smaller_edge = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > right) {
                int64_t len = i - bigger_edge - 1;
                result += len * (len + 1) / 2;
                bigger_edge = i;
            }
            if (nums[i] >= left) {
                int64_t len = i - smaller_edge - 1;
                result -= len * (len + 1) / 2;
                smaller_edge = i;
            }
        }
        int64_t len = (int)nums.size() - bigger_edge - 1;
        result += len * (len + 1) / 2;
        len = (int)nums.size() - smaller_edge - 1;
        result -= len * (len + 1) / 2;
        return result;
    }
};