#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_V 1000001

bool h_prime[MAX_V + 1];
int primes[MAX_V + 1];
int dp[MAX_V + 1];

void init() {
  memset(dp, 0, sizeof(dp));
  memset(h_prime, false, sizeof(h_prime));
  for (int i = 5; i <= MAX_V; i += 4) {
    h_prime[i] = true;
  }
  for (int i = 5; i <= MAX_V; i += 4) {
    if (h_prime[i]) {
      int step = 2 * i;
      for (int j = i + step; j <= MAX_V; j += step) {
        h_prime[j] = false;
      }
    }
  }
  /*
  int prime_count = 0;
  for (int i = 5; i <= MAX_V; i += 4) {
    if (h_prime[i]) {
      primes[prime_count++] = i;
    }
  }
  for (int i = 0; primes[i] <= 789; ++i) {
    printf("primes[%d] = %d\n", i, primes[i]);
  }
  */

  for (int a = 5; a <= MAX_V; a += 4) {
    for (int b = a; b <= MAX_V; b += 4) {
      int64_t t = (int64_t)a * b;
      if (t > MAX_V) {
        break;
      }
      if (h_prime[a] && h_prime[b]) {
        if (dp[t] == 0) {
          dp[t] = 1;
        }
      } else {
        dp[t] = -1;
      }
    }
  }
  
  /*
  for (int i = 0; i < prime_count; ++i) {
    for (int j = i; j < prime_count; ++j) {
      int64_t t = (int64_t)primes[i] * primes[j];
      if (t > MAX_V) {
        break;
      }
      if (t < 26) {
        printf("%d * %d = %lld\n", primes[i], primes[j], t);
      }
      if ((t & 3) == 1) {
        dp[t] = 1;
        if (t < 26) {
          printf("%lld\n", t);
        }
      }
    }
  }
  */
  for (int i = 1; i <= MAX_V; ++i) {
    if (dp[i] == -1) {
      dp[i] = 0;
    }
    dp[i] += dp[i-1];
  }
}

int main() {
  freopen("SemiPrimeHNumbers.in", "r", stdin);
  init();
  int H;
  while (scanf("%d", &H) == 1 && H != 0) {
    printf("%d %d\n", H, dp[H]);
  }
  return 0;
}
