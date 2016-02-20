#include <stdio.h>

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <cstring>

using namespace std;

int N;
int A[2000];
int sortedA[2000];

long long dp[2000][2000]; // 4 * 10^6 * 8 = 32M.

long long getMinChange() {
  memcpy(sortedA, A, sizeof(A));
  sort(sortedA, &sortedA[N]);
  // First try nonincreasing order.
  // dp[i][j] means the cost to make (0..i) >= sortedA[j] and in nonincreasing order.
  for (int j = N-1; j >= 0; --j) {
    dp[0][j] = abs(A[0] - sortedA[j]);
    if (j != N - 1) {
      dp[0][j] = min(dp[0][j], dp[0][j+1]);
    }
  }
  for (int i = 1; i < N; ++i) {
    for (int j = N-1; j >= 0; --j) {
      dp[i][j] = abs(A[i] - sortedA[j]) + dp[i-1][j];
      if (j != N - 1) {
        dp[i][j] = min(dp[i][j], dp[i][j+1]);
      }
    }
  }
  long long result = LLONG_MAX;
  for (int j = 0; j < N; ++j) {
    result = min(result, dp[N-1][j]);
  }
  // Second try nondecreasing order.
  // dp[i][j] means the cost to make (0..i) <= sortedA[j] and in nondecreasing order.
  for (int j = 0; j < N; ++j) {
    dp[0][j] = abs(A[0] - sortedA[j]);
    if (j != 0) {
      dp[0][j] = min(dp[0][j], dp[0][j-1]);
    }
  }
  for (int i = 1; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      dp[i][j] = abs(A[i] - sortedA[j]) + dp[i-1][j];
      if (j != 0) {
        dp[i][j] = min(dp[i][j], dp[i][j-1]);
      }
    }
  }
  for (int j = 0; j < N; ++j) {
    result = min(result, dp[N-1][j]);
  }
  return result;
}

int main() {
  freopen("MakingTheGrade.in", "r", stdin);
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }
  long long result = getMinChange();
  printf("%lld\n", result);
  return 0;
}
