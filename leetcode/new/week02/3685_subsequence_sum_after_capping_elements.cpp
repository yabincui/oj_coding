// key: sort, dp
// error: value out of range of dp vector size
class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        // x = 1: 1, 1, 1, 1
        // x = 2: 2 2 2 2
        // 3 3 2 3 (subsequence)
        // sort nums.
        // 4000.
        // O(n*k*n).  dp[i][j]. using nums[0..i], whether can reach j.
        // when x = t, check dp[][] with.
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<bool>> dp(k + 1, vector<bool>(n, false));
        for (int i = 0; i < n; i++) {
            dp[0][i] = true;
            int a = nums[i];
            if (a <= k) {
                dp[a][i] = true;
            }
            if (i == 0) {
                continue;
            }
            for (int j = 0; j <= k; j++) {
                if (dp[j][i - 1]) {
                    dp[j][i] = true;
                    if (j + a <= k) {
                        dp[j + a][i] = true;
                    }
                }
            }
        }
        vector<bool> answer(n, false);
        int i = n - 1;
        for (int x = n; x >= 1; x--) {
            while (i >= 0 && nums[i] >= x) {
                i--;
            }
            int x_count = n - i - 1;
            if (x_count == n) {
                answer[x - 1] = can_fill_by_x(x, x_count, k); 
                continue;
            }
            for (int j = 0; j <= k; j++) {
                if (dp[j][i] && can_fill_by_x(x, x_count, k - j)) {
                    answer[x - 1] = true;
                    break;
                }
            }
        }
        return answer;
    }

    bool can_fill_by_x(int x, int x_count, int sum) {
        return sum % x == 0 && sum / x <= x_count;
    }
};