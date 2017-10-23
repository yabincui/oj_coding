// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int low = 1;
        int high = n;
        while (low != high) {
            int mid = low + (high - low) / 2;
            int ret = guess(mid);
            if (ret == 0) {
                return mid;
            }
            if (ret > 0) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }
};