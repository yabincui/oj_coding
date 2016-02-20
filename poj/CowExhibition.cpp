#include <limits.h>
#include <stdio.h>

#include <algorithm>

using namespace std;

int N;

struct Cow {
  int s;
  int f;
} cows[100];

int dp[200001];

const int BASE = 100000;

int getMaxSum() {
  for (int j = -100000; j <= 100000; ++j) {
    dp[j + BASE] = INT_MIN;
  }
  dp[0 + BASE] = 0;
  for (int i = 0; i < N; ++i) {
    if (cows[i].s <= 0) {
      for (int j = -100000; j <= 100000; ++j) {
        int nj = j + cows[i].s;
        if (nj < -100000 || nj > 100000 || dp[j + BASE] == INT_MIN) {
          continue;
        }
        int ni = dp[j + BASE] + cows[i].f;
        if (dp[nj + BASE] < ni) {
          dp[nj + BASE] = ni;
        }
      }
    } else {
      for (int j = 100000; j >= -100000; --j) {
        int nj = j + cows[i].s;
        if (nj < -100000 || nj > 100000 || dp[j + BASE] == INT_MIN) {
          continue;
        }
        int ni = dp[j + BASE] + cows[i].f;
        if (dp[nj + BASE] < ni) {
          dp[nj + BASE] = ni;
        }
      }
    }
  }
  int result = 0;
  for (int j = 0; j <= 100000; ++j) {
    if (dp[j + BASE] >= 0) {
      result = max(result, j + dp[j + BASE]);
    }
  }
  return result;
}

int main() {
  freopen("CowExhibition.in", "r", stdin);
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &cows[i].s, &cows[i].f);
  }
  int result = getMaxSum();
  printf("%d\n", result);
  return 0;
}
