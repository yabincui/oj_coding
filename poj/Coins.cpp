#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

// C * n * m => m * (C + n).

int N, M;
int A[100];
int C[100];

bool dp[100001];
bool cur[100001];

// TLE, how important it is to use locality when accessing array elements.
int getCount() {
  memset(dp, false, sizeof(dp));
  dp[0] = true;
  for (int i = 0; i < N; ++i) {
    memset(cur, false, sizeof(cur));
    int t = C[i] * A[i];
    for (int start = 0; start <= M && start < A[i]; ++start) {
      int k = start;
      for (int j = start; j <= M; j += A[i]) {
        if (dp[j]) {
          cur[j] = true;
        } else {
          k = max(k, j - t);
          while (k < j) {
            if (cur[k]) {
              dp[j] = true;
              break;
            } else {
              k += A[i];
            }
          }
        }
      }
    }
  }
  int count = 0;
  for (int i = 1; i <= M; ++i) {
    if (dp[i]) {
      count++;
    }
  }
  return count;
}

void zb(int c) {
  for (int i = M; i >= c; --i) {
    dp[i] |= dp[i-c];
  }
}

void cb(int c) {
  for (int i = c; i <= M; ++i) {
    dp[i] |= dp[i-c];
  }
}

int getCount2() {
  memset(dp, false, sizeof(dp));
  dp[0] = true;
  for (int i = 0; i < N; ++i) {
    int count = C[i];
    if (count * A[i] >= M) {
      cb(A[i]);
    } else {
      for (int k = 1; k < count; k *= 2) {
        zb(k * A[i]);
        count -= k;
      }
      zb(count * A[i]);
    }
  }
  int result = 0;
  for (int i = 1; i <= M; ++i) {
    if (dp[i]) {
      result++;
    }
  }
  return result;
}

int getCount3() {
  memset(dp, false, sizeof(dp));
  dp[0] = true;
  for (int i = 0; i < N; ++i) {
    int t = C[i] * A[i];
    if (t >= M) {
      cb(A[i]);
      continue;
    }
    memset(cur, false, sizeof(cur));
    for (int start = 0; start <= M && start < A[i]; ++start) {
      int k = start;
      for (int j = start; j <= M; j += A[i]) {
        if (dp[j]) {
          cur[j] = true;
        } else {
          k = max(k, j - t);
          while (k < j) {
            if (cur[k]) {
              dp[j] = true;
              break;
            } else {
              k += A[i];
            }
          }
        }
      }
    }
  }
  int count = 0;
  for (int i = 1; i <= M; ++i) {
    if (dp[i]) {
      count++;
    }
  }
  return count;
}

int main() {
  freopen("Coins.in", "r", stdin);
  while (scanf("%d%d", &N, &M) == 2 && !(N == 0 && M == 0)) {
    for (int i = 0; i < N; ++i) {
      scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; ++i) {
      scanf("%d", &C[i]);
    }
    int result = getCount3();
    printf("%d\n", result);
  }
  return 0;
}
