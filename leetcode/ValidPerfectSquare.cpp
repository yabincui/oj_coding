// 367. Valid Perfect Square
class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num == 1) {
            return true;
        }
        int low = 2;
        int high = num / 2;
        while (low <= high) {
            int mid = (low + high) / 2;
            long long s = (long long)mid * mid;
            if (s == num) {
                return true;
            } else if (s < num) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return false;
    }
};
