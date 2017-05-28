class Solution {

    int dp[32][2];

    int findCount(int bits, bool hasPrefixOne) {
        if (dp[bits][hasPrefixOne] != -1) {
            return dp[bits][hasPrefixOne];
        }
        int result = 0;
        if (bits == 0) {
            result = 1;
        } else {
            result = findCount(bits - 1, false);
            if (!hasPrefixOne) {
                result += findCount(bits - 1, true);
            }
        }
        //printf("dp[bits = %d][hasPrefixOne = %d] = %d\n", bits, hasPrefixOne, result);
        dp[bits][hasPrefixOne] = result;
        return result;
    }

public:
    int findIntegers(int num) {
        memset(dp, -1, sizeof(dp));

        int result = 0;
        bool hasTwoContinueOne = false;
        int prevBitValue = 0;
        for (int bits = 32; bits >= 1; bits--) {
            int bitValue = (num >> (bits - 1)) & 1;
            if (bitValue == 1) {
                result += findCount(bits - 1, false);
                //printf("bits = %d, result = %d\n", bits, result);
            }
            if (prevBitValue == 1 && bitValue == 1) {
                hasTwoContinueOne = true;
                break;
            }
            prevBitValue = bitValue;
        }
        //printf("result = %d, hasTwoContinueOne = %d\n", result, hasTwoContinueOne);
        if (!hasTwoContinueOne) {
            result++;
        }
        return result;
    }
};
