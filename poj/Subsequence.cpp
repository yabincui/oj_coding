#include <stdio.h>

int N, S;
int a[100000];

int getMinInterval() {
  int bestLen = 0;
  int start = 0, end = -1;
  int curSum = 0;
  while (end < N) {
    while (end < N && curSum < S) {
      curSum += a[end++];
    }
    if (curSum < S) {
      break;
    }
    while (start < end && curSum >= S) {
      curSum -= a[start++];
    }
    int len = end - start + 1;
    if (bestLen == 0 || bestLen > len) {
      bestLen = len;
    }
  }
  return bestLen;
}

int main() {
  freopen("Subsequence.in", "r", stdin);
  int tests;
  scanf("%d", &tests);
  while (tests-- > 0) {
    scanf("%d%d", &N, &S);
    for (int i = 0; i < N; ++i) {
      scanf("%d", &a[i]);
    }
    int result = getMinInterval();
    printf("%d\n", result);
  }
  return 0;
}
