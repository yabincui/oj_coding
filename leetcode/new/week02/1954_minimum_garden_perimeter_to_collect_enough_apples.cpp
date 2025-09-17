// key: binary search, integer overflow
// error: return value requirement
class Solution {
public:
    long long minimumPerimeter(long long neededApples) {
        
      //  1  2  3  4
      //  5  6  7  8
      //  9 10 11 12
      // 13 14 15 16

      // reach k, [-k, k] * (2*k + 1) * 2
      // k * (k + 1) * (2*k + 1) * 2
      // use binary search.
      long long low  = 1;
      long long high = max((long long)sqrt(neededApples), 2LL);
      while (low + 1 < high) {
        long long mid = (low + high) / 2;
        long long a = mid * (mid + 1);
        if (neededApples / a >= (2 * mid + 1) * 2) {
            low = mid;
        } else {
            high = mid;
        }
      }
      if (low + 1 == high) {
        if (low * (low + 1) * (2 * low + 1) * 2 >= neededApples) {
            high = low;
        }
      }
      return high * 8;
    }
};