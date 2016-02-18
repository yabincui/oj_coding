#include <stdio.h>

#include <algorithm>
#include <utility>

using namespace std;

int N, M, R;

struct Work {
  int start;
  int end;
  int efficiency;
} works[1000];

int dp[1000];

bool compareWork(const Work& w1, const Work& w2) {
  return w1.start < w2.start;
}

int main() {
  freopen("MilkingTime.in", "r", stdin);
  scanf("%d%d%d", &N, &M, &R);
  for (int i = 0; i < M; ++i) {
    scanf("%d%d%d", &works[i].start, &works[i].end, &works[i].efficiency);
  }
  sort(works, &works[M], compareWork);
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < M; ++i) {
    int prev = 0;
    for (int j = 0; j < i; ++j) {
      if (works[j].end + R <= works[i].start) {
        prev = max(prev, dp[j]);
      }
    }
    dp[i] = prev + works[i].efficiency;
  }
  int result = 0;
  for (int i = 0; i < M; ++i) {
    result = max(dp[i], result);
  }
  printf("%d\n", result);
  return 0;
}
