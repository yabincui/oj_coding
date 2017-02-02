// 410. Split Array Largest Sum
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        uint64_t sum = 0;
        uint64_t max_value = 0;
        for (auto& n : nums) {
            sum += n;
            max_value = max(max_value, (uint64_t)n);
        }
        uint64_t low = max(sum / m, max_value);
        uint64_t high = max_value * (nums.size() + m - 1) / m;
        //printf("sum = %llu, max_value = %llu, low = %llu, high = %llu\n", sum, max_value, low, high);
        while (low < high) {
            uint64_t mid = (low + high) / 2;
            if (fulfill(nums, mid, m)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
    
    bool fulfill(vector<int>& nums, uint64_t mid, int m) {
        int count = 1;
        uint64_t cur = 0;
        for (auto& n : nums) {
            if (cur + n > mid) {
                count++;
                cur = n;
            } else {
                cur += n;
            }
        }
        //printf("mid = %llu, count = %d, m = %d\n", mid, count, m);
        return count <= m;
    }

    int splitArray2(vector<int>& nums, int m) {
        int n = nums.size();
        uint64_t sum[n + 1];
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1] + nums[i-1];
        }
        uint64_t dp[n + 1][m + 1];
        for (int j = 0; j <= m; ++j) {
            dp[0][j] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = UINT64_MAX;
            for (int j = 1; j <= m; ++j) {
                uint64_t min_value = UINT64_MAX;
                for (int pi = 0; pi < i; ++pi) {
                    uint64_t sub = sum[i] - sum[pi];
                    uint64_t tmp = max(sub, dp[pi][j-1]);
                    min_value = min(min_value, tmp);
                }
                dp[i][j] = min_value;
            }
        }
        return dp[n][m];
    }
};
