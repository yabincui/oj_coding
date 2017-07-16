class Solution {
    
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if (desiredTotal == 0) return true;
        if (maxChoosableInteger * (maxChoosableInteger + 1) < desiredTotal) {
            return false;
        }
        int mask = (1 << maxChoosableInteger) - 1;
        vector<bool> dp(mask + 1, false);  // dp[i] means let you start with i state (value 1 in bits of i can be choosen), can you win?
        for (int i = 0; i <= mask; ++i) {
            int prev_sum = 0;
            for (int j = 0; j < maxChoosableInteger; ++j) {
                if ((i & (1 << j)) == 0) {
                    prev_sum += j + 1;
                }
            }
            if (prev_sum >= desiredTotal) {
                dp[i] = false;
                //printf("dp[%d] = false\n", i);
                continue;
            }
            dp[i] = false;
            for (int j = 0; j < maxChoosableInteger; ++j) {
                if (i & (1 << j)) {
                    if (!dp[i & ~(1 << j)]) {
                        dp[i] = true;
                        break;
                    }
                }
            }
            //printf("dp[%d] = %d\n", i, dp[i]);
        }
        return dp[mask];
    }
};
