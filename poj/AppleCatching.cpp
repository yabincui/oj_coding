#include <stdio.h>

#include <algorithm>

using namespace std;

int T, W;
int S[1000];

int dp[1001][31][2];

int getMax() {
  for (int i = 0; i <= T; ++i) {
    for (int j = 0; j <= W; ++j) {
      for (int k = 0; k < 2; ++k) {
        if (i == 0) {
          dp[i][j][k] = 0;
          continue;
        }
        if (j == 0) {
          // The cow starts at tree 1.
          dp[i][j][k] = (k == 0) ? (dp[i-1][j][k] + (S[i-1] == 1)) : 0;
          continue;
        }
        dp[i][j][k] = max(dp[i-1][j][k], dp[i-1][j-1][1-k]) + (S[i-1] == k + 1);
      }
    }
  }
  return max(dp[T][W][0], dp[T][W][1]);
}

int main() {
  freopen("AppleCatching.in", "r", stdin);
  scanf("%d%d", &T, &W);
  for (int i = 0; i < T; ++i) {
    scanf("%d", &S[i]);
  }
  int result = getMax();
  printf("%d\n", result);
  return 0;
}
