class NumArray {
    
    vector<int64_t> sum;
    
public:
    NumArray(vector<int> nums) {
        sum.resize(nums.size() + 1, 0);
        for (int i = 1; i <= nums.size(); ++i) {
            sum[i] = sum[i-1] + nums[i-1];
            //printf("sum[%d] = %lld\n", i, (long long)sum[i]);
        }
    }
    
    int sumRange(int i, int j) {
        //printf("i=%d, j=%d\n", i, j);
        return sum[j+1] - sum[i];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */