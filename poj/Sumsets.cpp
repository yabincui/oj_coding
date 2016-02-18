#include <stdio.h>

int N;
int pow[21];
int dp[1000001][21];

#define LIMIT 1000000000

int getCount() {
  pow[0] = 1;
  for (int i = 1; i <= 20; ++i) {
    pow[i] = pow[i-1] * 2;
  }
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= 20; ++j) {
      if (j == 0) {
        dp[i][j] = 1;
      } else if (i < pow[j]) {
        dp[i][j] = dp[i][j-1];
      } else {
        dp[i][j] = (dp[i - pow[j]][j] + dp[i][j-1]);
        if (dp[i][j] >= LIMIT) {
          dp[i][j] -= LIMIT;
        }
      }
    }
  }
  return dp[N][20];
}

int main() {
  freopen("Sumsets.in", "r", stdin);
  scanf("%d", &N);
  int result = getCount();
  printf("%d\n", result);
  return 0;
}
