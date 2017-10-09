class Solution {
public:
    int largestPalindrome(int n) {
        if (n == 1) return 9;
        uint64_t max_n = 1;
        for (int i = 0; i < n; ++i) {
          max_n *= 10;
        }
        max_n--;
        uint64_t min_n = (max_n + 1) / 10;
        for (uint64_t a = max_n; a >= min_n; --a) {
          uint64_t u = getPalindrome(a, n);
          //printf("try u = %llu\n", (unsigned long long)u);
          double limit = sqrt(u);
          for (uint64_t b = max_n; b >= limit; b--) {
            if (u % b == 0) {
              //printf("b = %u\n", (int)b);
              return u % 1337;
            }
          }
        }
    }

    uint64_t getPalindrome(uint64_t a, int n) {
      int digits[32];
      int i = n - 1;
      uint64_t temp = a;
      while (temp != 0) {
        digits[i--] = temp % 10;
        temp /= 10;
      }
      for (int i = n; i < 2 * n; ++i) {
        digits[i] = digits[2 * n - 1 - i];
      }
      uint64_t res = 0;
      for (int i = 0; i < 2 * n; ++i) {
        res = res * 10 + digits[i];
      }
      return res;
    }
};
