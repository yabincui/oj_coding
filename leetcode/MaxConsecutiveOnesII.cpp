// 487. Max Consecutive Ones II
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        return findMax2(nums, 1);
    }
    
    int findMax(vector<int>& nums, int k) {
        // dp[i] means converted i 0s to 1s, the cur 1 string length.
        int dp[k+1];
        memset(dp, 0, sizeof(dp));
        int max_len = 0;
        for (auto& num : nums) {
            if (num == 0) {
                // convert this 0 into 1.
                if (dp[k] > max_len) {
                    max_len = dp[k];
                }
                for (int i = k - 1; i >= 0; --i) {
                    dp[i+1] = dp[i] + 1;
                }
                dp[0] = 0;
            } else {
                for (int i = 0; i <= k; ++i) {
                    dp[i]++;
                }
            }
        }
        if (dp[k] > max_len) {
            max_len = dp[k];
        }
        return max_len;
    }
    
    int findMax2(vector<int>& nums, int k) {
        int start;
        int end;
        queue<int> zero_pos_queue;
        int max_len = 0;
        start = 0;
        int id = 0;
        for (auto& num : nums) {
            if (num == 1) {
            } else {
                zero_pos_queue.push(id);
                if (zero_pos_queue.size() == k + 1) {
                    int len = id - start;
                    if (len > max_len) {
                        max_len = len;
                    }
                    start = zero_pos_queue.front() + 1;
                    zero_pos_queue.pop();
                }
            }
            id++;
        }
        int len = id -start;
        if (len > max_len) {
            max_len = len;
        }
        return max_len;
    }
};
