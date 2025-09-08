// key: Bit operation
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int k = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (i != nums[i]) {
                if (k == -1) {
                    k = nums[i];
                } else {
                    k &= nums[i];
                }
            }
        }
        if (k == -1) {
            k = 0;
        }
        return k;
    }
};