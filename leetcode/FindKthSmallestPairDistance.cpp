class Solution {
    
    int findCount(int dist, vector<int>& nums) {
        int count = 0;
        int end = 0;
        for (int begin = 0; begin < nums.size(); ++begin) {
            while (end < nums.size() && nums[end] - nums[begin] <= dist) {
                end++;
            }
            count += end - begin - 1;
        }
        //printf("dist = %d, count = %d\n", dist, count);
        return count;
    }
    
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int low = 0;
        int high = nums.back() - nums[0];
        while (low != high) {
            int mid = (low + high) / 2;
            int count = findCount(mid, nums); // <= mid
            if (count >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};