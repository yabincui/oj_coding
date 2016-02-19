#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <utility>

using namespace std;

int N;
pair<int, int> s[5000];
bool dp[5000];

int getMinCount() {
  memset(dp, false, sizeof(dp));
  int count = 0;
  while (true) {
    int start;
    for (start = 0; start < N; ++start) {
      if (!dp[start]) {
        break;
      }
    }
    if (start == N) {
      break;
    }
    count++;
    dp[start] = true;
    int prevW = s[start].second;
    for (int i = start + 1; i < N; ++i) {
      if (!dp[i] && s[i].second >= prevW) {
        dp[i] = true;
        prevW = s[i].second;
      }
    }
  }
  return count;
}

int main() {
  freopen("WoodenSticks.in", "r", stdin);
  int test_count;
  scanf("%d", &test_count);
  for (int test = 1; test <= test_count; ++test) {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
      scanf("%d%d", &s[i].first, &s[i].second);
    }
    sort(s, &s[N]);
    int result = getMinCount();
    printf("%d\n", result);
  }
  return 0;
}
