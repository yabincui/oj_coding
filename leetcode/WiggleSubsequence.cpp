class Solution {
public:
    int wiggleMaxLengthON2(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        vector<int> upCount(nums.size());
        vector<int> downCount(nums.size());
        upCount[0] = downCount[0] = 1;
        for (int i = 1; i < nums.size(); ++i) {
            int maxUpCount = 1;
            int maxDownCount = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    maxUpCount = max(maxUpCount, downCount[j] + 1); 
                } else if (nums[j] > nums[i]) {
                    maxDownCount = max(maxDownCount, upCount[j] + 1);
                }
            }
            upCount[i] = maxUpCount;
            downCount[i] = maxDownCount;
        }
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            res = max(res, max(upCount[i], downCount[i]));
        }
        return res;
    }
    
    int go(vector<int>& nums, bool firstUp) {
        int count = 1;
        bool needBigger = firstUp;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i-1]) {
                if (needBigger) {
                    count++;
                    needBigger = !needBigger;
                }
            } else if (nums[i] < nums[i-1]) {
                if (!needBigger) {
                    count++;
                    needBigger = !needBigger;
                }
            }
        }
        return count;
    }
    
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() < 2) return nums.size();
        int res = max(go(nums, true), go(nums, false));
        return res;
    }
};
